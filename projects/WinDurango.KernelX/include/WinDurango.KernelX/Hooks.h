#pragma once
#pragma comment(lib, "runtimeobject.lib")
#include <Shlwapi.h>
#include <codecvt>
#include <filesystem>
#include <locale>
#include <string>
#include <windows.applicationmodel.core.h>
#include <windows.h>
#include <winstring.h>
#include <wrl/wrappers/corewrappers.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/windows.storage.provider.h>
#include <wrl/client.h>
#include <detours/detours.h>
#include "CurrentApp.h"
#include "EraCoreWindow.h"
#include "EraCoreApplication.h"
#include "EraNetworking.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

typedef int32_t (__stdcall *GetActivationFactory_t)(HSTRING classId, IActivationFactory** factory);

// Provided by XWine1, all credits to them.
//(This is from the old impl but we can use it just fine).
HRESULT XWineGetImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ LPCSTR Import,
                       _Out_ PIMAGE_THUNK_DATA *pThunk);
HRESULT XWinePatchImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ PCSTR Import, _In_ PVOID Function);
HRESULT PatchNeededImports(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ PCSTR Import, _In_ PVOID Function);
HMODULE GetRuntimeModule();
inline HRESULT WINAPI EraRoGetActivationFactory(HSTRING classId, REFIID iid, void **factory);
HRESULT WINAPI GetActivationFactoryRedirect(PCWSTR str, REFIID riid, void **ppFactory);

HRESULT STDMETHODCALLTYPE EraAppActivateInstance(IActivationFactory *thisptr, IInspectable **instance);

template <typename T> inline T GetVTableMethod(void *table_base, std::uintptr_t index);

inline bool IsClassName(HSTRING classId, const char *classIdName)
{
    const wchar_t *classIdString = WindowsGetStringRawBuffer(classId, nullptr);
    std::wstring classIdWString(classIdString);
    const std::string classIdStringUTF8(classIdWString.begin(), classIdWString.end());

    return (classIdStringUTF8 == classIdName);
}

HRESULT(WINAPI *TrueActivateInstance)(IActivationFactory *thisptr, IInspectable **instance) = nullptr;

typedef HRESULT(WINAPI *PFNROGETACTIVATIONFACTORY)(HSTRING, REFIID, void **); // TODO: Put somewhere

#define IsXboxCallee() IsXboxAddress(_ReturnAddress())

BOOL IsXboxModule(HMODULE module)
{
    return module == GetModuleHandleW(nullptr);
}

inline BOOL IsXboxAddress(const PVOID Address)
{
    HMODULE hModule;

    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCWSTR>(Address), &hModule))
        return FALSE;

    return IsXboxModule(hModule);
}

HRESULT(STDMETHODCALLTYPE *TrueGetForCurrentThread)(ICoreWindowStatic *staticWindow, CoreWindow **window);

HRESULT STDMETHODCALLTYPE EraGetForCurrentThread(ICoreWindowStatic *pThis, CoreWindow **ppWindow);

typedef HWND(WINAPI *PCreateWindowInBandEx)(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
                                            int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                            HINSTANCE hInstance, LPVOID lpParam, DWORD dwBand, DWORD dwTypeFlags);

PCreateWindowInBandEx TrueCreateWindowInBandEx = 0;

HWND WINAPI EraCreateWindowInBandEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int x,
                                    int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
                                    LPVOID lpParam, DWORD dwBand, DWORD dwTypeFlags);

HRESULT(WINAPI *TrueCoCreateInstance)(_In_ REFCLSID rclsid, _In_opt_ LPUNKNOWN pUnkOuter, _In_ DWORD dwClsContext,
                                      _In_ REFIID riid,
                                      _COM_Outptr_ _At_(*ppv, _Post_readable_size_(_Inexpressible_(varies)))
                                          LPVOID FAR *ppv) = CoCreateInstance;

HRESULT __stdcall EraCoCreateInstance(_In_ REFCLSID rclsid, _In_opt_ LPUNKNOWN pUnkOuter, _In_ DWORD dwClsContext,
                                      _In_ REFIID riid,
                                      _COM_Outptr_ _At_(*ppv, _Post_readable_size_(_Inexpressible_(varies)))
                                          LPVOID FAR *ppv);

HANDLE(WINAPI* TrueCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFileW;
HANDLE(WINAPI* TrueCreateFileA)(LPCSTR lpFileName,DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFileA;

HANDLE(WINAPI* TrueCreateFile2)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
DWORD dwCreationDisposition, LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams) = CreateFile2;

BOOL(WINAPI* TrueCreateDirectoryA)(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) = CreateDirectoryA;
BOOL(WINAPI* TrueCreateDirectoryW)(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) = CreateDirectoryW;

DWORD(WINAPI* TrueGetFileAttributesW)(LPCWSTR lpFileName) = GetFileAttributesW;
BOOL(WINAPI* TrueGetFileAttributesExW)(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation) = GetFileAttributesExW;

HANDLE(WINAPI* TrueFindFirstFileW)(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) = FindFirstFileW;

BOOL(WINAPI* TrueDeleteFileW)(LPCWSTR lpFileName) = DeleteFileW;

HMODULE(WINAPI* TrueLoadLibraryExW)(LPCWSTR lpLibFileName, HANDLE  hFile, DWORD dwFlags) = LoadLibraryExW;
HMODULE(WINAPI* TrueLoadLibraryExA)(LPCSTR lpLibFileName, HANDLE  hFile, DWORD dwFlags) = LoadLibraryExA;
HMODULE(WINAPI* TrueLoadLibraryW)(LPCWSTR lpLibFileName) = LoadLibraryW;

DWORD(WINAPI *TrueGetFileAttributesA)(LPCSTR lpFileName) = GetFileAttributesA;

BOOL(WINAPI *TrueSetFileAttributesA)(LPCSTR lpFileName, DWORD dwFileAttributes) = SetFileAttributesA;

HANDLE(WINAPI* TrueFindFirstFileA)(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) = FindFirstFileA;

BOOL(WINAPI* TrueFindNextFileA)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) = FindNextFileA;

BOOL(WINAPI* TrueFindNextFileW)(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) = FindNextFileW;

BOOL(WINAPI *TrueGetFileInformationByHandleEx)(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize) = GetFileInformationByHandleEx;

BOOL(WINAPI* TrueReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) = ReadFile;

BOOL(WINAPI* TrueWriteFile)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) = WriteFile;

FARPROC(WINAPI* TrueGetProcAddress)(HMODULE hModule, LPCSTR lpProcName) = GetProcAddress;

HRESULT(WINAPI* TrueCoCreateInstanceEx)(REFCLSID Clsid, IUnknown* punkOuter, DWORD dwClsCtx, COSERVERINFO* pServerInfo, DWORD dwCount, MULTI_QI* pResults) = CoCreateInstanceEx;

HMODULE User32 = nullptr;

LONG(WINAPI *P_Halo5VectoredExceptionHandler)(_EXCEPTION_POINTERS *ExceptionInfo) = nullptr;

LONG D_Halo5VectoredExceptionHandler(_EXCEPTION_POINTERS *ExceptionInfo)
{
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
    {
        if (ExceptionInfo->ExceptionRecord->ExceptionInformation[0] == 1)
        {
            ULONG LastProtect = 0;
            LPVOID ExceptionAddress = (LPVOID)ExceptionInfo->ExceptionRecord->ExceptionInformation[1];
            VirtualProtect(ExceptionAddress, 1, PAGE_READWRITE, &LastProtect);

            return EXCEPTION_CONTINUE_EXECUTION;
        }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}