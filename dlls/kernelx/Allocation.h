//Here lies most (if not, all) the memory code from
//Kernelx. All the code is based on XWine1's SlimEra
//Repo (https://github.com/XWine1/SlimEra). All credits
//to XWine1 and DaZombieKiller.
#pragma once
#include <Windows.h>
#include <bitset>

//Used in VirtualAlloc's flAllocationType.
//Should set flProtect to PAGE_READONLY for 
//placement update tracking and optionally force
//the memory to be commited (MEM_COMMIT).
#define MEM_GRAPHICS 0x10000000

//Used in VirtualAlloc's flAllocationType.
//Sets the allocated memory range from 2TiB to 4TiB.
#define MEM_TITLE    0x40000000

#define MEM_PHYSICAL_SIZE 0x400000000ULL // 16 GiB
#define MEM_ESRAM_SIZE 0x2000000ULL // 32 MiB

//Page sizes. Used for virtual memory implementation.
#define PAGE_SIZE_4KB (1ULL << 12)
#define PAGE_SIZE_64K (1ULL << 16)
#define PAGE_SIZE_2MB (1ULL << 21)
#define PAGE_SIZE_4MB (1ULL << 22)

//flAllocationType and flProtect (respectively) masks.
#define MEM_MASK (MEM_COMMIT | MEM_RESERVE | MEM_RESET | MEM_TOP_DOWN | MEM_WRITE_WATCH | MEM_RESET_UNDO)
#define PAGE_MASK (PAGE_NOACCESS | PAGE_READONLY | PAGE_READWRITE | PAGE_GUARD)

//Used by d3d11.x
EXTERN_C HRESULT WINAPI MapTitleEsramPages(
    _In_ PVOID VirtualAddress,
    _In_ UINT NumberOfPages,
    _In_ DWORD flAllocationType,
    _In_opt_ UINT const* PageArray);

//structs and definitions
typedef struct _TOOLINGMEMORYSTATUS
{
    DWORD dwLength;
    DWORD dwReserved;
    ULONGLONG ullTotalMem;
    ULONGLONG ullAvailMem;
    ULONGLONG ulPeakUsage;
    ULONGLONG ullPageTableUsage;
} TOOLINGMEMORYSTATUS, * PTOOLINGMEMORYSTATUS, * LPTOOLINGMEMORYSTATUS;

typedef union _XALLOC_ATTRIBUTES
{
    ULONGLONG dwAttributes;

    struct
    {
        ULONGLONG dwObjectType : 14;
        ULONGLONG dwPageSize : 2;
        ULONGLONG dwAllocatorId : 8;
        ULONGLONG dwAlignment : 5;
        ULONGLONG dwMemoryType : 4;
        ULONGLONG reserved : 31;
    } s;
} XALLOC_ATTRIBUTES, * PXALLOC_ATTRIBUTES, * LPXALLOC_ATTRIBUTES;

typedef enum _XALLOC_PAGESIZE
{
    XALLOC_PAGESIZE_4KB,
    XALLOC_PAGESIZE_64KB,
    XALLOC_PAGESIZE_4MB,
} XALLOC_PAGESIZE, * PXALLOC_PAGESIZE;

typedef enum _XALLOC_MEMTYPE
{
    XALLOC_MEMTYPE_HEAP,
    XALLOC_MEMTYPE_GRAPHICS_1,
    XALLOC_MEMTYPE_GRAPHICS_2,
    XALLOC_MEMTYPE_GRAPHICS_3,
    XALLOC_MEMTYPE_GRAPHICS_4,
    XALLOC_MEMTYPE_GRAPHICS_5,
    XALLOC_MEMTYPE_GRAPHICS_6,
    XALLOC_MEMTYPE_PHYSICAL_1,
    XALLOC_MEMTYPE_PHYSICAL_2,
    XALLOC_MEMTYPE_PHYSICAL_3,
} XALLOC_MEMTYPE, * PXALLOC_MEMTYPE;

typedef struct _TITLEMEMORYSTATUS
{
    DWORD dwLength;
    DWORD dwReserved;
    ULONGLONG ullTotalMem;
    ULONGLONG ullAvailMem;
    ULONGLONG ullLegacyUsed;
    ULONGLONG ullLegacyPeak;
    ULONGLONG ullLegacyAvail;
    ULONGLONG ullTitleUsed;
    ULONGLONG ullTitleAvail;
    ULONGLONG ullLegacyPageTableUsed;
    ULONGLONG ullTitlePageTableUsed;
} TITLEMEMORYSTATUS, * PTITLEMEMORYSTATUS, * LPTITLEMEMORYSTATUS;

typedef PVOID WINAPI XMEMALLOC_ROUTINE(
    _In_ SIZE_T dwSize,
    _In_ ULONGLONG dwAttributes);

typedef XMEMALLOC_ROUTINE* PXMEMALLOC_ROUTINE, * LPXMEMALLOC_ROUTINE;

typedef void WINAPI XMEMFREE_ROUTINE(
    _In_ PVOID lpAddress,
    _In_ ULONGLONG dwAttributes);

typedef XMEMFREE_ROUTINE* PXMEMFREE_ROUTINE, * LPXMEMFREE_ROUTINE;

//Usable with MapTitlePhysicalPages and D3DMapEsramMemory
typedef struct _MAPPABLE_MEM
{
    ULONG_PTR RegionSize : 63;
    ULONG_PTR Is4MBPages : 1;
} MAPPABLE_MEM, * PMAPPABLE_MEM;

//Helper
static DWORD WIN32_FROM_HRESULT(_In_ HRESULT hr)
{
    if (SUCCEEDED(hr))
        return ERROR_SUCCESS;

    return HRESULT_FACILITY(hr) == FACILITY_WIN32 ? HRESULT_CODE(hr) : hr;
}

static SRWLOCK XwpMappableLock = SRWLOCK_INIT;

static std::map<ULONG_PTR, MAPPABLE_MEM> XwpMappables;

static LPVOID MappableQuery(_In_opt_ LPCVOID lpAddress, _Out_ PMAPPABLE_MEM pMappable)
{
    auto it = XwpMappables.upper_bound((ULONG_PTR)lpAddress);

    if (it == XwpMappables.begin())
    {
        *pMappable = {};
        return nullptr;
    }

    --it;

    if (it->first + it->second.RegionSize <= (ULONG_PTR)lpAddress)
    {
        *pMappable = {};
        return nullptr;
    }

    *pMappable = it->second;
    return (LPVOID)it->first;
}

static std::bitset<(MEM_PHYSICAL_SIZE >> 16)> XwpPhysicalPages;

static SRWLOCK XwpPhysicalMemoryLock = SRWLOCK_INIT;

static HANDLE XwpPhysicalMemory = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE, MEM_PHYSICAL_SIZE, nullptr, nullptr, 0);

static HANDLE XwpEsramMemory = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE, MEM_ESRAM_SIZE, nullptr, nullptr, 0);

CRITICAL_SECTION XmpAllocationHookLock;

PVOID WINAPI XMemAllocDefault_X(SIZE_T dwSize, ULONGLONG dwAttributes);

void WINAPI XMemFreeDefault_X(PVOID lpAddress, ULONGLONG dwAttributes);

static PXMEMALLOC_ROUTINE XmpAllocRoutine = XMemAllocDefault_X;

static PXMEMFREE_ROUTINE XmpFreeRoutine = XMemFreeDefault_X;