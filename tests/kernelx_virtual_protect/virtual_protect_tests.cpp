#include <windows.h>
#include <array>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

constexpr SIZE_T PAGE_SIZE_4KB = 1ULL << 12;
constexpr SIZE_T PAGE_SIZE_64K = 1ULL << 16;
constexpr SIZE_T PAGE_SIZE_2MB = 1ULL << 21;
constexpr SIZE_T PAGE_SIZE_4MB = 1ULL << 22;

#include "production_virtual_protect.h"

namespace
{
    void require(bool condition, const char* message)
    {
        if (!condition) throw std::runtime_error(message);
    }

    struct MappedAllocation
    {
        BYTE* base = nullptr;
        HANDLE mapping = nullptr;
        SIZE_T blockSize;
        std::array<bool, 3> mapped{};
        SIZE_T registeredSize;

        explicit MappedAllocation(std::array<bool, 3> committed = {true, true, true},
                                  bool large = false, SIZE_T trackedBlocks = 3)
            : blockSize(large ? PAGE_SIZE_4MB : PAGE_SIZE_64K),
              registeredSize(trackedBlocks * blockSize)
        {
            try
            {
                const auto size = blockSize * mapped.size();
                MEM_ADDRESS_REQUIREMENTS addressRequirements{};
                addressRequirements.Alignment = blockSize;
                MEM_EXTENDED_PARAMETER parameter{};
                parameter.Type = MemExtendedParameterAddressRequirements;
                parameter.Pointer = &addressRequirements;
                base = static_cast<BYTE*>(VirtualAlloc2(nullptr, nullptr, size,
                    MEM_RESERVE | MEM_RESERVE_PLACEHOLDER, PAGE_NOACCESS, &parameter, 1));
                require(base != nullptr, "fixture placeholder reservation failed");
                for (SIZE_T i = 0; i + 1 < mapped.size(); ++i)
                    require(VirtualFree(base + i * blockSize, blockSize,
                        MEM_RELEASE | MEM_PRESERVE_PLACEHOLDER) != FALSE,
                        "fixture placeholder split failed");
                mapping = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE,
                    0, static_cast<DWORD>(size), nullptr);
                require(mapping != nullptr, "fixture file mapping failed");
                for (SIZE_T i = 0; i < mapped.size(); ++i)
                {
                    if (!committed[i]) continue;
                    require(MapViewOfFile3(mapping, nullptr, base + i * blockSize,
                        i * blockSize, blockSize, MEM_REPLACE_PLACEHOLDER,
                        PAGE_READWRITE, nullptr, 0) != nullptr,
                        "fixture view replacement failed");
                    mapped[i] = true;
                }
                AcquireSRWLockExclusive(&XwpMappableLock);
                XwpMappables[reinterpret_cast<ULONG_PTR>(base)] = {registeredSize, large ? 1ULL : 0ULL};
                ReleaseSRWLockExclusive(&XwpMappableLock);
            }
            catch (...)
            {
                release();
                throw;
            }
        }

        MappedAllocation(const MappedAllocation&) = delete;
        MappedAllocation& operator=(const MappedAllocation&) = delete;
        ~MappedAllocation() { release(); }

        void release()
        {
            if (base)
            {
                AcquireSRWLockExclusive(&XwpMappableLock);
                XwpMappables.erase(reinterpret_cast<ULONG_PTR>(base));
                ReleaseSRWLockExclusive(&XwpMappableLock);
                for (SIZE_T i = 0; i < mapped.size(); ++i)
                {
                    if (mapped[i]) UnmapViewOfFile2(GetCurrentProcess(), base + i * blockSize, 0);
                    else VirtualFree(base + i * blockSize, 0, MEM_RELEASE);
                }
                base = nullptr;
            }
            if (mapping) CloseHandle(mapping);
            mapping = nullptr;
        }

        DWORD protection(SIZE_T offset) const
        {
            MEMORY_BASIC_INFORMATION info{};
            require(VirtualQuery(base + offset, &info, sizeof(info)) == sizeof(info),
                "fixture query failed");
            return info.Protect;
        }
    };

    void boundedRange(SIZE_T offset, SIZE_T size, SIZE_T first, SIZE_T last)
    {
        MappedAllocation allocation;
        DWORD oldProtect = 0;
        require(EraVirtualProtect(allocation.base + offset, size, PAGE_READONLY, &oldProtect),
            "valid request failed");
        require(oldProtect == PAGE_READWRITE, "wrong first-page previous protection");
        for (SIZE_T page = 0; page < 4; ++page)
        {
            const DWORD expected = (page >= first && page <= last) ? PAGE_READONLY : PAGE_READWRITE;
            require(allocation.protection(page * PAGE_SIZE_4KB) == expected,
                "changed a page outside the requested byte range");
        }
    }

    void exactPage() { boundedRange(0, PAGE_SIZE_4KB, 0, 0); }
    void unalignedEnd() { boundedRange(1, PAGE_SIZE_4KB - 1, 0, 0); }
    void straddlingBytes() { boundedRange(PAGE_SIZE_4KB - 1, 2, 0, 1); }
    void twoPages() { boundedRange(0, 2 * PAGE_SIZE_4KB, 0, 1); }

    void adjacentView()
    {
        MappedAllocation allocation;
        DWORD oldProtect = 0;
        require(EraVirtualProtect(allocation.base + PAGE_SIZE_64K - 1, 1,
            PAGE_READONLY, &oldProtect), "last-byte request failed");
        require(allocation.protection(PAGE_SIZE_64K - PAGE_SIZE_4KB) == PAGE_READONLY,
            "requested page was not protected");
        require(allocation.protection(PAGE_SIZE_64K) == PAGE_READWRITE,
            "changed the neighboring mapped view");
    }

    void spansViews()
    {
        MappedAllocation allocation;
        DWORD oldProtect = 0;
        require(EraVirtualProtectEx(GetCurrentProcess(), allocation.base + PAGE_SIZE_64K - 1,
            2, PAGE_READONLY, &oldProtect), "cross-view request failed");
        require(allocation.protection(PAGE_SIZE_64K - PAGE_SIZE_4KB) == PAGE_READONLY &&
            allocation.protection(PAGE_SIZE_64K) == PAGE_READONLY &&
            allocation.protection(PAGE_SIZE_64K + PAGE_SIZE_4KB) == PAGE_READWRITE,
            "cross-view protection touched the wrong pages");
    }

    void rejectsSize(SIZE_T size)
    {
        MappedAllocation allocation;
        DWORD oldProtect = 0x12345678;
        SetLastError(ERROR_SUCCESS);
        const auto status = EraVirtualProtect(allocation.base + 1, size, PAGE_READONLY, &oldProtect);
        const auto error = GetLastError();
        require(!status, "invalid size was reported as successful");
        require(error == ERROR_INVALID_PARAMETER, "invalid size returned the wrong error");
        require(allocation.protection(0) == PAGE_READWRITE, "invalid size modified memory protection");
        require(oldProtect == 0x12345678, "invalid size changed the output value");
    }
    void zeroSize() { rejectsSize(0); }
    void overflowingSize() { rejectsSize((std::numeric_limits<SIZE_T>::max)()); }

    void outsideAllocation()
    {
        MappedAllocation allocation({true, true, true}, false, 2);
        DWORD oldProtect = 0;
        SetLastError(ERROR_SUCCESS);
        const auto status = EraVirtualProtect(allocation.base + allocation.registeredSize - 1,
            2, PAGE_READONLY, &oldProtect);
        const auto error = GetLastError();
        require(!status && error == ERROR_INVALID_ADDRESS, "cross-allocation range was accepted");
        require(allocation.protection(allocation.registeredSize - PAGE_SIZE_4KB) == PAGE_READWRITE &&
            allocation.protection(allocation.registeredSize) == PAGE_READWRITE,
            "cross-allocation request modified protection");
    }

    void laterFailure()
    {
        MappedAllocation allocation({true, false, true});
        DWORD oldProtect = 0;
        SetLastError(ERROR_SUCCESS);
        const auto status = EraVirtualProtect(allocation.base,
            2 * PAGE_SIZE_64K + 1, PAGE_READONLY, &oldProtect);
        const auto error = GetLastError();
        require(!status, "a later page failure was reported as success");
        require(error == ERROR_INVALID_ADDRESS, "later page failure lost the Windows error");
        require(allocation.protection(2 * PAGE_SIZE_64K) == PAGE_READWRITE,
            "continued changing pages after the first failure");
    }

    void firstFailure()
    {
        MappedAllocation allocation({false, true, true});
        DWORD oldProtect = 0;
        SetLastError(ERROR_SUCCESS);
        const auto status = EraVirtualProtect(allocation.base, PAGE_SIZE_64K + 1,
            PAGE_READONLY, &oldProtect);
        const auto error = GetLastError();
        require(!status && error == ERROR_INVALID_ADDRESS, "first page failure was lost");
        require(allocation.protection(PAGE_SIZE_64K) == PAGE_READWRITE,
            "changed a later page after the first page failed");
    }

    void previousProtection()
    {
        MappedAllocation allocation;
        DWORD ignored = 0;
        require(VirtualProtect(allocation.base, PAGE_SIZE_4KB, PAGE_NOACCESS, &ignored),
            "fixture initial protection failed");
        DWORD oldProtect = 0;
        require(EraVirtualProtect(allocation.base, PAGE_SIZE_4KB + 1, PAGE_READONLY, &oldProtect),
            "mixed-protection request failed");
        require(oldProtect == PAGE_NOACCESS, "did not return the first page's previous protection");
    }

    void optionalOutput()
    {
        MappedAllocation allocation;
        require(EraVirtualProtect(allocation.base, 1, PAGE_READONLY, nullptr),
            "optional old-protection output was rejected");
        require(allocation.protection(0) == PAGE_READONLY, "optional-output request had no effect");
    }

    void largeMapping()
    {
        MappedAllocation allocation({true, true, true}, true);
        DWORD oldProtect = 0;
        require(EraVirtualProtect(allocation.base, PAGE_SIZE_2MB, PAGE_READONLY, &oldProtect),
            "4-MiB mapping request failed");
        require(allocation.protection(0) == PAGE_READONLY &&
            allocation.protection(PAGE_SIZE_2MB - PAGE_SIZE_4KB) == PAGE_READONLY &&
            allocation.protection(PAGE_SIZE_2MB) == PAGE_READWRITE,
            "changed the next 2-MiB protection unit");
    }

    void normalAllocation()
    {
        auto base = VirtualAlloc(nullptr, 2 * PAGE_SIZE_4KB, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        require(base != nullptr, "ordinary allocation failed");
        DWORD oldProtect = 0;
        const auto status = EraVirtualProtect(base, PAGE_SIZE_4KB, PAGE_READONLY, &oldProtect);
        MEMORY_BASIC_INFORMATION neighbor{};
        VirtualQuery(static_cast<BYTE*>(base) + PAGE_SIZE_4KB, &neighbor, sizeof(neighbor));
        VirtualFree(base, 0, MEM_RELEASE);
        require(status && oldProtect == PAGE_READWRITE && neighbor.Protect == PAGE_READWRITE,
            "ordinary Windows allocation forwarding failed");
    }

    void limitedHandle()
    {
        MappedAllocation allocation;
        const auto handle = OpenProcess(PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
        require(handle != nullptr, "operation-only process handle failed");
        DWORD oldProtect = 0;
        const auto status = EraVirtualProtectEx(handle, allocation.base, 1, PAGE_READONLY, &oldProtect);
        CloseHandle(handle);
        require(status && oldProtect == PAGE_READWRITE && allocation.protection(0) == PAGE_READONLY,
            "added a process-query permission requirement");
    }
}

int main()
{
    const std::pair<const char*, void (*)()> cases[] = {
        {"exact 4-KiB page excludes its neighbor", exactPage},
        {"unaligned range ending at a page boundary", unalignedEnd},
        {"two bytes straddling a boundary", straddlingBytes},
        {"two exact pages exclude the third", twoPages},
        {"last byte excludes an adjacent mapped view", adjacentView},
        {"range spanning mapped views", spansViews},
        {"zero size fails without modification", zeroSize},
        {"overflowing size fails without modification", overflowingSize},
        {"range cannot leave its tracked allocation", outsideAllocation},
        {"later page failure stops and returns failure", laterFailure},
        {"first page failure stops immediately", firstFailure},
        {"reports the first page's previous protection", previousProtection},
        {"old-protection output remains optional", optionalOutput},
        {"4-MiB mapping respects a 2-MiB boundary", largeMapping},
        {"ordinary allocation forwards to Windows", normalAllocation},
        {"operation-only process handle remains usable", limitedHandle},
    };
    unsigned failed = 0;
    for (const auto& [name, run] : cases)
    {
        try { run(); std::cout << "PASS: " << name << '\n'; }
        catch (const std::exception& error)
        {
            ++failed;
            std::cout << "FAIL: " << name << ": " << error.what() << '\n';
        }
    }
    std::cout << (std::size(cases) - failed) << '/' << std::size(cases) << " checks passed\n";
    return failed ? 1 : 0;
}
