//Here lies some of the KernelX implementation.
//All the code is based on XWine1's SlimEra
//Repo (https://github.com/XWine1/SlimEra).
//All credits to XWine1 and DaZombieKiller.
#include "pch.h"
#include "../common/common.h"
#include "Allocation.h"

//No game uses that so far so
//no worries about that for now.
UINT64 WINAPI NlsUpdateLocale_X()
{
    return 0;
}

void WINAPI WakeByAddressSingle_X(PVOID Address)
{
    WakeByAddressSingle(Address);
}

void WINAPI WakeByAddressAll_X(PVOID Address)
{
    WakeByAddressAll(Address);
}

BOOL WINAPI WaitOnAddress_X(volatile void* Address, PVOID CompareAddress, SIZE_T AddressSize, DWORD dwMilliseconds)
{
    return WaitOnAddress(Address, CompareAddress, AddressSize, dwMilliseconds);
}

BOOL WINAPI JobTitleMemoryStatus_X(void* pJob, LPTITLEMEMORYSTATUS Buffer)
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

BOOL WINAPI SetThreadpoolAffinityMask_X()
{
    return TRUE;
}

BOOL WINAPI SetThreadName_X(HANDLE hThread, const WCHAR* lpThreadName)
{
    HRESULT hr = SetThreadDescription(hThread, lpThreadName);
    SetLastError(WIN32_FROM_HRESULT(hr));
    return SUCCEEDED(hr);
}

void WINAPI QueryProcessorSchedulingStatistics_X(PPROCESSOR_SCHEDULING_STATISTICS ProcessorSchedulingStatistics)
{
    LARGE_INTEGER Frequency, Counter;
    FILETIME IdleTime, KernelTime, UserTime;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&Counter);
    ProcessorSchedulingStatistics->GlobalTime = Counter.QuadPart / (Frequency.QuadPart / 10000000ULL);

    if (GetSystemTimes(&IdleTime, &KernelTime, &UserTime))
    {
        ULARGE_INTEGER IdleTime64 = { IdleTime.dwLowDateTime, IdleTime.dwHighDateTime };
        ULARGE_INTEGER KernelTime64 = { KernelTime.dwLowDateTime, KernelTime.dwHighDateTime };
        ULARGE_INTEGER UserTime64 = { UserTime.dwLowDateTime, UserTime.dwHighDateTime };
        ProcessorSchedulingStatistics->RunningTime = (KernelTime64.QuadPart - IdleTime64.QuadPart) + UserTime64.QuadPart;
        ProcessorSchedulingStatistics->IdleTime = IdleTime64.QuadPart;
    }
    else
    {
        ProcessorSchedulingStatistics->RunningTime = 0;
        ProcessorSchedulingStatistics->IdleTime = 0;
    }
}

BOOL WINAPI GetThreadName_X(HANDLE hThread, PWSTR lpThreadName, SIZE_T dwBufferLength, PSIZE_T pdwReturnLength)
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

void GetSystemOSVersion_X(LPSYSTEMOSVERSIONINFO VersionInformation)
{
    DWORD FileVersionSize = GetFileVersionInfoSizeW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL);
    if (!FileVersionSize)
    {
        MessageBoxW(nullptr, L"Couldn't get the combase version info size! Make sure you have EmbeddedXvd in the game root/Mount folder.\n", L"Error!", MB_OK);
        return;
    }

    BYTE* Data = new BYTE[FileVersionSize];
    BOOL ret = GetFileVersionInfoW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL, FileVersionSize, Data);
    if (!ret)
    {
        MessageBoxW(nullptr, L"Couldn't get the combase version info! Make sure you have EmbeddedXvd in the game root/Mount folder.\n", L"Error!", MB_OK);
        delete[] Data;
        return;
    }

    VS_FIXEDFILEINFO* pFixedFileInfo{};
    UINT Length = 0;

    VerQueryValueW(Data, L"\\", (LPVOID*)&pFixedFileInfo, &Length);
    if (!pFixedFileInfo)
    {
        MessageBoxW(nullptr, L"Couldn't get the combase version value! Make sure you have EmbeddedXvd in the game root/Mount folder.\n", L"Error!", MB_OK);
        delete[] Data;
        return;
    }

    DWORD major = HIWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD minor = LOWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD build = HIWORD(pFixedFileInfo->dwProductVersionLS);
    DWORD revision = LOWORD(pFixedFileInfo->dwProductVersionLS);

    VersionInformation->MajorVersion = major;
    VersionInformation->MinorVersion = minor;
    VersionInformation->BuildNumber = build;
    VersionInformation->Revision = revision;

    delete[] Data;
}

CONSOLE_TYPE WINAPI GetConsoleType_X()
{
    //TODO: Allow users to change the console type based
    //On the experience they want (i.e. Enhanced graphics etc)
    return CONSOLE_TYPE::CONSOLE_TYPE_XBOX_ONE_X_DEVKIT;
}

void WINAPI XMemSetAllocationHooks_X(PXMEMALLOC_ROUTINE pAllocRoutine, PXMEMFREE_ROUTINE pFreeRoutine)
{
    EnterCriticalSection(&XmpAllocationHookLock);

    if (pAllocRoutine)
    {
        XmpAllocRoutine = pAllocRoutine;
        XmpFreeRoutine = pFreeRoutine;
    }
    else
    {
        XmpAllocRoutine = XMemAllocDefault_X;
        XmpFreeRoutine = XMemFreeDefault_X;
    }

    LeaveCriticalSection(&XmpAllocationHookLock);
}

LPVOID WINAPI VirtualAllocEx_X(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    //TODO: Rewrite d3d11.x (WITH XDL, THIS
    //ISN'T NEGOTIABLE.) and
    //Add an VEH for resource tracking.
    if (flAllocationType & MEM_GRAPHICS)
    {
        //For placement update tracking.
        flProtect = PAGE_READONLY;

        //Optional but to make sure the memory
        //will be able to be read when 
        //placement update happens.
        flAllocationType |= MEM_COMMIT;
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
        return VirtualAlloc2(hProcess, lpAddress, dwSize, flAllocationType & MEM_MASK, flProtect & PAGE_MASK, &ExtParam, 1);

    if ((flAllocationType & MEM_4MB_PAGES) || Mappable.Is4MBPages)
        dwPageSize = PAGE_SIZE_4MB;
    else
        dwPageSize = PAGE_SIZE_64K;

    dwSize = (dwSize + (dwPageSize - 1)) & ~(dwPageSize - 1);
    lpAddress = (LPVOID)((ULONG_PTR)lpAddress & ~(dwPageSize - 1));

    if (flAllocationType & (MEM_RESERVE | MEM_TOP_DOWN))
    {
        Mappable = { dwSize, !!(flAllocationType & MEM_4MB_PAGES) };
        lpAddress = VirtualAlloc2(hProcess, lpAddress, dwSize, MEM_RESERVE | MEM_RESERVE_PLACEHOLDER | (flAllocationType & MEM_TOP_DOWN), PAGE_NOACCESS, &ExtParam, 1);

        if (lpAddress)
        {
            // Split the placeholder by the physical page size to enable individual mappings.
            // This comes with its own caveats. MEM_COMMIT and other Virtual* functions must
            // be aware of mappable memory allocations and handle them appropriately.
            for (SIZE_T dwOffset = dwPageSize; dwOffset < dwSize; dwOffset += dwPageSize)
                VirtualFreeEx(hProcess, (LPBYTE)lpAddress + dwOffset, dwPageSize, MEM_RELEASE | MEM_PRESERVE_PLACEHOLDER);

            AcquireSRWLockExclusive(&XwpMappableLock);
            XwpMappables[(ULONG_PTR)lpAddress] = Mappable;
            ReleaseSRWLockExclusive(&XwpMappableLock);
        }
    }

    if (lpAddress && (flAllocationType & MEM_COMMIT))
    {
        HANDLE hMap = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE, dwSize, nullptr, nullptr, 0);

        if (!hMap)
        {
            SetLastError(ERROR_OUTOFMEMORY);
            return nullptr;
        }

        for (SIZE_T dwOffset = 0; dwOffset < dwSize; dwOffset += dwPageSize)
        {
            LPVOID PageAddress = (LPBYTE)lpAddress + dwOffset;
            MapViewOfFile3(hMap, hProcess, PageAddress, dwOffset, dwPageSize, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0);
            VirtualAlloc2(hProcess, PageAddress, dwPageSize, MEM_COMMIT, flProtect & PAGE_MASK, nullptr, 0);
        }

        CloseHandle(hMap);
    }

    return lpAddress;
}


LPVOID WINAPI VirtualAlloc_X(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    return VirtualAllocEx_X(GetCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL WINAPI VirtualFreeEx_X(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
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
        if (Status) XwpMappables.erase((ULONG_PTR)AllocationBase);
        ReleaseSRWLockExclusive(&XwpMappableLock);
        return Status;
    }

    return VirtualFreeEx(hProcess, lpAddress, dwSize, dwFreeType);
}

BOOL WINAPI VirtualFree_X(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    return VirtualFreeEx_X(GetCurrentProcess(), lpAddress, dwSize, dwFreeType);
}

SIZE_T WINAPI VirtualQueryEx_X(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
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

SIZE_T WINAPI VirtualQuery_X(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
    return VirtualQueryEx_X(GetCurrentProcess(), lpAddress, lpBuffer, dwLength);
}

BOOL WINAPI VirtualProtectEx_X(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
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
        BOOL Status = VirtualProtectEx(hProcess, (LPVOID)BasePage, PageSize, flNewProtect, lpflOldProtect ? lpflOldProtect : &flOldProtect);

        for (ULONG_PTR Page = BasePage + PageSize; Page <= LastPage; Page += PageSize)
            Status |= VirtualProtectEx(hProcess, (LPVOID)Page, PageSize, flNewProtect, &flOldProtect);

        return Status;
    }

    return VirtualProtectEx(hProcess, lpAddress, dwSize, flNewProtect, lpflOldProtect ? lpflOldProtect : &flOldProtect);
}

BOOL WINAPI VirtualProtect_X(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
    return VirtualProtectEx_X(GetCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

BOOL WINAPI ToolingMemoryStatus_X(LPTOOLINGMEMORYSTATUS buffer)
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

BOOL WINAPI TitleMemoryStatus_X(LPTITLEMEMORYSTATUS Buffer)
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

PVOID WINAPI XMemAllocDefault_X(SIZE_T dwSize, ULONGLONG dwAttributes)
{
    auto attr = XALLOC_ATTRIBUTES{ dwAttributes };

    if (attr.s.dwMemoryType != XALLOC_MEMTYPE_HEAP)
    {
        DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;

        if (attr.s.dwPageSize <= XALLOC_PAGESIZE_4KB || attr.s.dwPageSize >= XALLOC_PAGESIZE_4MB)
            flAllocationType |= MEM_LARGE_PAGES;

        if (attr.s.dwMemoryType >= XALLOC_MEMTYPE_GRAPHICS_1 &&
            attr.s.dwMemoryType <= XALLOC_MEMTYPE_GRAPHICS_6)
        {
            flAllocationType |= MEM_GRAPHICS;
        }

        return VirtualAlloc_X(nullptr, dwSize, flAllocationType, PAGE_READWRITE);
    }

    void* ptr = _aligned_malloc(dwSize, 1ULL << max(4, attr.s.dwAlignment));

    if (ptr)
        memset(ptr, 0, dwSize);

    return ptr;
}

void WINAPI XMemFreeDefault_X(PVOID lpAddress, ULONGLONG dwAttributes)
{
    auto attr = XALLOC_ATTRIBUTES{ dwAttributes };

    if (attr.s.dwMemoryType != XALLOC_MEMTYPE_HEAP)
    {
        VirtualFree_X(lpAddress, 0, MEM_RELEASE);
        return;
    }

    _aligned_free(lpAddress);
}


void WINAPI XMemFree_X(PVOID pADDRESS, uint64_t dwAllocAttributes)
{
    return XmpFreeRoutine(pADDRESS, dwAllocAttributes);
}


PVOID WINAPI XMemAlloc_X(SIZE_T dwSize, uint64_t flags)
{
    return XmpAllocRoutine(dwSize, flags);
}

BOOL WINAPI AllocateTitlePhysicalPages_X(HANDLE hProcess, DWORD flAllocationType, PULONG_PTR NumberOfPages, PULONG_PTR PageArray)
{
    UNREFERENCED_PARAMETER(hProcess);

    if (!NumberOfPages || !PageArray ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
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

BOOL WINAPI FreeTitlePhysicalPages_X(HANDLE hProcess, ULONG_PTR NumberOfPages, PULONG_PTR PageArray)
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

PVOID WINAPI MapTitlePhysicalPages_X(PVOID VirtualAddress, ULONG_PTR NumberOfPages, DWORD flAllocationType, DWORD flProtect, PULONG_PTR PageArray)
{
    // TODO: Validate that PageArray contains contiguous 4MB blocks of 64K pages for MEM_4MB_PAGES

    if (!PageArray ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
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

    if (MEMORY_BASIC_INFORMATION mbi; !VirtualAddress || !VirtualQuery(VirtualAddress, &mbi, sizeof(mbi)) || mbi.State == MEM_FREE)
    {
        VirtualAddress = VirtualAlloc_X(
            VirtualAddress,
            NumberOfPages * PAGE_SIZE_64K,
            MEM_RESERVE | flAllocationType,
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
        MapViewOfFile3(XwpPhysicalMemory, nullptr, PageVirtualAddress, PhysicalOffset, dwPageSize, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0);
        VirtualAlloc2(nullptr, PageVirtualAddress, dwPageSize, MEM_COMMIT, flProtect & PAGE_MASK, nullptr, 0);
    }

    SetLastError(ERROR_SUCCESS);
    return VirtualAddress;
}

EXTERN_C HRESULT WINAPI MapTitleEsramPages(PVOID VirtualAddress, UINT NumberOfPages, DWORD flAllocationType, UINT const* PageArray)
{
    if (!VirtualAddress ||
        (flAllocationType & (MEM_LARGE_PAGES | MEM_4MB_PAGES)) == 0 ||
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
}

