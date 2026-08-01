#include "kernelx.h"
#include "Logan.h"
#include <atlbase.h>
#include "Hooks.h"
#include <winternl.h>
#include "EraCoreApplication.h"

EXTERN_C CONSOLE_TYPE __stdcall GetConsoleType()
{
    return CONSOLE_TYPE_XBOX_ONE;
}

EXTERN_C VOID __stdcall GetSystemOSVersion(LPSYSTEMOSVERSIONINFO lpVersionInformation)
{
    DWORD FileVersionSize = GetFileVersionInfoSizeW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL);
    if (!FileVersionSize)
    {
        MessageBoxW(nullptr,
                    L"Couldn't get the combase version info size! Make sure you have EmbeddedXvd in the game "
                    L"root/Mount folder.",
                    L"Error!", MB_OK);
    }

    BYTE *Data = new BYTE[FileVersionSize];
    BOOL ret = GetFileVersionInfoW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL, FileVersionSize, Data);
    if (!ret)
    {
        MessageBoxW(
            nullptr,
            L"Couldn't get the combase version info! Make sure you have EmbeddedXvd in the game root/Mount folder.",
            L"Error!", MB_OK);
        delete[] Data;
    }

    VS_FIXEDFILEINFO *pFixedFileInfo{};
    UINT Length = 0;

    VerQueryValueW(Data, L"\\", (LPVOID *)&pFixedFileInfo, &Length);
    if (!pFixedFileInfo)
    {
        MessageBoxW(
            nullptr,
            L"Couldn't get the combase version value! Make sure you have EmbeddedXvd in the game root/Mount folder.",
            L"Error!", MB_OK);
        delete[] Data;
    }

    DWORD major = HIWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD minor = LOWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD build = HIWORD(pFixedFileInfo->dwProductVersionLS);
    DWORD revision = LOWORD(pFixedFileInfo->dwProductVersionLS);

    lpVersionInformation->MajorVersion = (BYTE)major;
    lpVersionInformation->MinorVersion = (BYTE)minor;
    lpVersionInformation->BuildNumber = (WORD)build;
    lpVersionInformation->Revision = (WORD)revision;
    delete[] Data;
}

EXTERN_C VOID __stdcall QueryProcessorSchedulingStatistics(PPROCESSOR_SCHEDULING_STATISTICS lpStatistics)
{
    LARGE_INTEGER Frequency, Counter;
    FILETIME IdleTime, KernelTime, UserTime;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&Counter);
    lpStatistics->GlobalTime = Counter.QuadPart / (Frequency.QuadPart / 10000000ULL);

    if (GetSystemTimes(&IdleTime, &KernelTime, &UserTime))
    {
        ULARGE_INTEGER IdleTime64 = {IdleTime.dwLowDateTime, IdleTime.dwHighDateTime};
        ULARGE_INTEGER KernelTime64 = {KernelTime.dwLowDateTime, KernelTime.dwHighDateTime};
        ULARGE_INTEGER UserTime64 = {UserTime.dwLowDateTime, UserTime.dwHighDateTime};
        lpStatistics->RunningTime = (KernelTime64.QuadPart - IdleTime64.QuadPart) + UserTime64.QuadPart;
        lpStatistics->IdleTime = IdleTime64.QuadPart;
    }
    else
    {
        lpStatistics->RunningTime = 0;
        lpStatistics->IdleTime = 0;
    }
}

EXTERN_C BOOL __stdcall SetThreadpoolAffinityMask(PTP_POOL Pool, DWORD_PTR dwThreadAffinityMask)
{
    UNREFERENCED_PARAMETER(Pool);
    UNREFERENCED_PARAMETER(dwThreadAffinityMask);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C BOOL __stdcall SetThreadName(HANDLE hThread, PCWSTR lpThreadName)
{
    HRESULT hr = SetThreadDescription(hThread, lpThreadName);
    SetLastError(WIN32_FROM_HRESULT(hr));
    return SUCCEEDED(hr);
}

EXTERN_C BOOL __stdcall GetThreadName(HANDLE hThread, PWSTR lpThreadName, SIZE_T dwBufferLength,
                                      PSIZE_T pdwReturnLength)
{
    PWSTR pszThreadDescription;
    int nThreadDescriptionLength;

    if (!pdwReturnLength)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    if (HRESULT hr; FAILED(hr = GetThreadDescription(hThread, &pszThreadDescription)))
    {
        *pdwReturnLength = 0;
        SetLastError(WIN32_FROM_HRESULT(hr));
        return FALSE;
    }

    nThreadDescriptionLength = lstrlenW(pszThreadDescription);
    *pdwReturnLength = nThreadDescriptionLength;

    if (!lpThreadName || nThreadDescriptionLength >= dwBufferLength)
    {
        LocalFree((HLOCAL)pszThreadDescription);
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }

    CopyMemory(lpThreadName, pszThreadDescription, sizeof(WCHAR) * nThreadDescriptionLength);
    lpThreadName[nThreadDescriptionLength] = L'\0';
    LocalFree((HLOCAL)pszThreadDescription);
    SetLastError(ERROR_SUCCESS);
    return TRUE;
}

EXTERN_C BOOL __stdcall TitleMemoryStatus(LPTITLEMEMORYSTATUS lpBuffer)
{
    if (lpBuffer->dwLength != 64)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    INT64 ProcessInformation[7]{};
    NTSTATUS Result = NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)(0x3A | 0x3A), ProcessInformation, 56, 0);
    if (!NT_SUCCESS(Result))
    {
        SetLastError(Result);
        return FALSE;
    }

    lpBuffer->ullTotalMem = ProcessInformation[0];
    lpBuffer->ullAvailMem = ProcessInformation[0] - ProcessInformation[1];
    lpBuffer->ullLegacyUsed = ProcessInformation[2];
    lpBuffer->ullLegacyAvail = ProcessInformation[4] - ProcessInformation[2];
    lpBuffer->ullLegacyPeak = ProcessInformation[3];
    lpBuffer->ullTitleUsed = ProcessInformation[5];
    lpBuffer->ullTitleAvail = ProcessInformation[6] - ProcessInformation[5];

    SetLastError(ERROR_SUCCESS);
    return TRUE;
}

EXTERN_C BOOL __stdcall JobTitleMemoryStatus(LPTITLEMEMORYSTATUS lpBuffer)
{
    UNREFERENCED_PARAMETER(lpBuffer);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C BOOL __stdcall ToolingMemoryStatus(LPTOOLINGMEMORYSTATUS lpBuffer)
{
    UNREFERENCED_PARAMETER(lpBuffer);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C BOOL __stdcall AllocateTitlePhysicalPages(HANDLE hProcess, DWORD flAllocationType, PULONG_PTR NumberOfPages,
                                                   PULONG_PTR PageArray)
{
    UNREFERENCED_PARAMETER(hProcess);

    if (!NumberOfPages || !PageArray || (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == (MEM_LARGE_PAGES | MEM_4MB_PAGES) ||
        ((flAllocationType & MEM_4MB_PAGES) && (*NumberOfPages & 63)))
    {
        if (NumberOfPages)
            *NumberOfPages = 0;

        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    ULONG_PTR PagesAllocated = 0;
    ULONG_PTR PagesRequested = *NumberOfPages;
    ULONG_PTR PagesPerRegion = (flAllocationType & MEM_4MB_PAGES) ? 64 : 1;
    AcquireSRWLockExclusive(&XwpPhysicalMemoryLock);

    for (ULONG_PTR i = 0; (i + PagesPerRegion - 1) < XwpPhysicalPages.size() && PagesAllocated < PagesRequested;)
    {
        BOOL FoundContiguousPages = TRUE;

        for (ULONG_PTR j = 0; j < PagesPerRegion; j++)
        {
            if (XwpPhysicalPages[i + j])
            {
                FoundContiguousPages = FALSE;
                break;
            }
        }

        if (!FoundContiguousPages)
        {
            i++;
            continue;
        }

        for (ULONG_PTR j = 0; j < PagesPerRegion; j++)
        {
            XwpPhysicalPages[i + j] = true;
            PageArray[PagesAllocated++] = i + j;
        }

        i += PagesPerRegion;
    }

    ReleaseSRWLockExclusive(&XwpPhysicalMemoryLock);
    *NumberOfPages = PagesAllocated;
    SetLastError(PagesAllocated > 0 ? ERROR_SUCCESS : ERROR_OUTOFMEMORY);
    return PagesAllocated > 0;
}

EXTERN_C BOOL __stdcall FreeTitlePhysicalPages(HANDLE hProcess, ULONG_PTR NumberOfPages, PULONG_PTR PageArray)
{
    UNREFERENCED_PARAMETER(hProcess);

    if (NumberOfPages && !PageArray)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    AcquireSRWLockExclusive(&XwpPhysicalMemoryLock);

    for (ULONG_PTR i = 0; i < NumberOfPages; i++)
        XwpPhysicalPages[PageArray[i]] = false;

    ReleaseSRWLockExclusive(&XwpPhysicalMemoryLock);
    SetLastError(ERROR_SUCCESS);
    return TRUE;
}

EXTERN_C LPVOID __stdcall EraVirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType,
                                            DWORD flProtect)
{
    if (flAllocationType & MEM_GRAPHICS)
    {
        flProtect = PAGE_READONLY;
    }

    MEM_ADDRESS_REQUIREMENTS AddrRq;
    AddrRq.LowestStartingAddress = nullptr;
    AddrRq.HighestEndingAddress = nullptr;
    AddrRq.Alignment = 0;

    MEM_EXTENDED_PARAMETER ExtParam;
    ExtParam.Type = MemExtendedParameterAddressRequirements;
    ExtParam.Reserved = 0;
    ExtParam.Pointer = &AddrRq;

    // If true, the memory can be used with MapTitlePhysicalPages and D3DMapEsramMemory.
    // These allocations go through a file mapping and therefore get handled differently.
    BOOL bMappable = FALSE;
    MAPPABLE_MEM Mappable = {};
    SIZE_T dwPageSize = PAGE_SIZE_4KB;

    if (flAllocationType & (MEM_RESERVE | MEM_TOP_DOWN))
    {
        // If MEM_LARGE_PAGES or MEM_4MB_PAGES is specified, the memory is mappable.
        bMappable = !!(flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES));

        if (!lpAddress)
        {
            if (flAllocationType & MEM_4MB_PAGES)
                AddrRq.Alignment = PAGE_SIZE_4MB;

            // If we're reserving memory, ERA will use specific memory ranges.
            // TODO: Does any set of flags use 1 TiB -> 2 TiB? Need to test on hardware.
            if (flAllocationType & MEM_GRAPHICS) // 4 GiB -> 1 TiB
            {
                AddrRq.LowestStartingAddress = (PVOID)0x100000000ULL;
                AddrRq.HighestEndingAddress = (PVOID)0xFFFFFFFFFFULL;
            }
            else if (flAllocationType & MEM_TITLE) // 2 TiB -> 4 TiB
            {
                AddrRq.LowestStartingAddress = (PVOID)0x40000000000ULL;
                AddrRq.HighestEndingAddress = (PVOID)0x7FFFFFFFFFFULL;
            }
            else // 4 TiB -> 8 TiB
            {
                AddrRq.LowestStartingAddress = (PVOID)0x20000000000ULL;
                AddrRq.HighestEndingAddress = (PVOID)0x3FFFFFFFFFFULL;
            }
        }
    }
    else if (lpAddress && (flAllocationType & MEM_COMMIT))
    {
        AcquireSRWLockShared(&XwpMappableLock);
        bMappable = !!MappableQuery(lpAddress, &Mappable);
        ReleaseSRWLockShared(&XwpMappableLock);
    }

    if (!bMappable)
        return VirtualAlloc2(hProcess, lpAddress, dwSize, flAllocationType & MEM_MASK, flProtect & PAGE_MASK, &ExtParam,
                             1);

    if ((flAllocationType & MEM_4MB_PAGES) || Mappable.Is4MBPages)
        dwPageSize = PAGE_SIZE_4MB;
    else
        dwPageSize = PAGE_SIZE_64K;

    dwSize = (dwSize + (dwPageSize - 1)) & ~(dwPageSize - 1);
    lpAddress = (LPVOID)((ULONG_PTR)lpAddress & ~(dwPageSize - 1));

    if (flAllocationType & (MEM_RESERVE | MEM_TOP_DOWN))
    {
        Mappable = {dwSize, !!(flAllocationType & MEM_4MB_PAGES)};
        lpAddress = VirtualAlloc2(hProcess, lpAddress, dwSize,
                                  MEM_RESERVE | MEM_RESERVE_PLACEHOLDER | (flAllocationType & MEM_TOP_DOWN),
                                  PAGE_NOACCESS, &ExtParam, 1);

        if (lpAddress)
        {
            // Split the placeholder by the physical page size to enable individual mappings.
            // This comes with its own caveats. MEM_COMMIT and other Virtual* functions must
            // be aware of mappable memory allocations and handle them appropriately.
            for (SIZE_T dwOffset = dwPageSize; dwOffset < dwSize; dwOffset += dwPageSize)
                VirtualFreeEx(hProcess, (LPBYTE)lpAddress + dwOffset, dwPageSize,
                              MEM_RELEASE | MEM_PRESERVE_PLACEHOLDER);

            AcquireSRWLockExclusive(&XwpMappableLock);
            XwpMappables[(ULONG_PTR)lpAddress] = Mappable;
            ReleaseSRWLockExclusive(&XwpMappableLock);
        }
    }

    if (lpAddress && (flAllocationType & MEM_COMMIT))
    {
        HANDLE hMap = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE,
                                         SEC_RESERVE, dwSize, nullptr, nullptr, 0);

        if (!hMap)
        {
            SetLastError(ERROR_OUTOFMEMORY);
            return nullptr;
        }

        for (SIZE_T dwOffset = 0; dwOffset < dwSize; dwOffset += dwPageSize)
        {
            LPVOID PageAddress = (LPBYTE)lpAddress + dwOffset;
            MapViewOfFile3(hMap, hProcess, PageAddress, dwOffset, dwPageSize, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE,
                           nullptr, 0);
            VirtualAlloc2(hProcess, PageAddress, dwPageSize, MEM_COMMIT, flProtect & PAGE_MASK, nullptr, 0);
        }

        CloseHandle(hMap);
    }

    return lpAddress;
}

EXTERN_C LPVOID __stdcall EraVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    return EraVirtualAllocEx(GetCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
}

EXTERN_C BOOL __stdcall EraVirtualFreeEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    LPVOID AllocationBase;
    MAPPABLE_MEM Mappable;
    AcquireSRWLockShared(&XwpMappableLock);
    AllocationBase = MappableQuery(lpAddress, &Mappable);
    ReleaseSRWLockShared(&XwpMappableLock);

    // If we have a mappable allocation, we need to ensure it is unmapped first.
    if (AllocationBase)
    {
        ULONG_PTR PageSize = Mappable.Is4MBPages ? PAGE_SIZE_4MB : PAGE_SIZE_64K;
        ULONG_PTR BasePage = (ULONG_PTR)lpAddress & ~(PageSize - 1);

        if (dwFreeType == MEM_RELEASE && (AllocationBase != lpAddress || dwSize))
            return FALSE;

        if (dwFreeType == MEM_RELEASE || (dwFreeType == MEM_DECOMMIT && !dwSize))
            dwSize = Mappable.RegionSize - ((ULONG_PTR)BasePage - (ULONG_PTR)AllocationBase);

        ULONG_PTR LastPage = ((ULONG_PTR)lpAddress + dwSize) & ~(PageSize - 1);

        for (ULONG_PTR BaseAddress = BasePage; BaseAddress <= LastPage; BaseAddress += PageSize)
            UnmapViewOfFile2(hProcess, (PVOID)BaseAddress, MEM_PRESERVE_PLACEHOLDER);

        if (dwFreeType == MEM_DECOMMIT)
            return TRUE;

        BOOL Status;
        VirtualFreeEx(hProcess, lpAddress, dwSize, MEM_RELEASE | MEM_COALESCE_PLACEHOLDERS);
        AcquireSRWLockExclusive(&XwpMappableLock);
        Status = VirtualFreeEx(hProcess, lpAddress, 0, MEM_RELEASE);
        if (Status)
            XwpMappables.erase((ULONG_PTR)AllocationBase);
        ReleaseSRWLockExclusive(&XwpMappableLock);
        return Status;
    }

    return VirtualFreeEx(hProcess, lpAddress, dwSize, dwFreeType);
}

EXTERN_C BOOL __stdcall EraVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    return EraVirtualFreeEx(GetCurrentProcess(), lpAddress, dwSize, dwFreeType);
}

EXTERN_C SIZE_T __stdcall EraVirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer,
                                            SIZE_T dwLength)
{
    LPVOID AllocationBase;
    MAPPABLE_MEM Mappable;

    if (!lpBuffer || dwLength < sizeof(*lpBuffer))
        return 0;

    AcquireSRWLockShared(&XwpMappableLock);
    AllocationBase = MappableQuery(lpAddress, &Mappable);
    ReleaseSRWLockShared(&XwpMappableLock);

    // Mappable memory requires special handling because of placeholder splits.
    // VirtualQuery will normally only report on pages that belong to the same allocation.
    if (AllocationBase)
    {
        MEMORY_BASIC_INFORMATION Region;
        ULONG_PTR PageSize = Mappable.Is4MBPages ? PAGE_SIZE_2MB : PAGE_SIZE_4KB;
        ULONG_PTR BasePage = (ULONG_PTR)lpAddress & ~(PageSize - 1);
        ULONG_PTR ByteSize = Mappable.RegionSize - ((ULONG_PTR)BasePage - (ULONG_PTR)AllocationBase);
        ULONG_PTR LastPage = ((ULONG_PTR)lpAddress + ByteSize) & ~(PageSize - 1);

        if (!VirtualQueryEx(hProcess, (LPCVOID)BasePage, &Region, sizeof(Region)))
            return 0;

        lpBuffer->BaseAddress = (PVOID)BasePage;
        lpBuffer->AllocationBase = AllocationBase;
        lpBuffer->AllocationProtect = Region.AllocationProtect;
        lpBuffer->PartitionId = Region.PartitionId;
        lpBuffer->RegionSize = PageSize;
        lpBuffer->State = Region.State;
        lpBuffer->Protect = Region.Protect;
        lpBuffer->Type = Region.Type;

        for (ULONG_PTR Page = BasePage + PageSize; Page <= LastPage; Page += PageSize)
        {
            if (!VirtualQueryEx(hProcess, (LPCVOID)Page, &Region, sizeof(Region)))
                break;

            if (Region.State != lpBuffer->State || Region.Protect != lpBuffer->Protect)
                break;

            if (Region.RegionSize < PageSize)
            {
                lpBuffer->RegionSize += Region.RegionSize;
                break;
            }

            lpBuffer->RegionSize += PageSize;
        }

        return sizeof(*lpBuffer);
    }

    return VirtualQueryEx(hProcess, lpAddress, lpBuffer, dwLength);
}

EXTERN_C SIZE_T __stdcall EraVirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
    return EraVirtualQueryEx(GetCurrentProcess(), lpAddress, lpBuffer, dwLength);
}

EXTERN_C BOOL __stdcall EraVirtualProtectEx(_In_ HANDLE hProcess, _In_ LPVOID lpAddress, _In_ SIZE_T dwSize,
                                            _In_ DWORD flNewProtect, _Out_opt_ PDWORD lpflOldProtect)
{
    DWORD flOldProtect;
    LPVOID AllocationBase;
    MAPPABLE_MEM Mappable;
    AcquireSRWLockShared(&XwpMappableLock);
    AllocationBase = MappableQuery(lpAddress, &Mappable);
    ReleaseSRWLockShared(&XwpMappableLock);

    // Mappable memory requires special handling because of placeholder splits.
    // VirtualProtect will normally only work on pages that belong to the same allocation.
    if (AllocationBase)
    {
        // TODO: Validate all pages are committed before changing protections
        ULONG_PTR PageSize = Mappable.Is4MBPages ? PAGE_SIZE_2MB : PAGE_SIZE_4KB;
        ULONG_PTR BasePage = (ULONG_PTR)lpAddress & ~(PageSize - 1);
        ULONG_PTR LastPage = ((ULONG_PTR)lpAddress + dwSize) & ~(PageSize - 1);
        BOOL Status = VirtualProtectEx(hProcess, (LPVOID)BasePage, PageSize, flNewProtect,
                                       lpflOldProtect ? lpflOldProtect : &flOldProtect);

        for (ULONG_PTR Page = BasePage + PageSize; Page <= LastPage; Page += PageSize)
            Status |= VirtualProtectEx(hProcess, (LPVOID)Page, PageSize, flNewProtect, &flOldProtect);

        return Status;
    }

    return VirtualProtectEx(hProcess, lpAddress, dwSize, flNewProtect, lpflOldProtect ? lpflOldProtect : &flOldProtect);
}

EXTERN_C BOOL __stdcall EraVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
    return EraVirtualProtectEx(GetCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

EXTERN_C PVOID __stdcall MapTitlePhysicalPages(PVOID VirtualAddress, ULONG_PTR NumberOfPages, DWORD flAllocationType,
                                               DWORD flProtect, PULONG_PTR PageArray)
{
    // TODO: Validate that PageArray contains contiguous 4MB blocks of 64K pages for MEM_4MB_PAGES

    if (!PageArray || (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == (MEM_LARGE_PAGES | MEM_4MB_PAGES) ||
        ((flAllocationType & MEM_4MB_PAGES) && (NumberOfPages & 63)))
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return nullptr;
    }

    ULONG_PTR dwPageSize = (flAllocationType & MEM_LARGE_PAGES) ? PAGE_SIZE_64K : PAGE_SIZE_4MB;
    ULONG_PTR RegionSize = (flAllocationType & MEM_4MB_PAGES) ? 64 : 1;

    if (VirtualAddress && ((ULONG_PTR)VirtualAddress & (dwPageSize - 1)))
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return nullptr;
    }

    if (MEMORY_BASIC_INFORMATION mbi;
        !VirtualAddress || !VirtualQuery(VirtualAddress, &mbi, sizeof(mbi)) || mbi.State == MEM_FREE)
    {
        VirtualAddress = EraVirtualAlloc(VirtualAddress, NumberOfPages * PAGE_SIZE_64K, MEM_RESERVE | flAllocationType,
                                         PAGE_NOACCESS);

        if (!VirtualAddress)
        {
            return nullptr;
        }
    }

    for (ULONG_PTR i = 0; i < NumberOfPages; i += RegionSize)
    {
        ULONG_PTR PhysicalOffset = PAGE_SIZE_64K * PageArray[i];
        PVOID PageVirtualAddress = (PVOID)((ULONG_PTR)VirtualAddress + i * PAGE_SIZE_64K);
        UnmapViewOfFile2(GetCurrentProcess(), PageVirtualAddress, MEM_PRESERVE_PLACEHOLDER);
        MapViewOfFile3(XwpPhysicalMemory, nullptr, PageVirtualAddress, PhysicalOffset, dwPageSize,
                       MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0);
        VirtualAlloc2(nullptr, PageVirtualAddress, dwPageSize, MEM_COMMIT, flProtect & PAGE_MASK, nullptr, 0);
    }

    SetLastError(ERROR_SUCCESS);
    return VirtualAddress;
}

EXTERN_C HRESULT __stdcall MapTitleEsramPages(PVOID VirtualAddress, UINT NumberOfPages, DWORD flAllocationType,
                                              UINT const *PageArray)
{
    if (!VirtualAddress || (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == (MEM_LARGE_PAGES | MEM_4MB_PAGES))
    {
        return E_INVALIDARG;
    }

    SIZE_T dwPageSize = (flAllocationType & MEM_LARGE_PAGES) ? PAGE_SIZE_64K : PAGE_SIZE_4MB;

    if (NumberOfPages * dwPageSize > MEM_ESRAM_SIZE)
        return E_INVALIDARG;

    if ((ULONG_PTR)VirtualAddress & (dwPageSize - 1))
        return E_INVALIDARG;

    if (!PageArray)
    {
        for (ULONG_PTR dwOffset = 0; dwOffset < NumberOfPages * dwPageSize; dwOffset += dwPageSize)
        {
            PVOID PageAddress = (PVOID)((ULONG_PTR)VirtualAddress + dwOffset);
            UnmapViewOfFile2(GetCurrentProcess(), PageAddress, MEM_PRESERVE_PLACEHOLDER);
        }

        return S_OK;
    }

    for (ULONG_PTR i = 0; i < NumberOfPages; i++)
    {
        ULONG_PTR PhysicalOffset = PageArray[i] * dwPageSize;
        PVOID PageVirtualAddress = (PVOID)((ULONG_PTR)VirtualAddress + i * dwPageSize);

        if (PhysicalOffset + dwPageSize > MEM_ESRAM_SIZE)
            return E_INVALIDARG;

        MapViewOfFile3(XwpEsramMemory, nullptr, PageVirtualAddress, PhysicalOffset, dwPageSize, MEM_REPLACE_PLACEHOLDER,
                       PAGE_READWRITE, nullptr, 0);
        VirtualAlloc2(nullptr, PageVirtualAddress, dwPageSize, MEM_COMMIT, PAGE_READWRITE, nullptr, 0);
    }

    return S_OK;
}

#define XALLOC_IS_GRAPHICS(Attributes) ((BOOL)(((Attributes) & 0x1E0000000ULL) != 0))

EXTERN_C PVOID __stdcall XMemAllocDefault(SIZE_T dwSize, ULONGLONG dwAttributes)
{
    auto attr = XALLOC_ATTRIBUTES{dwAttributes};

    if (attr.s.dwMemoryType != XALLOC_MEMTYPE_HEAP)
    {
        DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;

        if (attr.s.dwPageSize == XALLOC_PAGESIZE_4MB)
            flAllocationType |= MEM_4MB_PAGES;
        else if (attr.s.dwPageSize == XALLOC_PAGESIZE_4KB)
            flAllocationType |= MEM_LARGE_PAGES;

        if (attr.s.dwMemoryType >= XALLOC_MEMTYPE_GRAPHICS_1 &&
            attr.s.dwMemoryType <= XALLOC_MEMTYPE_GRAPHICS_6)
        {
            flAllocationType |= MEM_GRAPHICS;
        }

        return EraVirtualAlloc(nullptr, dwSize, flAllocationType, PAGE_READWRITE);
    }

    void *ptr = _aligned_malloc(dwSize, 1ULL << max(4, attr.s.dwAlignment));

    if (ptr)
        memset(ptr, 0, dwSize);

    return ptr;
}

EXTERN_C void __stdcall XMemFreeDefault(PVOID lpAddress, ULONGLONG dwAttributes)
{
    if (XALLOC_IS_GRAPHICS(dwAttributes))
    {
        EraVirtualFree(lpAddress, 0, MEM_RELEASE);
        return;
    }

    _aligned_free(lpAddress);
}

EXTERN_C PVOID __stdcall XMemAlloc(SIZE_T dwSize, ULONGLONG dwAttributes)
{
    return XmpAllocRoutine(dwSize, dwAttributes);
}

EXTERN_C void __stdcall XMemFree(PVOID lpAddress, ULONGLONG dwAttributes)
{
    return XmpFreeRoutine(lpAddress, dwAttributes);
}

EXTERN_C void __stdcall XMemSetAllocationHooks(PXMEMALLOC_ROUTINE pAllocRoutine, PXMEMFREE_ROUTINE pFreeRoutine)
{
    EnterCriticalSection(&XmpAllocationHookLock);

    if (pAllocRoutine)
    {
        XmpAllocRoutine = pAllocRoutine;
        XmpFreeRoutine = pFreeRoutine;
    }
    else
    {
        XmpAllocRoutine = XMemAllocDefault;
        XmpFreeRoutine = XMemFreeDefault;
    }

    LeaveCriticalSection(&XmpAllocationHookLock);
}

EXTERN_C void __stdcall XMemCheckDefaultHeaps()
{
    // This function is empty in kernelx.dll
}

EXTERN_C BOOL __stdcall XMemSetAllocationHysteresis()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C SIZE_T __stdcall XMemGetAllocationHysteresis()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return MAXSIZE_T;
}

EXTERN_C BOOL __stdcall XMemPreallocateFreeSpace()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C BOOL __stdcall XMemGetAllocationStatistics()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

EXTERN_C HANDLE __stdcall XMemGetAuxiliaryTitleMemory()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return nullptr;
}

EXTERN_C void __stdcall XMemReleaseAuxiliaryTitleMemory(_In_opt_ HANDLE hHandle)
{
    UNREFERENCED_PARAMETER(hHandle);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
}


void FixRelativePath(LPCWSTR &lpFileName)
{
    static std::wstring convert{};
    std::wstring_view fileName(lpFileName);

    if (fileName.size() == 0)
        return;

    int length = fileName.length();

    if (fileName[0] == '.' && fileName[1] == '\\')
    {
        static std::wstring trimPath{};
        trimPath = fileName.substr(2);
        fileName = trimPath.data();
        convert = std::filesystem::current_path().c_str();
        if (convert.back() != '\\')
        {
            convert.append(L"\\");
        }
        convert.append(fileName);
        std::replace(convert.begin(), convert.end(), L'\\', L'/');
        std::replace(convert.begin(), convert.end(), L'//', L'/');

        lpFileName = convert.data();
        return;
    }
    if (fileName[1] != ':')
    {
        convert = std::filesystem::current_path().c_str();
        convert.append(L"\\");
        convert.append(fileName);
        std::replace(convert.begin(), convert.end(), L'\\', L'/');
        std::replace(convert.begin(), convert.end(), L'//', L'/');

        lpFileName = convert.data();
    }
    else if ((fileName[0] == 'G' || fileName[0] == 'g') && fileName[1] == ':')
    {
        static std::wstring trimPath{};
        trimPath = fileName.substr(2);
        fileName = trimPath.data();
        convert = std::filesystem::current_path().c_str();
        convert.append(fileName);
        std::replace(convert.begin(), convert.end(), L'\\', L'/');
        std::replace(convert.begin(), convert.end(), L'//', L'/');

        lpFileName = convert.data();
    }
    else if ((fileName[0] == 'T' || fileName[0] == 't') && fileName[1] == ':')
    {

        static std::wstring trimPath{};
        trimPath = fileName.substr(2);
        fileName = trimPath.data();
        convert = winrt::Windows::Storage::ApplicationData::Current().TemporaryFolder().Path();
        convert.append(fileName);
        std::replace(convert.begin(), convert.end(), L'\\', L'/');
        std::replace(convert.begin(), convert.end(), L'//', L'/');

        lpFileName = convert.data();
    }
}

EXTERN_C HANDLE __stdcall EraCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    // We do this so we have a Logan event copy, so we know when AcpHal tries to communicate via DeviceIoControl.
    if (wcscmp(lpFileName, L"\\\\?\\acpi_hal#logan#0#{f764922a-de30-40a5-a66e-c46cb191a1cd}") == 0)
    {
        HANDLE Event = CreateEventW(NULL, FALSE, FALSE, NULL);
        LoganHandle = Event;

        LoganInit();
        SetLastError(ERROR_SUCCESS);

        return LoganHandle;
    }

    static std::wstring convert{};
    std::wstring_view fileName(lpFileName);

    int length = fileName.length();
    if (fileName[0] == '/')
    {
        static std::wstring trimPath{};
        trimPath = fileName.substr(1);
        fileName = trimPath.data();
        convert = std::filesystem::current_path().c_str();
        convert.append(L"\\");
        convert.append(fileName);

        lpFileName = convert.data();
    }
    else if (fileName[0] == '\\')
    {
    }
    else if (fileName[length - 1] == '/')
    {
        convert = std::filesystem::current_path().c_str();
        convert.append(L"\\");
        convert.append(lpFileName);
        std::replace(convert.begin(), convert.end(), L'/', L'\\');
        lpFileName = convert.c_str();
    }
    else
    {
        FixRelativePath(lpFileName);
    }

    HANDLE Result = TrueCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition,
                                    dwFlagsAndAttributes, hTemplateFile);

    return Result;
}

EXTERN_C HANDLE __stdcall EraCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    USES_CONVERSION;
    LPCWSTR FileName = A2W(lpFileName);
    FixRelativePath(FileName);

    HANDLE Result = TrueCreateFileW(FileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition,
                                    dwFlagsAndAttributes, hTemplateFile);

    return Result;
}

EXTERN_C HANDLE __stdcall EraCreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         DWORD dwCreationDisposition, LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams)
{
    FixRelativePath(lpFileName);
    HANDLE Result = TrueCreateFile2(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, pCreateExParams);

    return Result;
}

EXTERN_C BOOL __stdcall EraCreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    USES_CONVERSION;
    LPCWSTR PathName = A2W(lpPathName);
    FixRelativePath(PathName);
    BOOL Result = TrueCreateDirectoryW(PathName, lpSecurityAttributes);

    return Result;
}

EXTERN_C BOOL __stdcall EraCreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    FixRelativePath(lpPathName);
    BOOL Result = TrueCreateDirectoryW(lpPathName, lpSecurityAttributes);

    return Result;
}

EXTERN_C HMODULE __stdcall EraLoadLibraryExA(LPCSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags)
{
    USES_CONVERSION;
    LPCWSTR LibName = A2W(lpLibFileName);

    static std::wstring convert{};
    std::wstring_view fileName(LibName);

    if (fileName.size() != 0 && fileName[0] == 'G' && fileName[1] == ':')
    {
        static std::wstring trimPath{};
        trimPath = fileName.substr(2);
        fileName = trimPath.data();
        convert = std::filesystem::current_path().c_str();
        convert.append(fileName);
    }

    HMODULE result = TrueLoadLibraryExW(LibName, hFile, dwFlags);

    PatchNeededImports(result, GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z",
                       GetActivationFactoryRedirect);
    return result;
}

EXTERN_C HMODULE __stdcall EraLoadLibraryW(LPCWSTR lpLibFileName)
{
    static std::wstring convert{};
    std::wstring_view fileName(lpLibFileName);

    if (fileName[0] == 'G' && fileName[1] == ':' && fileName.size() != 0)
    {

        static std::wstring trimPath{};
        trimPath = fileName.substr(2);
        fileName = trimPath.data();
        convert = std::filesystem::current_path().c_str();
        convert.append(fileName);

        lpLibFileName = convert.data();
    }

    HMODULE result = TrueLoadLibraryW(lpLibFileName);
    PatchNeededImports(result, GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z",
                       GetActivationFactoryRedirect);
    return result;
}

EXTERN_C DWORD __stdcall EraGetFileAttributesW(LPCWSTR lpFileName)
{
    FixRelativePath(lpFileName);
    return TrueGetFileAttributesW(lpFileName);
}

EXTERN_C BOOL __stdcall EraGetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
                                                LPVOID lpFileInformation)
{
    FixRelativePath(lpFileName);
    return TrueGetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation);
}
EXTERN_C DWORD __stdcall EraGetFileAttributesA(LPCSTR lpFileName)
{
    USES_CONVERSION;
    LPCWSTR FileName = A2W(lpFileName);
    FixRelativePath(FileName);

    DWORD Result = TrueGetFileAttributesW(FileName);

    return Result;
}

EXTERN_C HANDLE __stdcall EraFindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
    FixRelativePath(lpFileName);
    return TrueFindFirstFileW(lpFileName, lpFindFileData);
}

EXTERN_C BOOL __stdcall EraDeleteFileW(LPCWSTR lpFileName)
{
    FixRelativePath(lpFileName);
    return TrueDeleteFileW(lpFileName);
}

EXTERN_C HMODULE __stdcall EraLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    FixRelativePath(lpLibFileName);
    return TrueLoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

EXTERN_C BOOL __stdcall EraSetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes)
{
    USES_CONVERSION;
    LPCWSTR WideFileName = A2W(lpFileName);
    FixRelativePath(WideFileName);
    
    LPCSTR FileName = W2A(WideFileName);

    BOOL Result = TrueSetFileAttributesA(FileName, dwFileAttributes);

    return Result;
}

EXTERN_C HANDLE __stdcall EraFindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    USES_CONVERSION;
    LPCWSTR WideFileName = A2W(lpFileName);
    FixRelativePath(WideFileName);
    
    LPCSTR FileName = W2A(WideFileName);

    HANDLE Result = TrueFindFirstFileA(FileName, lpFindFileData);

    return Result;
}

EXTERN_C BOOL __stdcall EraFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
    BOOL Result = TrueFindNextFileA(hFindFile, lpFindFileData);

    return Result;
}

EXTERN_C BOOL __stdcall EraFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
    BOOL Result = TrueFindNextFileW(hFindFile, lpFindFileData);

    return Result;
}

EXTERN_C BOOL __stdcall EraGetFileInformationByHandleEx(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize)
{
    BOOL Result = TrueGetFileInformationByHandleEx(hFile, FileInformationClass, lpFileInformation, dwBufferSize);

    return Result;
}

EXTERN_C BOOL __stdcall EraReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    return TrueReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

EXTERN_C BOOL __stdcall EraWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    return TrueWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

EXTERN_C void __stdcall NtEnable32BitProcess(HANDLE hProcess, UINT Flags, LPVOID lpAddress, UINT16 Unknown)
{
    //TODO
    printf("TODO: NtEnable32BitProcess\n");
    lpAddress = EraVirtualAllocEx(hProcess, (LPVOID)0x100000000, 0x100000000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //In theory, 0x100000000 is the starting address?
}

EXTERN_C FARPROC _stdcall EraGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (hModule == ntdll)
    {
        if (!strcmp(lpProcName, "NtEnable32BitProcess"))
        {
            return (FARPROC)NtEnable32BitProcess;
        }
    }

    return TrueGetProcAddress(hModule, lpProcName);
}

HRESULT __stdcall EraCoCreateInstanceEx(REFCLSID Clsid, IUnknown *punkOuter, DWORD dwClsCtx, COSERVERINFO *pServerInfo, DWORD dwCount, MULTI_QI *pResults)
{
    if (Clsid == __uuidof(IPersistentLocalStorageManagerEra))
    {
        pResults->hr = S_OK;
        pResults->pIID = &Clsid;
        pResults->pItf = new PersistentLocalStorageManagerEra();
        return S_OK;
    }

    return TrueCoCreateInstanceEx(Clsid, punkOuter, dwClsCtx, pServerInfo, dwCount, pResults);
}

// Imports
#pragma comment(lib, "onecore.lib")
#pragma comment(lib, "kernel32.lib")

// Exports
#pragma comment(linker, "/export:AcquireSRWLockExclusive=kernel32.AcquireSRWLockExclusive")
#pragma comment(linker, "/export:AcquireSRWLockShared=kernel32.AcquireSRWLockShared")
#pragma comment(linker, "/export:AddVectoredContinueHandler=kernel32.AddVectoredContinueHandler")
#pragma comment(linker, "/export:AddVectoredExceptionHandler=kernel32.AddVectoredExceptionHandler")
#pragma comment(linker, "/export:AllocateTitlePhysicalPages")
#pragma comment(linker, "/export:AppPolicyGetProcessTerminationMethod=kernel32.AppPolicyGetProcessTerminationMethod")
#pragma comment(linker, "/export:AppPolicyGetShowDeveloperDiagnostic=kernel32.AppPolicyGetShowDeveloperDiagnostic")
#pragma comment(linker, "/export:AppPolicyGetThreadInitializationType=kernel32.AppPolicyGetThreadInitializationType")
#pragma comment(linker, "/export:AppPolicyGetWindowingModel=kernel32.AppPolicyGetWindowingModel")
#pragma comment(linker, "/export:AreFileApisANSI=kernel32.AreFileApisANSI")
#pragma comment(linker, "/export:Beep=kernel32.Beep")
#pragma comment(linker, "/export:BindIoCompletionCallback=kernel32.BindIoCompletionCallback")
#pragma comment(linker, "/export:CallbackMayRunLong=kernel32.CallbackMayRunLong")
#pragma comment(linker, "/export:CancelIo=kernel32.CancelIo")
#pragma comment(linker, "/export:CancelIoEx=kernel32.CancelIoEx")
#pragma comment(linker, "/export:CancelSynchronousIo=kernel32.CancelSynchronousIo")
#pragma comment(linker, "/export:CancelThreadpoolIo=kernel32.CancelThreadpoolIo")
#pragma comment(linker, "/export:CancelWaitableTimer=kernel32.CancelWaitableTimer")
#pragma comment(linker, "/export:CloseHandle=kernel32.CloseHandle")
#pragma comment(linker, "/export:CloseThreadpool=kernel32.CloseThreadpool")
#pragma comment(linker, "/export:CloseThreadpoolCleanupGroup=kernel32.CloseThreadpoolCleanupGroup")
#pragma comment(linker, "/export:CloseThreadpoolCleanupGroupMembers=kernel32.CloseThreadpoolCleanupGroupMembers")
#pragma comment(linker, "/export:CloseThreadpoolIo=kernel32.CloseThreadpoolIo")
#pragma comment(linker, "/export:CloseThreadpoolTimer=kernel32.CloseThreadpoolTimer")
#pragma comment(linker, "/export:CloseThreadpoolWait=kernel32.CloseThreadpoolWait")
#pragma comment(linker, "/export:CloseThreadpoolWork=kernel32.CloseThreadpoolWork")
#pragma comment(linker, "/export:CompareFileTime=kernel32.CompareFileTime")
#pragma comment(linker, "/export:CompareStringEx=kernel32.CompareStringEx")
#pragma comment(linker, "/export:CompareStringOrdinal=kernel32.CompareStringOrdinal")
#pragma comment(linker, "/export:CompareStringW=kernel32.CompareStringW")
#pragma comment(linker, "/export:ConnectNamedPipe=kernel32.ConnectNamedPipe")
#pragma comment(linker, "/export:ConvertFiberToThread=kernel32.ConvertFiberToThread")
#pragma comment(linker, "/export:ConvertThreadToFiber=kernel32.ConvertThreadToFiber")
#pragma comment(linker, "/export:ConvertThreadToFiberEx=kernel32.ConvertThreadToFiberEx")
#pragma comment(linker, "/export:CopyContext=kernel32.CopyContext")
#pragma comment(linker, "/export:CopyFile2=kernel32.CopyFile2")
#pragma comment(linker, "/export:CopyMemoryNonTemporal=kernelbase.CopyMemoryNonTemporal")
#pragma comment(linker, "/export:CreateDirectoryA=kernel32.CreateDirectoryA")
#pragma comment(linker, "/export:CreateDirectoryW=kernel32.CreateDirectoryW")
#pragma comment(linker, "/export:CreateEventA=kernel32.CreateEventA")
#pragma comment(linker, "/export:CreateEventExA=kernel32.CreateEventExA")
#pragma comment(linker, "/export:CreateEventExW=kernel32.CreateEventExW")
#pragma comment(linker, "/export:CreateEventW=kernel32.CreateEventW")
#pragma comment(linker, "/export:CreateFiber=kernel32.CreateFiber")
#pragma comment(linker, "/export:CreateFiberEx=kernel32.CreateFiberEx")
#pragma comment(linker, "/export:CreateFile2=kernel32.CreateFile2")
#pragma comment(linker, "/export:CreateFileA=kernel32.CreateFileA")
#pragma comment(linker, "/export:CreateFileMappingW=kernel32.CreateFileMappingW")
#pragma comment(linker, "/export:CreateFileW=kernel32.CreateFileW")
#pragma comment(linker, "/export:CreateHardLinkW=kernel32.CreateHardLinkW")
#pragma comment(linker, "/export:CreateIoCompletionPort=kernel32.CreateIoCompletionPort")
#pragma comment(linker, "/export:CreateMutexA=kernel32.CreateMutexA")
#pragma comment(linker, "/export:CreateMutexExA=kernel32.CreateMutexExA")
#pragma comment(linker, "/export:CreateMutexExW=kernel32.CreateMutexExW")
#pragma comment(linker, "/export:CreateMutexW=kernel32.CreateMutexW")
#pragma comment(linker, "/export:CreateNamedPipeW=kernel32.CreateNamedPipeW")
#pragma comment(linker, "/export:CreatePipe=kernel32.CreatePipe")
#pragma comment(linker, "/export:CreateProcessA=kernel32.CreateProcessA")
#pragma comment(linker, "/export:CreateProcessW=kernel32.CreateProcessW")
#pragma comment(linker, "/export:CreateRemoteThread=kernel32.CreateRemoteThread")
#pragma comment(linker, "/export:CreateRemoteThreadEx=kernel32.CreateRemoteThreadEx")
#pragma comment(linker, "/export:CreateSemaphoreA=kernel32.CreateSemaphoreA")
#pragma comment(linker, "/export:CreateSemaphoreExA=kernel32.CreateSemaphoreExA")
#pragma comment(linker, "/export:CreateSemaphoreExW=kernel32.CreateSemaphoreExW")
#pragma comment(linker, "/export:CreateSemaphoreW=kernel32.CreateSemaphoreW")
#pragma comment(linker, "/export:CreateSymbolicLinkW=kernel32.CreateSymbolicLinkW")
#pragma comment(linker, "/export:CreateThread=kernel32.CreateThread")
#pragma comment(linker, "/export:CreateThreadpool=kernel32.CreateThreadpool")
#pragma comment(linker, "/export:CreateThreadpoolCleanupGroup=kernel32.CreateThreadpoolCleanupGroup")
#pragma comment(linker, "/export:CreateThreadpoolIo=kernel32.CreateThreadpoolIo")
#pragma comment(linker, "/export:CreateThreadpoolTimer=kernel32.CreateThreadpoolTimer")
#pragma comment(linker, "/export:CreateThreadpoolWait=kernel32.CreateThreadpoolWait")
#pragma comment(linker, "/export:CreateThreadpoolWork=kernel32.CreateThreadpoolWork")
#pragma comment(linker, "/export:CreateWaitableTimerA=kernel32.CreateWaitableTimerA")
#pragma comment(linker, "/export:CreateWaitableTimerExA=kernel32.CreateWaitableTimerExA")
#pragma comment(linker, "/export:CreateWaitableTimerExW=kernel32.CreateWaitableTimerExW")
#pragma comment(linker, "/export:CreateWaitableTimerW=kernel32.CreateWaitableTimerW")
#pragma comment(linker, "/export:DebugBreak=kernel32.DebugBreak")
#pragma comment(linker, "/export:DecodePointer=kernel32.DecodePointer")
#pragma comment(linker, "/export:DecodeSystemPointer=kernel32.DecodeSystemPointer")
#pragma comment(linker, "/export:DeleteCriticalSection=kernel32.DeleteCriticalSection")
#pragma comment(linker, "/export:DeleteFiber=kernel32.DeleteFiber")
#pragma comment(linker, "/export:DeleteFileA=kernel32.DeleteFileA")
#pragma comment(linker, "/export:DeleteFileW=EraDeleteFileW")
#pragma comment(linker, "/export:DeleteProcThreadAttributeList=kernel32.DeleteProcThreadAttributeList")
#pragma comment(linker, "/export:DeleteSynchronizationBarrier=kernel32.DeleteSynchronizationBarrier")
#pragma comment(linker, "/export:DeviceIoControl=EraDeviceIoControl")
#pragma comment(linker, "/export:DisableThreadLibraryCalls=kernel32.DisableThreadLibraryCalls")
#pragma comment(linker, "/export:DisassociateCurrentThreadFromCallback=kernel32.DisassociateCurrentThreadFromCallback")
#pragma comment(linker, "/export:DisconnectNamedPipe=kernel32.DisconnectNamedPipe")
#pragma comment(linker, "/export:DuplicateHandle=kernel32.DuplicateHandle")
#pragma comment(linker, "/export:EncodePointer=kernel32.EncodePointer")
#pragma comment(linker, "/export:EncodeSystemPointer=kernel32.EncodeSystemPointer")
#pragma comment(linker, "/export:EnterCriticalSection=kernel32.EnterCriticalSection")
#pragma comment(linker, "/export:EnterSynchronizationBarrier=kernel32.EnterSynchronizationBarrier")
#pragma comment(linker, "/export:EnumSystemLocalesA=kernel32.EnumSystemLocalesA")
#pragma comment(linker, "/export:EnumSystemLocalesEx=kernel32.EnumSystemLocalesEx")
#pragma comment(linker, "/export:EnumSystemLocalesW=kernel32.EnumSystemLocalesW")
#pragma comment(linker, "/export:EventActivityIdControl=kernelbase.EventActivityIdControl")
#pragma comment(linker, "/export:EventEnabled=kernelbase.EventEnabled")
#pragma comment(linker, "/export:EventProviderEnabled=kernelbase.EventProviderEnabled")
#pragma comment(linker, "/export:EventRegister=kernelbase.EventRegister")
#pragma comment(linker, "/export:EventSetInformation=kernelbase.EventSetInformation")
#pragma comment(linker, "/export:EventUnregister=kernelbase.EventUnregister")
#pragma comment(linker, "/export:EventWrite=kernelbase.EventWrite")
#pragma comment(linker, "/export:EventWriteEx=kernelbase.EventWriteEx")
#pragma comment(linker, "/export:EventWriteString=kernelbase.EventWriteString")
#pragma comment(linker, "/export:EventWriteTransfer=kernelbase.EventWriteTransfer")
#pragma comment(linker, "/export:ExitProcess=kernel32.ExitProcess")
#pragma comment(linker, "/export:ExitThread=kernel32.ExitThread")
#pragma comment(linker, "/export:ExpandEnvironmentStringsW=kernel32.ExpandEnvironmentStringsW")
#pragma comment(linker, "/export:FatalAppExitA=kernel32.FatalAppExitA")
#pragma comment(linker, "/export:FileTimeToLocalFileTime=kernel32.FileTimeToLocalFileTime")
#pragma comment(linker, "/export:FileTimeToSystemTime=kernel32.FileTimeToSystemTime")
#pragma comment(linker, "/export:FillMemoryNonTemporal=ntdll.RtlFillMemoryNonTemporal")
#pragma comment(linker, "/export:FindClose=kernel32.FindClose")
#pragma comment(linker, "/export:FindFirstFileA=kernel32.FindFirstFileA")
#pragma comment(linker, "/export:FindFirstFileExA=kernel32.FindFirstFileExA")
#pragma comment(linker, "/export:FindFirstFileExW=kernel32.FindFirstFileExW")
#pragma comment(linker, "/export:FindFirstFileW=kernel32.FindFirstFileW")
#pragma comment(linker, "/export:FindNLSString=kernel32.FindNLSString")
#pragma comment(linker, "/export:FindNLSStringEx=kernel32.FindNLSStringEx")
#pragma comment(linker, "/export:FindNextFileA=kernel32.FindNextFileA")
#pragma comment(linker, "/export:FindNextFileW=kernel32.FindNextFileW")
#pragma comment(linker, "/export:FindResourceExW=kernel32.FindResourceExW")
#pragma comment(linker, "/export:FindResourceW=kernel32.FindResourceW")
#pragma comment(linker, "/export:FindStringOrdinal=kernel32.FindStringOrdinal")
#pragma comment(linker, "/export:FlsAlloc=kernel32.FlsAlloc")
#pragma comment(linker, "/export:FlsFree=kernel32.FlsFree")
#pragma comment(linker, "/export:FlsGetValue=kernel32.FlsGetValue")
#pragma comment(linker, "/export:FlsSetValue=kernel32.FlsSetValue")
#pragma comment(linker, "/export:FlushFileBuffers=kernel32.FlushFileBuffers")
#pragma comment(linker, "/export:FlushProcessWriteBuffers=kernel32.FlushProcessWriteBuffers")
#pragma comment(linker, "/export:FoldStringW=kernel32.FoldStringW")
#pragma comment(linker, "/export:FormatMessageW=kernel32.FormatMessageW")
#pragma comment(linker, "/export:FreeEnvironmentStringsW=kernel32.FreeEnvironmentStringsW")
#pragma comment(linker, "/export:FreeLibrary=kernel32.FreeLibrary")
#pragma comment(linker, "/export:FreeLibraryAndExitThread=kernel32.FreeLibraryAndExitThread")
#pragma comment(linker, "/export:FreeLibraryWhenCallbackReturns=kernel32.FreeLibraryWhenCallbackReturns")
#pragma comment(linker, "/export:FreeTitlePhysicalPages")
#pragma comment(linker, "/export:GetACP=kernel32.GetACP")
#pragma comment(linker, "/export:GetCPInfo=kernel32.GetCPInfo")
#pragma comment(linker, "/export:GetCommandLineA=kernel32.GetCommandLineA")
#pragma comment(linker, "/export:GetCommandLineW=kernel32.GetCommandLineW")
#pragma comment(linker, "/export:GetComputerNameExW=kernel32.GetComputerNameExW")
#pragma comment(linker, "/export:GetConsoleCP=kernel32.GetConsoleCP")
#pragma comment(linker, "/export:GetConsoleMode=kernel32.GetConsoleMode")
#pragma comment(linker, "/export:GetConsoleType")
#pragma comment(linker, "/export:GetCurrencyFormatEx=kernel32.GetCurrencyFormatEx")
#pragma comment(linker, "/export:GetCurrentDirectoryA=kernel32.GetCurrentDirectoryA")
#pragma comment(linker, "/export:GetCurrentDirectoryW=kernel32.GetCurrentDirectoryW")
#pragma comment(linker, "/export:GetCurrentProcess=kernel32.GetCurrentProcess")
#pragma comment(linker, "/export:GetCurrentProcessId=kernel32.GetCurrentProcessId")
#pragma comment(linker, "/export:GetCurrentProcessorNumber=kernel32.GetCurrentProcessorNumber")
#pragma comment(linker, "/export:GetCurrentProcessorNumberEx=kernel32.GetCurrentProcessorNumberEx")
#pragma comment(linker, "/export:GetCurrentThread=kernel32.GetCurrentThread")
#pragma comment(linker, "/export:GetCurrentThreadId=kernel32.GetCurrentThreadId")
#pragma comment(linker, "/export:GetCurrentThreadStackLimits=kernel32.GetCurrentThreadStackLimits")
#pragma comment(linker, "/export:GetDateFormatA=kernel32.GetDateFormatA")
#pragma comment(linker, "/export:GetDateFormatEx=kernel32.GetDateFormatEx")
#pragma comment(linker, "/export:GetDateFormatW=kernel32.GetDateFormatW")
#pragma comment(linker, "/export:GetDiskFreeSpaceExW=kernel32.GetDiskFreeSpaceExW")
#pragma comment(linker, "/export:GetDiskFreeSpaceW=kernel32.GetDiskFreeSpaceW")
#pragma comment(linker, "/export:GetDriveTypeA=kernel32.GetDriveTypeA")
#pragma comment(linker, "/export:GetDriveTypeW=kernel32.GetDriveTypeW")
#pragma comment(linker, "/export:GetDynamicTimeZoneInformation=kernel32.GetDynamicTimeZoneInformation")
#pragma comment(linker, "/export:GetEnabledXStateFeatures=kernel32.GetEnabledXStateFeatures")
#pragma comment(linker, "/export:GetEnvironmentStringsW=kernel32.GetEnvironmentStringsW")
#pragma comment(linker, "/export:GetEnvironmentVariableW=kernel32.GetEnvironmentVariableW")
#pragma comment(linker, "/export:GetExitCodeProcess=kernel32.GetExitCodeProcess")
#pragma comment(linker, "/export:GetExitCodeThread=kernel32.GetExitCodeThread")
#pragma comment(linker, "/export:GetFileAttributesA=kernel32.GetFileAttributesA")
#pragma comment(linker, "/export:GetFileAttributesExA=kernel32.GetFileAttributesExA")
#pragma comment(linker, "/export:GetFileAttributesExW=kernel32.GetFileAttributesExW")
#pragma comment(linker, "/export:GetFileAttributesW=kernel32.GetFileAttributesW")
#pragma comment(linker, "/export:GetFileInformationByHandle=kernel32.GetFileInformationByHandle")
#pragma comment(linker, "/export:GetFileInformationByHandleEx=kernel32.GetFileInformationByHandleEx")
#pragma comment(linker, "/export:GetFileSize=kernel32.GetFileSize")
#pragma comment(linker, "/export:GetFileSizeEx=kernel32.GetFileSizeEx")
#pragma comment(linker, "/export:GetFileTime=kernel32.GetFileTime")
#pragma comment(linker, "/export:GetFileType=kernel32.GetFileType")
#pragma comment(linker, "/export:GetFullPathNameA=kernel32.GetFullPathNameA")
#pragma comment(linker, "/export:GetFullPathNameW=kernel32.GetFullPathNameW")
#pragma comment(linker, "/export:GetGeoInfoW=kernel32.GetGeoInfoW")
#pragma comment(linker, "/export:GetHandleInformation=kernel32.GetHandleInformation")
#pragma comment(linker, "/export:GetLastError=kernel32.GetLastError")
#pragma comment(linker, "/export:GetLocalTime=kernel32.GetLocalTime")
#pragma comment(linker, "/export:GetLocaleInfoA=kernel32.GetLocaleInfoA")
#pragma comment(linker, "/export:GetLocaleInfoEx=kernel32.GetLocaleInfoEx")
#pragma comment(linker, "/export:GetLocaleInfoW=kernel32.GetLocaleInfoW")
#pragma comment(linker, "/export:GetLogicalDrives=kernel32.GetLogicalDrives")
#pragma comment(linker, "/export:GetModuleFileNameA=kernel32.GetModuleFileNameA")
#pragma comment(linker, "/export:GetModuleFileNameW=kernel32.GetModuleFileNameW")
#pragma comment(linker, "/export:GetModuleHandleA=kernel32.GetModuleHandleA")
#pragma comment(linker, "/export:GetModuleHandleExA=kernel32.GetModuleHandleExA")
#pragma comment(linker, "/export:GetModuleHandleExW=kernel32.GetModuleHandleExW")
#pragma comment(linker, "/export:GetModuleHandleW=kernel32.GetModuleHandleW")
#pragma comment(linker, "/export:GetNativeSystemInfo=kernel32.GetNativeSystemInfo")
#pragma comment(linker, "/export:GetNumberFormatEx=kernel32.GetNumberFormatEx")
#pragma comment(linker, "/export:GetNumberOfConsoleInputEvents=kernel32.GetNumberOfConsoleInputEvents")
#pragma comment(linker, "/export:GetOEMCP=kernel32.GetOEMCP")
#pragma comment(linker, "/export:GetOverlappedResult=kernel32.GetOverlappedResult")
#pragma comment(linker, "/export:GetOverlappedResultEx=kernel32.GetOverlappedResultEx")
#pragma comment(linker, "/export:GetProcAddress=kernel32.GetProcAddress")
#pragma comment(linker, "/export:GetProcessAffinityMask=kernel32.GetProcessAffinityMask")
#pragma comment(linker, "/export:GetProcessHandleCount=kernel32.GetProcessHandleCount")
#pragma comment(linker, "/export:GetProcessHeap=kernel32.GetProcessHeap")
#pragma comment(linker, "/export:GetProcessHeaps=kernel32.GetProcessHeaps")
#pragma comment(linker, "/export:GetProcessId=kernel32.GetProcessId")
#pragma comment(linker, "/export:GetProcessIdOfThread=kernel32.GetProcessIdOfThread")
#pragma comment(linker, "/export:GetProcessPriorityBoost=kernel32.GetProcessPriorityBoost")
#pragma comment(linker, "/export:GetProcessTimes=kernel32.GetProcessTimes")
#pragma comment(linker, "/export:GetProcessWorkingSetSize=kernel32.GetProcessWorkingSetSize")
#pragma comment(linker, "/export:GetQueuedCompletionStatus=kernel32.GetQueuedCompletionStatus")
#pragma comment(linker, "/export:GetQueuedCompletionStatusEx=kernel32.GetQueuedCompletionStatusEx")
#pragma comment(linker, "/export:GetStartupInfoW=kernel32.GetStartupInfoW")
#pragma comment(linker, "/export:GetStdHandle=kernel32.GetStdHandle")
#pragma comment(linker, "/export:GetStringTypeExW=kernel32.GetStringTypeExW")
#pragma comment(linker, "/export:GetStringTypeW=kernel32.GetStringTypeW")
#pragma comment(linker, "/export:GetSystemDirectoryW=kernel32.GetSystemDirectoryW")
#pragma comment(linker, "/export:GetSystemFileCacheSize=kernel32.GetSystemFileCacheSize")
#pragma comment(linker, "/export:GetSystemInfo=kernel32.GetSystemInfo")
#pragma comment(linker, "/export:GetSystemOSVersion")
#pragma comment(linker, "/export:GetSystemTime=kernel32.GetSystemTime")
#pragma comment(linker, "/export:GetSystemTimeAdjustment=kernel32.GetSystemTimeAdjustment")
#pragma comment(linker, "/export:GetSystemTimeAsFileTime=kernel32.GetSystemTimeAsFileTime")
#pragma comment(linker, "/export:GetSystemTimePreciseAsFileTime=kernel32.GetSystemTimePreciseAsFileTime")
#pragma comment(linker, "/export:GetSystemWindowsDirectoryW=kernel32.GetSystemWindowsDirectoryW")
#pragma comment(linker, "/export:GetTempPathW=kernel32.GetTempPathW")
#pragma comment(linker, "/export:GetThreadContext=kernel32.GetThreadContext")
#pragma comment(linker, "/export:GetThreadGroupAffinity=kernel32.GetThreadGroupAffinity")
#pragma comment(linker, "/export:GetThreadId=kernel32.GetThreadId")
#pragma comment(linker, "/export:GetThreadIdealProcessorEx=kernel32.GetThreadIdealProcessorEx")
#pragma comment(linker, "/export:GetThreadLocale=kernel32.GetThreadLocale")
#pragma comment(linker, "/export:GetThreadName")
#pragma comment(linker, "/export:GetThreadPriority=kernel32.GetThreadPriority")
#pragma comment(linker, "/export:GetThreadPriorityBoost=kernel32.GetThreadPriorityBoost")
#pragma comment(linker, "/export:GetThreadTimes=kernel32.GetThreadTimes")
#pragma comment(linker, "/export:GetTickCount=kernel32.GetTickCount")
#pragma comment(linker, "/export:GetTickCount64=kernel32.GetTickCount64")
#pragma comment(linker, "/export:GetTimeFormatA=kernel32.GetTimeFormatA")
#pragma comment(linker, "/export:GetTimeFormatEx=kernel32.GetTimeFormatEx")
#pragma comment(linker, "/export:GetTimeFormatW=kernel32.GetTimeFormatW")
#pragma comment(linker, "/export:GetTimeZoneInformation=kernel32.GetTimeZoneInformation")
#pragma comment(linker, "/export:GetTimeZoneInformationForYear=kernel32.GetTimeZoneInformationForYear")
#pragma comment(linker, "/export:GetTraceEnableFlags=kernelbase.GetTraceEnableFlags")
#pragma comment(linker, "/export:GetTraceEnableLevel=kernelbase.GetTraceEnableLevel")
#pragma comment(linker, "/export:GetTraceLoggerHandle=kernelbase.GetTraceLoggerHandle")
#pragma comment(linker, "/export:GetUserDefaultLCID=kernel32.GetUserDefaultLCID")
#pragma comment(linker, "/export:GetUserDefaultLocaleName=kernel32.GetUserDefaultLocaleName")
#pragma comment(linker, "/export:GetUserGeoID=kernel32.GetUserGeoID")
#pragma comment(linker, "/export:GetVersion=kernel32.GetVersion")
#pragma comment(linker, "/export:GetVersionExW=kernel32.GetVersionExW")
#pragma comment(linker, "/export:GetVolumeInformationByHandleW=kernel32.GetVolumeInformationByHandleW")
#pragma comment(linker, "/export:GetVolumeInformationW=kernel32.GetVolumeInformationW")
#pragma comment(linker, "/export:GetVolumePathNameW=kernel32.GetVolumePathNameW")
#pragma comment(linker, "/export:GetWindowsDirectoryW=kernel32.GetWindowsDirectoryW")
#pragma comment(linker, "/export:GetXStateFeaturesMask=kernel32.GetXStateFeaturesMask")
#pragma comment(linker, "/export:GlobalMemoryStatusEx=kernel32.GlobalMemoryStatusEx")
#pragma comment(linker, "/export:HeapAlloc=kernel32.HeapAlloc")
#pragma comment(linker, "/export:HeapCompact=kernel32.HeapCompact")
#pragma comment(linker, "/export:HeapCreate=kernel32.HeapCreate")
#pragma comment(linker, "/export:HeapDestroy=kernel32.HeapDestroy")
#pragma comment(linker, "/export:HeapFree=kernel32.HeapFree")
#pragma comment(linker, "/export:HeapLock=kernel32.HeapLock")
#pragma comment(linker, "/export:HeapQueryInformation=kernel32.HeapQueryInformation")
#pragma comment(linker, "/export:HeapReAlloc=kernel32.HeapReAlloc")
#pragma comment(linker, "/export:HeapSetInformation=kernel32.HeapSetInformation")
#pragma comment(linker, "/export:HeapSize=kernel32.HeapSize")
#pragma comment(linker, "/export:HeapUnlock=kernel32.HeapUnlock")
#pragma comment(linker, "/export:HeapValidate=kernel32.HeapValidate")
#pragma comment(linker, "/export:HeapWalk=kernel32.HeapWalk")
#pragma comment(linker, "/export:InitOnceBeginInitialize=kernel32.InitOnceBeginInitialize")
#pragma comment(linker, "/export:InitOnceComplete=kernel32.InitOnceComplete")
#pragma comment(linker, "/export:InitOnceExecuteOnce=kernel32.InitOnceExecuteOnce")
#pragma comment(linker, "/export:InitOnceInitialize=kernel32.InitOnceInitialize")
#pragma comment(linker, "/export:InitializeConditionVariable=kernel32.InitializeConditionVariable")
#pragma comment(linker, "/export:InitializeContext=kernel32.InitializeContext")
#pragma comment(linker, "/export:InitializeCriticalSection=kernel32.InitializeCriticalSection")
#pragma comment(linker, "/export:InitializeCriticalSectionAndSpinCount=kernel32.InitializeCriticalSectionAndSpinCount")
#pragma comment(linker, "/export:InitializeCriticalSectionEx=kernel32.InitializeCriticalSectionEx")
#pragma comment(linker, "/export:InitializeProcThreadAttributeList=kernel32.InitializeProcThreadAttributeList")
#pragma comment(linker, "/export:InitializeSListHead=kernel32.InitializeSListHead")
#pragma comment(linker, "/export:InitializeSRWLock=kernel32.InitializeSRWLock")
#pragma comment(linker, "/export:InitializeSynchronizationBarrier=kernel32.InitializeSynchronizationBarrier")
#pragma comment(linker, "/export:InterlockedFlushSList=kernel32.InterlockedFlushSList")
#pragma comment(linker, "/export:InterlockedPopEntrySList=kernel32.InterlockedPopEntrySList")
#pragma comment(linker, "/export:InterlockedPushEntrySList=kernel32.InterlockedPushEntrySList")
#pragma comment(linker, "/export:InterlockedPushListSList=kernel32.InterlockedPushListSList")
#pragma comment(linker, "/export:InterlockedPushListSListEx=kernel32.InterlockedPushListSListEx")
#pragma comment(linker, "/export:IsDebuggerPresent=kernel32.IsDebuggerPresent")
#pragma comment(linker, "/export:IsProcessorFeaturePresent=kernel32.IsProcessorFeaturePresent")
#pragma comment(linker, "/export:IsThreadAFiber=kernel32.IsThreadAFiber")
#pragma comment(linker, "/export:IsThreadpoolTimerSet=kernel32.IsThreadpoolTimerSet")
#pragma comment(linker, "/export:IsValidCodePage=kernel32.IsValidCodePage")
#pragma comment(linker, "/export:IsValidLocale=kernel32.IsValidLocale")
#pragma comment(linker, "/export:IsValidLocaleName=kernel32.IsValidLocaleName")
#pragma comment(linker, "/export:JobTitleMemoryStatus")
#pragma comment(linker, "/export:LCIDToLocaleName=kernel32.LCIDToLocaleName")
#pragma comment(linker, "/export:LCMapStringEx=kernel32.LCMapStringEx")
#pragma comment(linker, "/export:LCMapStringW=kernel32.LCMapStringW")
#pragma comment(linker, "/export:LeaveCriticalSection=kernel32.LeaveCriticalSection")
#pragma comment(linker,                                                                                                \
                "/export:LeaveCriticalSectionWhenCallbackReturns=kernel32.LeaveCriticalSectionWhenCallbackReturns")
#pragma comment(linker, "/export:LoadLibraryExA=kernel32.LoadLibraryExA")
#pragma comment(linker, "/export:LoadLibraryExW=kernel32.LoadLibraryExW")
#pragma comment(linker, "/export:LoadLibraryW=kernel32.LoadLibraryW")
#pragma comment(linker, "/export:LoadPackagedLibrary=kernel32.LoadPackagedLibrary")
#pragma comment(linker, "/export:LoadResource=kernel32.LoadResource")
#pragma comment(linker, "/export:LoadStringW=kernelbase.LoadStringW")
#pragma comment(linker, "/export:LocalAlloc=kernel32.LocalAlloc")
#pragma comment(linker, "/export:LocalFileTimeToFileTime=kernel32.LocalFileTimeToFileTime")
#pragma comment(linker, "/export:LocalFree=kernel32.LocalFree")
#pragma comment(linker, "/export:LocaleNameToLCID=kernel32.LocaleNameToLCID")
#pragma comment(linker, "/export:LocateXStateFeature=kernel32.LocateXStateFeature")
#pragma comment(linker, "/export:LockFile=kernel32.LockFile")
#pragma comment(linker, "/export:LockFileEx=kernel32.LockFileEx")
#pragma comment(linker, "/export:LockResource=kernel32.LockResource")
#pragma comment(linker, "/export:MapTitlePhysicalPages")
#pragma comment(linker, "/export:MapViewOfFileEx=kernel32.MapViewOfFileEx")
#pragma comment(linker, "/export:MoveFileExW=kernel32.MoveFileExW")
#pragma comment(linker, "/export:MulDiv=kernel32.MulDiv")
#pragma comment(linker, "/export:MultiByteToWideChar=kernel32.MultiByteToWideChar")
#pragma comment(linker, "/export:NlsUpdateLocale=kernel32.NlsUpdateLocale")
#pragma comment(linker, "/export:OpenEventA=kernel32.OpenEventA")
#pragma comment(linker, "/export:OpenEventW=kernel32.OpenEventW")
#pragma comment(linker, "/export:OpenFileMappingW=kernel32.OpenFileMappingW")
#pragma comment(linker, "/export:OpenJobObjectW=kernel32.OpenJobObjectW")
#pragma comment(linker, "/export:OpenMutexA=kernel32.OpenMutexA")
#pragma comment(linker, "/export:OpenMutexW=kernel32.OpenMutexW")
#pragma comment(linker, "/export:OpenProcess=kernel32.OpenProcess")
#pragma comment(linker, "/export:OpenSemaphoreA=kernel32.OpenSemaphoreA")
#pragma comment(linker, "/export:OpenSemaphoreW=kernel32.OpenSemaphoreW")
#pragma comment(linker, "/export:OpenThread=kernel32.OpenThread")
#pragma comment(linker, "/export:OpenWaitableTimerA=kernel32.OpenWaitableTimerA")
#pragma comment(linker, "/export:OpenWaitableTimerW=kernel32.OpenWaitableTimerW")
#pragma comment(linker, "/export:OutputDebugStringA=kernel32.OutputDebugStringA")
#pragma comment(linker, "/export:OutputDebugStringW=kernel32.OutputDebugStringW")
#pragma comment(linker, "/export:PeekConsoleInputA=kernel32.PeekConsoleInputA")
#pragma comment(linker, "/export:PeekNamedPipe=kernel32.PeekNamedPipe")
#pragma comment(linker, "/export:PostQueuedCompletionStatus=kernel32.PostQueuedCompletionStatus")
#pragma comment(linker, "/export:QueryDepthSList=kernel32.QueryDepthSList")
#pragma comment(linker, "/export:QueryPerformanceCounter=kernel32.QueryPerformanceCounter")
#pragma comment(linker, "/export:QueryPerformanceFrequency=kernel32.QueryPerformanceFrequency")
#pragma comment(linker, "/export:QueryProcessorSchedulingStatistics")
#pragma comment(linker, "/export:QueryThreadpoolStackInformation=kernel32.QueryThreadpoolStackInformation")
#pragma comment(linker, "/export:QueueUserAPC=kernel32.QueueUserAPC")
#pragma comment(linker, "/export:QueueUserWorkItem=kernel32.QueueUserWorkItem")
#pragma comment(linker, "/export:RaiseException=kernel32.RaiseException")
#pragma comment(linker, "/export:RaiseFailFastException=kernel32.RaiseFailFastException")
#pragma comment(linker, "/export:ReadConsoleInputA=kernel32.ReadConsoleInputA")
#pragma comment(linker, "/export:ReadConsoleInputW=kernel32.ReadConsoleInputW")
#pragma comment(linker, "/export:ReadConsoleW=kernel32.ReadConsoleW")
#pragma comment(linker, "/export:ReadFile=kernel32.ReadFile")
#pragma comment(linker, "/export:ReadFileEx=kernel32.ReadFileEx")
#pragma comment(linker, "/export:ReadFileScatter=kernel32.ReadFileScatter")
#pragma comment(linker, "/export:ReadProcessMemory=kernel32.ReadProcessMemory")
#pragma comment(linker, "/export:RegCloseKey=kernel32.RegCloseKey")
#pragma comment(linker, "/export:RegCreateKeyExW=kernel32.RegCreateKeyExW")
#pragma comment(linker, "/export:RegCreateKeyW=advapi32.RegCreateKeyW")
#pragma comment(linker, "/export:RegDeleteKeyExW=kernel32.RegDeleteKeyExW")
#pragma comment(linker, "/export:RegDeleteKeyW=advapi32.RegDeleteKeyW")
#pragma comment(linker, "/export:RegDeleteValueW=kernel32.RegDeleteValueW")
#pragma comment(linker, "/export:RegEnumKeyExW=kernel32.RegEnumKeyExW")
#pragma comment(linker, "/export:RegEnumKeyW=advapi32.RegEnumKeyW")
#pragma comment(linker, "/export:RegEnumValueW=kernel32.RegEnumValueW")
#pragma comment(linker, "/export:RegOpenKeyExW=kernel32.RegOpenKeyExW")
#pragma comment(linker, "/export:RegOpenKeyW=advapi32.RegOpenKeyW")
#pragma comment(linker, "/export:RegQueryInfoKeyW=kernel32.RegQueryInfoKeyW")
#pragma comment(linker, "/export:RegQueryValueExW=kernel32.RegQueryValueExW")
#pragma comment(linker, "/export:RegSetValueExW=kernel32.RegSetValueExW")
#pragma comment(linker, "/export:RegisterTraceGuidsW=kernelbase.RegisterTraceGuidsW")
#pragma comment(linker, "/export:RegisterWaitForSingleObject=kernel32.RegisterWaitForSingleObject")
#pragma comment(linker, "/export:ReleaseMutex=kernel32.ReleaseMutex")
#pragma comment(linker, "/export:ReleaseMutexWhenCallbackReturns=kernel32.ReleaseMutexWhenCallbackReturns")
#pragma comment(linker, "/export:ReleaseSRWLockExclusive=kernel32.ReleaseSRWLockExclusive")
#pragma comment(linker, "/export:ReleaseSRWLockShared=kernel32.ReleaseSRWLockShared")
#pragma comment(linker, "/export:ReleaseSemaphore=kernel32.ReleaseSemaphore")
#pragma comment(linker, "/export:ReleaseSemaphoreWhenCallbackReturns=kernel32.ReleaseSemaphoreWhenCallbackReturns")
#pragma comment(linker, "/export:RemoveDirectoryA=kernel32.RemoveDirectoryA")
#pragma comment(linker, "/export:RemoveDirectoryW=kernel32.RemoveDirectoryW")
#pragma comment(linker, "/export:RemoveVectoredContinueHandler=kernel32.RemoveVectoredContinueHandler")
#pragma comment(linker, "/export:RemoveVectoredExceptionHandler=kernel32.RemoveVectoredExceptionHandler")
#pragma comment(linker, "/export:ResetEvent=kernel32.ResetEvent")
#pragma comment(linker, "/export:ResolveLocaleName=kernel32.ResolveLocaleName")
#pragma comment(linker, "/export:RestoreLastError=kernel32.RestoreLastError")
#pragma comment(linker, "/export:ResumeThread=kernel32.ResumeThread")
#pragma comment(linker, "/export:RtlCaptureContext=kernel32.RtlCaptureContext")
#pragma comment(linker, "/export:RtlCaptureStackBackTrace=kernel32.RtlCaptureStackBackTrace")
#pragma comment(linker, "/export:RtlLookupFunctionEntry=kernel32.RtlLookupFunctionEntry")
#pragma comment(linker, "/export:RtlPcToFileHeader=kernel32.RtlPcToFileHeader")
#pragma comment(linker, "/export:RtlRaiseException=kernel32.RtlRaiseException")
#pragma comment(linker, "/export:RtlRestoreContext=kernel32.RtlRestoreContext")
#pragma comment(linker, "/export:RtlUnwind=kernel32.RtlUnwind")
#pragma comment(linker, "/export:RtlUnwindEx=kernel32.RtlUnwindEx")
#pragma comment(linker, "/export:RtlVirtualUnwind=kernel32.RtlVirtualUnwind")
#pragma comment(linker, "/export:SearchPathW=kernel32.SearchPathW")
#pragma comment(linker, "/export:SetConsoleCtrlHandler=kernel32.SetConsoleCtrlHandler")
#pragma comment(linker, "/export:SetConsoleMode=kernel32.SetConsoleMode")
#pragma comment(linker, "/export:SetCriticalSectionSpinCount=kernel32.SetCriticalSectionSpinCount")
#pragma comment(linker, "/export:SetCurrentDirectoryA=kernel32.SetCurrentDirectoryA")
#pragma comment(linker, "/export:SetCurrentDirectoryW=kernel32.SetCurrentDirectoryW")
#pragma comment(linker, "/export:SetDynamicTimeZoneInformation=kernel32.SetDynamicTimeZoneInformation")
#pragma comment(linker, "/export:SetEndOfFile=kernel32.SetEndOfFile")
#pragma comment(linker, "/export:SetEnvironmentStringsW=kernel32.SetEnvironmentStringsW")
#pragma comment(linker, "/export:SetEnvironmentVariableA=kernel32.SetEnvironmentVariableA")
#pragma comment(linker, "/export:SetEnvironmentVariableW=kernel32.SetEnvironmentVariableW")
#pragma comment(linker, "/export:SetErrorMode=kernel32.SetErrorMode")
#pragma comment(linker, "/export:SetEvent=kernel32.SetEvent")
#pragma comment(linker, "/export:SetEventWhenCallbackReturns=kernel32.SetEventWhenCallbackReturns")
#pragma comment(linker, "/export:SetFileAttributesA=kernel32.SetFileAttributesA")
#pragma comment(linker, "/export:SetFileAttributesW=kernel32.SetFileAttributesW")
#pragma comment(linker, "/export:SetFileInformationByHandle=kernel32.SetFileInformationByHandle")
#pragma comment(linker, "/export:SetFilePointer=kernel32.SetFilePointer")
#pragma comment(linker, "/export:SetFilePointerEx=kernel32.SetFilePointerEx")
#pragma comment(linker, "/export:SetFileTime=kernel32.SetFileTime")
#pragma comment(linker, "/export:SetFileValidData=kernel32.SetFileValidData")
#pragma comment(linker, "/export:SetHandleInformation=kernel32.SetHandleInformation")
#pragma comment(linker, "/export:SetLastError=kernel32.SetLastError")
#pragma comment(linker, "/export:SetLocalTime=kernel32.SetLocalTime")
#pragma comment(linker, "/export:SetNamedPipeHandleState=kernel32.SetNamedPipeHandleState")
#pragma comment(linker, "/export:SetProcessAffinityMask=kernel32.SetProcessAffinityMask")
#pragma comment(linker, "/export:SetProcessPriorityBoost=kernel32.SetProcessPriorityBoost")
#pragma comment(linker, "/export:SetProcessWorkingSetSize=kernel32.SetProcessWorkingSetSize")
#pragma comment(linker, "/export:SetStdHandle=kernel32.SetStdHandle")
#pragma comment(linker, "/export:SetStdHandleEx=kernel32.SetStdHandleEx")
#pragma comment(linker, "/export:SetSystemFileCacheSize=kernel32.SetSystemFileCacheSize")
#pragma comment(linker, "/export:SetThreadAffinityMask=kernel32.SetThreadAffinityMask")
#pragma comment(linker, "/export:SetThreadContext=kernel32.SetThreadContext")
#pragma comment(linker, "/export:SetThreadGroupAffinity=kernel32.SetThreadGroupAffinity")
#pragma comment(linker, "/export:SetThreadIdealProcessorEx=kernel32.SetThreadIdealProcessorEx")
#pragma comment(linker, "/export:SetThreadLocale=kernel32.SetThreadLocale")
#pragma comment(linker, "/export:SetThreadName")
#pragma comment(linker, "/export:SetThreadPriority=kernel32.SetThreadPriority")
#pragma comment(linker, "/export:SetThreadPriorityBoost=kernel32.SetThreadPriorityBoost")
#pragma comment(linker, "/export:SetThreadStackGuarantee=kernel32.SetThreadStackGuarantee")
#pragma comment(linker, "/export:SetThreadpoolAffinityMask")
#pragma comment(linker, "/export:SetThreadpoolStackInformation=kernel32.SetThreadpoolStackInformation")
#pragma comment(linker, "/export:SetThreadpoolThreadMaximum=kernel32.SetThreadpoolThreadMaximum")
#pragma comment(linker, "/export:SetThreadpoolThreadMinimum=kernel32.SetThreadpoolThreadMinimum")
#pragma comment(linker, "/export:SetThreadpoolTimer=kernel32.SetThreadpoolTimer")
#pragma comment(linker, "/export:SetThreadpoolWait=kernel32.SetThreadpoolWait")
#pragma comment(linker, "/export:SetUnhandledExceptionFilter=kernel32.SetUnhandledExceptionFilter")
#pragma comment(linker, "/export:SetUserGeoID=kernel32.SetUserGeoID")
#pragma comment(linker, "/export:SetWaitableTimer=kernel32.SetWaitableTimer")
#pragma comment(linker, "/export:SetWaitableTimerEx=kernel32.SetWaitableTimerEx")
#pragma comment(linker, "/export:SetXStateFeaturesMask=kernel32.SetXStateFeaturesMask")
#pragma comment(linker, "/export:SignalObjectAndWait=kernel32.SignalObjectAndWait")
#pragma comment(linker, "/export:SizeofResource=kernel32.SizeofResource")
#pragma comment(linker, "/export:Sleep=kernel32.Sleep")
#pragma comment(linker, "/export:SleepConditionVariableCS=kernel32.SleepConditionVariableCS")
#pragma comment(linker, "/export:SleepConditionVariableSRW=kernel32.SleepConditionVariableSRW")
#pragma comment(linker, "/export:SleepEx=kernel32.SleepEx")
#pragma comment(linker, "/export:StartThreadpoolIo=kernel32.StartThreadpoolIo")
#pragma comment(linker, "/export:SubmitThreadpoolWork=kernel32.SubmitThreadpoolWork")
#pragma comment(linker, "/export:SuspendThread=kernel32.SuspendThread")
#pragma comment(linker, "/export:SwitchToFiber=kernel32.SwitchToFiber")
#pragma comment(linker, "/export:SwitchToThread=kernel32.SwitchToThread")
#pragma comment(linker, "/export:SystemTimeToFileTime=kernel32.SystemTimeToFileTime")
#pragma comment(linker, "/export:SystemTimeToTzSpecificLocalTime=kernel32.SystemTimeToTzSpecificLocalTime")
#pragma comment(linker, "/export:TerminateProcess=kernel32.TerminateProcess")
#pragma comment(linker, "/export:TerminateThread=kernel32.TerminateThread")
#pragma comment(linker, "/export:TitleMemoryStatus")
#pragma comment(linker, "/export:TlsAlloc=kernel32.TlsAlloc")
#pragma comment(linker, "/export:TlsFree=kernel32.TlsFree")
#pragma comment(linker, "/export:TlsGetValue=kernel32.TlsGetValue")
#pragma comment(linker, "/export:TlsSetValue=kernel32.TlsSetValue")
#pragma comment(linker, "/export:ToolingMemoryStatus")
#pragma comment(linker, "/export:TraceEvent=kernelbase.TraceEvent")
#pragma comment(linker, "/export:TraceMessage=kernelbase.TraceMessage")
#pragma comment(linker, "/export:TraceMessageVa=kernelbase.TraceMessageVa")
#pragma comment(linker, "/export:TryAcquireSRWLockExclusive=kernel32.TryAcquireSRWLockExclusive")
#pragma comment(linker, "/export:TryAcquireSRWLockShared=kernel32.TryAcquireSRWLockShared")
#pragma comment(linker, "/export:TryEnterCriticalSection=kernel32.TryEnterCriticalSection")
#pragma comment(linker, "/export:TrySubmitThreadpoolCallback=kernel32.TrySubmitThreadpoolCallback")
#pragma comment(linker, "/export:TzSpecificLocalTimeToSystemTime=kernel32.TzSpecificLocalTimeToSystemTime")
#pragma comment(linker, "/export:UnhandledExceptionFilter=kernel32.UnhandledExceptionFilter")
#pragma comment(linker, "/export:UnlockFile=kernel32.UnlockFile")
#pragma comment(linker, "/export:UnlockFileEx=kernel32.UnlockFileEx")
#pragma comment(linker, "/export:UnmapViewOfFile=kernel32.UnmapViewOfFile")
#pragma comment(linker, "/export:UnregisterTraceGuids=kernelbase.UnregisterTraceGuids")
#pragma comment(linker, "/export:UnregisterWaitEx=kernel32.UnregisterWaitEx")
#pragma comment(linker, "/export:UpdateProcThreadAttribute=kernel32.UpdateProcThreadAttribute")
#pragma comment(linker, "/export:VirtualAlloc=EraVirtualAlloc")
#pragma comment(linker, "/export:VirtualAllocEx=EraVirtualAllocEx")
#pragma comment(linker, "/export:VirtualFree=EraVirtualFree")
#pragma comment(linker, "/export:VirtualFreeEx=EraVirtualFreeEx")
#pragma comment(linker, "/export:VirtualProtect=EraVirtualProtect")
#pragma comment(linker, "/export:VirtualProtectEx=EraVirtualProtectEx")
#pragma comment(linker, "/export:VirtualQuery=EraVirtualQuery")
#pragma comment(linker, "/export:VirtualQueryEx=EraVirtualQueryEx")
#pragma comment(linker, "/export:WaitForMultipleObjects=kernel32.WaitForMultipleObjects")
#pragma comment(linker, "/export:WaitForMultipleObjectsEx=kernel32.WaitForMultipleObjectsEx")
#pragma comment(linker, "/export:WaitForSingleObject=kernel32.WaitForSingleObject")
#pragma comment(linker, "/export:WaitForSingleObjectEx=kernel32.WaitForSingleObjectEx")
#pragma comment(linker, "/export:WaitForThreadpoolIoCallbacks=kernel32.WaitForThreadpoolIoCallbacks")
#pragma comment(linker, "/export:WaitForThreadpoolTimerCallbacks=kernel32.WaitForThreadpoolTimerCallbacks")
#pragma comment(linker, "/export:WaitForThreadpoolWaitCallbacks=kernel32.WaitForThreadpoolWaitCallbacks")
#pragma comment(linker, "/export:WaitForThreadpoolWorkCallbacks=kernel32.WaitForThreadpoolWorkCallbacks")
#pragma comment(linker, "/export:WaitNamedPipeW=kernel32.WaitNamedPipeW")
#pragma comment(linker, "/export:WaitOnAddress=kernelbase.WaitOnAddress")
#pragma comment(linker, "/export:WakeAllConditionVariable=kernel32.WakeAllConditionVariable")
#pragma comment(linker, "/export:WakeByAddressAll=kernelbase.WakeByAddressAll")
#pragma comment(linker, "/export:WakeByAddressSingle=kernelbase.WakeByAddressSingle")
#pragma comment(linker, "/export:WakeConditionVariable=kernel32.WakeConditionVariable")
#pragma comment(linker, "/export:WerRegisterFile=kernel32.WerRegisterFile")
#pragma comment(linker, "/export:WerUnregisterFile=kernel32.WerUnregisterFile")
#pragma comment(linker, "/export:WideCharToMultiByte=kernel32.WideCharToMultiByte")
#pragma comment(linker, "/export:WriteConsoleW=kernel32.WriteConsoleW")
#pragma comment(linker, "/export:WriteFile=kernel32.WriteFile")
#pragma comment(linker, "/export:WriteFileEx=kernel32.WriteFileEx")
#pragma comment(linker, "/export:WriteFileGather=kernel32.WriteFileGather")
#pragma comment(linker, "/export:WriteProcessMemory=kernel32.WriteProcessMemory")
#pragma comment(linker, "/export:XMemAlloc")
#pragma comment(linker, "/export:XMemAllocDefault")
#pragma comment(linker, "/export:XMemCheckDefaultHeaps")
#pragma comment(linker, "/export:XMemFree")
#pragma comment(linker, "/export:XMemFreeDefault")
#pragma comment(linker, "/export:XMemGetAllocationHysteresis")
#pragma comment(linker, "/export:XMemGetAllocationStatistics")
#pragma comment(linker, "/export:XMemGetAuxiliaryTitleMemory")
#pragma comment(linker, "/export:XMemPreallocateFreeSpace")
#pragma comment(linker, "/export:XMemReleaseAuxiliaryTitleMemory")
#pragma comment(linker, "/export:XMemSetAllocationHooks")
#pragma comment(linker, "/export:XMemSetAllocationHysteresis")
#pragma comment(linker, "/export:lstrcmpA=kernel32.lstrcmpA")
#pragma comment(linker, "/export:lstrcmpW=kernel32.lstrcmpW")
#pragma comment(linker, "/export:lstrcmpiA=kernel32.lstrcmpiA")
#pragma comment(linker, "/export:lstrcmpiW=kernel32.lstrcmpiW")

// For D3D11.X
#pragma comment(linker, "/export:MapTitleEsramPages")
