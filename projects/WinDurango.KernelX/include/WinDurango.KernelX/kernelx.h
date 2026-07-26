//
// Created by DexrnZacAttack on 1/23/26 using zPc-i2.
//
#pragma once

#include <Windows.h>
#include <bitset>
#include <map>
#include "WinDurango.Common/Interfaces/Storage/Directory.h"
#include "WinDurango.Common/WinDurango.h"
#include "WinDurango.Implementation.WinRT/Interfaces/Storage/Directory.h"

// Most of those came from XWine1
//(More specifically, SlimEra).

// For Allocation Purposes
#define MEM_GRAPHICS 0x10000000
#define MEM_TITLE 0x40000000
#define PAGE_SIZE_4KB (1ULL << 12)
#define PAGE_SIZE_64K (1ULL << 16)
#define PAGE_SIZE_2MB (1ULL << 21)
#define PAGE_SIZE_4MB (1ULL << 22)
#define MEM_MASK (MEM_COMMIT | MEM_RESERVE | MEM_RESET | MEM_TOP_DOWN | MEM_WRITE_WATCH | MEM_RESET_UNDO)
#define PAGE_MASK (PAGE_NOACCESS | PAGE_READONLY | PAGE_READWRITE | PAGE_GUARD)
#define MEM_PHYSICAL_SIZE 0x400000000ULL // 16 GiB
static std::bitset<(MEM_PHYSICAL_SIZE >> 16)> XwpPhysicalPages;
static SRWLOCK XwpPhysicalMemoryLock = SRWLOCK_INIT;
static HANDLE XwpPhysicalMemory =
    CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE,
                       MEM_PHYSICAL_SIZE, nullptr, nullptr, 0);

// ESRAM stuff
#define MEM_ESRAM_SIZE 0x2000000ULL // 32 MiB
static HANDLE XwpEsramMemory = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE,
                                                  PAGE_READWRITE, SEC_RESERVE, MEM_ESRAM_SIZE, nullptr, nullptr, 0);

typedef struct _MAPPABLE_MEM
{
    ULONG_PTR RegionSize : 63;
    ULONG_PTR Is4MBPages : 1;
} MAPPABLE_MEM, *PMAPPABLE_MEM;

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

static DWORD WIN32_FROM_HRESULT(_In_ HRESULT hr)
{
    if (SUCCEEDED(hr))
        return ERROR_SUCCESS;

    return HRESULT_FACILITY(hr) == FACILITY_WIN32 ? HRESULT_CODE(hr) : hr;
}

typedef enum _CONSOLE_TYPE
{
    CONSOLE_TYPE_UNKNOWN,
    CONSOLE_TYPE_XBOX_ONE,
    CONSOLE_TYPE_XBOX_ONE_S,
    CONSOLE_TYPE_XBOX_ONE_X,
    CONSOLE_TYPE_XBOX_ONE_X_DEVKIT,
} CONSOLE_TYPE, *PCONSOLE_TYPE, *LPCONSOLE_TYPE;

EXTERN_C CONSOLE_TYPE WINAPI GetConsoleType();

typedef struct _SYSTEMOSVERSIONINFO
{
    BYTE MajorVersion;
    BYTE MinorVersion;
    WORD BuildNumber;
    WORD Revision;
} SYSTEMOSVERSIONINFO, *PSYSTEMOSVERSIONINFO, *LPSYSTEMOSVERSIONINFO;

EXTERN_C VOID WINAPI GetSystemOSVersion(_Out_ LPSYSTEMOSVERSIONINFO lpVersionInformation);

typedef struct _PROCESSOR_SCHEDULING_STATISTICS
{
    ULONGLONG RunningTime;
    ULONGLONG IdleTime;
    ULONGLONG GlobalTime;
} PROCESSOR_SCHEDULING_STATISTICS, *PPROCESSOR_SCHEDULING_STATISTICS, *LPPROCESSOR_SCHEDULING_STATISTICS;

EXTERN_C VOID WINAPI QueryProcessorSchedulingStatistics(_Out_ PPROCESSOR_SCHEDULING_STATISTICS lpStatistics);

EXTERN_C BOOL WINAPI SetThreadpoolAffinityMask(_Inout_ PTP_POOL Pool, _In_ DWORD_PTR dwThreadAffinityMask);

EXTERN_C BOOL WINAPI SetThreadName(_In_ HANDLE hThread, _In_ PCWSTR lpThreadName);

EXTERN_C BOOL WINAPI GetThreadName(_In_ HANDLE hThread, _Out_ PWSTR lpThreadName, _In_ SIZE_T dwBufferLength,
                                   _Out_ PSIZE_T pdwReturnLength);

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
} TITLEMEMORYSTATUS, *PTITLEMEMORYSTATUS, *LPTITLEMEMORYSTATUS;

EXTERN_C BOOL WINAPI TitleMemoryStatus(_Inout_ LPTITLEMEMORYSTATUS lpBuffer);

EXTERN_C BOOL WINAPI JobTitleMemoryStatus(_Inout_ LPTITLEMEMORYSTATUS lpBuffer);

typedef struct _TOOLINGMEMORYSTATUS
{
    DWORD dwLength;
    DWORD dwReserved;
    ULONGLONG ullTotalMem;
    ULONGLONG ullAvailMem;
    ULONGLONG ulPeakUsage;
    ULONGLONG ullPageTableUsage;
} TOOLINGMEMORYSTATUS, *PTOOLINGMEMORYSTATUS, *LPTOOLINGMEMORYSTATUS;

EXTERN_C BOOL WINAPI ToolingMemoryStatus(_Inout_ LPTOOLINGMEMORYSTATUS lpBuffer);

EXTERN_C BOOL WINAPI AllocateTitlePhysicalPages(_In_ HANDLE hProcess, _In_ DWORD flAllocationType,
                                                _Inout_ PULONG_PTR NumberOfPages, _Out_ PULONG_PTR PageArray);

EXTERN_C BOOL WINAPI FreeTitlePhysicalPages(_In_ HANDLE hProcess, _In_ ULONG_PTR NumberOfPages,
                                            _In_ PULONG_PTR PageArray);

EXTERN_C PVOID WINAPI MapTitlePhysicalPages(_In_opt_ PVOID VirtualAddress, _In_ ULONG_PTR NumberOfPages,
                                            _In_ DWORD flAllocationType, _In_ DWORD flProtect,
                                            _In_ PULONG_PTR PageArray);

// This is not a standard ERA function, it is provided for convenience
// to aid in the implementation of the Direct3D D3DMapEsramMemory API.
EXTERN_C HRESULT WINAPI MapTitleEsramPages(_In_ PVOID VirtualAddress, _In_ UINT NumberOfPages,
                                           _In_ DWORD flAllocationType, _In_opt_ UINT const *PageArray);

typedef union _XALLOC_ATTRIBUTES {
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
} XALLOC_ATTRIBUTES, *PXALLOC_ATTRIBUTES, *LPXALLOC_ATTRIBUTES;

typedef enum _XALLOC_PAGESIZE
{
    XALLOC_PAGESIZE_4KB,
    XALLOC_PAGESIZE_64KB,
    XALLOC_PAGESIZE_4MB,
} XALLOC_PAGESIZE, *PXALLOC_PAGESIZE;

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
} XALLOC_MEMTYPE, *PXALLOC_MEMTYPE;

EXTERN_C PVOID WINAPI XMemAllocDefault(_In_ SIZE_T dwSize, _In_ ULONGLONG dwAttributes);

EXTERN_C void WINAPI XMemFreeDefault(_In_ PVOID lpAddress, _In_ ULONGLONG dwAttributes);

EXTERN_C PVOID WINAPI XMemAlloc(_In_ SIZE_T dwSize, _In_ ULONGLONG dwAttributes);

EXTERN_C void WINAPI XMemFree(_In_ PVOID lpAddress, _In_ ULONGLONG dwAttributes);

EXTERN_C LPVOID WINAPI EraVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

typedef PVOID WINAPI XMEMALLOC_ROUTINE(_In_ SIZE_T dwSize, _In_ ULONGLONG dwAttributes);

typedef XMEMALLOC_ROUTINE *PXMEMALLOC_ROUTINE, *LPXMEMALLOC_ROUTINE;

typedef void WINAPI XMEMFREE_ROUTINE(_In_ PVOID lpAddress, _In_ ULONGLONG dwAttributes);

typedef XMEMFREE_ROUTINE *PXMEMFREE_ROUTINE, *LPXMEMFREE_ROUTINE;

EXTERN_C void WINAPI XMemSetAllocationHooks(_In_opt_ PXMEMALLOC_ROUTINE pAllocRoutine,
                                            _In_opt_ PXMEMFREE_ROUTINE pFreeRoutine);

// More XMem stuff
CRITICAL_SECTION XmpAllocationHookLock;
static PXMEMALLOC_ROUTINE XmpAllocRoutine = XMemAllocDefault;
static PXMEMFREE_ROUTINE XmpFreeRoutine = XMemFreeDefault;

extern std::shared_ptr<wd::common::WinDurango> winDurango;

EXTERN_C HANDLE __stdcall EraCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

EXTERN_C HANDLE __stdcall EraCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

EXTERN_C HANDLE __stdcall EraCreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                                         DWORD dwCreationDisposition,
                                         LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams);

EXTERN_C BOOL __stdcall EraCreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

EXTERN_C HMODULE __stdcall EraLoadLibraryExA(LPCSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags);

EXTERN_C HMODULE __stdcall EraLoadLibraryW(LPCWSTR lpLibFileName);

EXTERN_C DWORD __stdcall EraGetFileAttributesW(LPCWSTR lpFileName);

EXTERN_C BOOL __stdcall EraGetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
                                                LPVOID lpFileInformation);

EXTERN_C HANDLE __stdcall EraFindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);

EXTERN_C BOOL __stdcall EraDeleteFileW(LPCWSTR lpFileName);

EXTERN_C HMODULE __stdcall EraLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);