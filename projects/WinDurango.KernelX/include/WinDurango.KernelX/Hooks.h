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

HMODULE User32 = nullptr;