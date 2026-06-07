#pragma comment(lib, "runtimeobject.lib")
#include "Hooks.h"
#include "kernelx.h"
#include "CurrentApp.h"
#include <detours/detours.h>
#include <wrl.h>
#include "MMDeviceEnumerator.h"

using namespace ABI::Windows::ApplicationModel::Store;

std::shared_ptr<wd::common::WinDurango> winDurango;

HRESULT WINAPI WdRoGetActivationFactory(_In_ HSTRING activatableClassId, _In_ REFIID iid, _COM_Outptr_ void **factory);

HRESULT WINAPI WdRoGetActivationFactoryCore(_In_ HSTRING activatableClassId, _In_ REFIID iid, _COM_Outptr_ void **factory);

static PFNROGETACTIVATIONFACTORY g_RoGetActivationFactory = RoGetActivationFactory;

static std::vector<PFNGETACTIVATIONFACTORY> g_RoEntryPoints;

HRESULT XWineGetImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ LPCSTR Import,
                       _Out_ PIMAGE_THUNK_DATA *pThunk)
{
importProcedure:
    if (ImportModule == nullptr)
        return E_INVALIDARG;

    if (pThunk == nullptr)
        return E_POINTER;

    if (Module == nullptr)
        Module = GetModuleHandleW(nullptr);

    auto dosHeader = (PIMAGE_DOS_HEADER)Module;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)Module + dosHeader->e_lfanew);
    auto directory = &ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

    if (directory->VirtualAddress == 0)
        return E_FAIL;

    auto peImports = (PIMAGE_IMPORT_DESCRIPTOR)((PBYTE)Module + directory->VirtualAddress);

    for (size_t i = 0; peImports[i].Name; i++)
    {
        if (GetModuleHandleA((LPCSTR)((PBYTE)Module + peImports[i].Name)) != ImportModule)
            continue;

        auto iatThunks = (PIMAGE_THUNK_DATA)((PBYTE)Module + peImports[i].FirstThunk);
        auto intThunks = (PIMAGE_THUNK_DATA)((PBYTE)Module + peImports[i].OriginalFirstThunk);

        for (size_t j = 0; intThunks[j].u1.AddressOfData; j++)
        {
            if ((intThunks[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG) != 0)
            {
                if (!IS_INTRESOURCE(Import))
                    continue;

                if (((intThunks[j].u1.Ordinal & ~IMAGE_ORDINAL_FLAG) == (ULONG_PTR)Import))
                {
                    *pThunk = &iatThunks[j];
                    return S_OK;
                }

                continue;
            }

            if (strcmp(((PIMAGE_IMPORT_BY_NAME)((PBYTE)Module + intThunks[j].u1.AddressOfData))->Name, Import))
                continue;

            *pThunk = &iatThunks[j];
            return S_OK;
        }
    }

    //Rodrigo Todescatto: I did this masterpiece. It looks awful, yet works perfectly. Never mess with something if it works.
    if (ImportModule == GetModuleHandleW(L"vccorlib110.dll"))
    {
        ImportModule = GetModuleHandleW(L"vccorlib120.dll");
        if (ImportModule)
        {
            goto importProcedure;
        }
        else
        {
            ImportModule = GetModuleHandleW(L"vccorlib140.dll");
            if (ImportModule)
            {
                goto importProcedure;
            }
        }
    }

    *pThunk = nullptr;
    return E_FAIL;
}

HRESULT XWinePatchImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ PCSTR Import, _In_ PVOID Function)
{
    DWORD protect;
    PIMAGE_THUNK_DATA pThunk;
    HRESULT hr = XWineGetImport(Module, ImportModule, Import, &pThunk);
    if (FAILED(hr))
        return hr;

    if (!VirtualProtect(&pThunk->u1.Function, sizeof(ULONG_PTR), PAGE_READWRITE, &protect))
        return GetLastError();

    pThunk->u1.Function = (ULONG_PTR)Function;

    if (!VirtualProtect(&pThunk->u1.Function, sizeof(ULONG_PTR), protect, &protect))
        return GetLastError();

    return S_OK;
}

HRESULT PatchNeededImports(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ PCSTR Import, _In_ PVOID Function)
{
    PIMAGE_THUNK_DATA pThunk;
    HRESULT hr = XWineGetImport(Module, ImportModule, Import, &pThunk);
    if (FAILED(hr))
        return hr;

    return XWinePatchImport(Module, ImportModule, Import, Function);
}

HMODULE GetRuntimeModule()
{
    std::array<const wchar_t *, 3> modules = {L"vccorlib110.dll", L"vccorlib120.dll", L"vccorlib140.dll"};
    HMODULE hModule = nullptr;

    for (auto &module : modules)
    {
        HMODULE Module = GetModuleHandleW(module);
        if (Module != nullptr)
        {
            hModule = Module;
            break;
        }
    }

    return hModule;
}

template <typename T> inline T GetVTableMethod(void *table_base, std::uintptr_t index)
{
    return (T)((*reinterpret_cast<std::uintptr_t **>(table_base))[index]);
}

HRESULT __stdcall EraAppActivateInstance(IActivationFactory *thisptr, IInspectable **instance)
{
    IInspectable *pInstance = nullptr;
    HRESULT hr = TrueActivateInstance(thisptr, &pInstance);
    if (FAILED(hr))
        return hr;

    *instance = new EraLicenseInformationWrapper(reinterpret_cast<ILicenseInformation*>(pInstance));
    return S_OK;
}

HRESULT __stdcall EraGetForCurrentThread(ICoreWindowStatic *pThis, CoreWindow **ppWindow)
{
    HRESULT hr = TrueGetForCurrentThread(pThis, ppWindow);
    if (FAILED(hr))
    {
        return hr;
    }

    if (*ppWindow == NULL)
    {
        return hr;
    }

    if (IsXboxCallee())
    {
        *reinterpret_cast<ICoreWindowEra **>(ppWindow) = new CoreWindowEra(*ppWindow);
    }

    return hr;
}

HWND __stdcall EraCreateWindowInBandEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int x,
                                       int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                       HINSTANCE hInstance, LPVOID lpParam, DWORD dwBand, DWORD dwTypeFlags)
{
    if (dwExStyle & WS_EX_NOREDIRECTIONBITMAP)
    {
        dwExStyle &= ~WS_EX_NOREDIRECTIONBITMAP;
    }

    return TrueCreateWindowInBandEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent,
                                    hMenu, hInstance, lpParam, dwBand, dwTypeFlags);
}

HRESULT __stdcall EraCoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid,
                                      LPVOID *ppv)
{
    HRESULT hr = TrueCoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
    if (FAILED(hr))
        return hr;

    if (riid == __uuidof(IMMDeviceEnumerator))
    {
        *ppv = new MMDeviceEnumeratorWrapper(static_cast<IMMDeviceEnumerator*>(*ppv));
        return S_OK;
    }

    return hr;
}

static void WdRoInitializeLibraries()
{
    static std::vector<std::wstring> s_RoLibraryNames = {
        L"Microsoft.Xbox.GameChat.dll",
        L"Microsoft.Xbox.Services.dll",
        L"Microsoft.XBox.Services.dll",
        L"windows.media.devices.dll",
        L"SystemUI.Api.dll",
        L"XboxUI.Api.dll"
    };

    for (auto name : s_RoLibraryNames)
    {
        HMODULE dll = LoadLibraryW(name.c_str());
        if (dll != nullptr)
        {
            if (auto pfn = GetProcAddress(dll, "DllGetActivationFactory"); pfn != nullptr)
            {
                g_RoEntryPoints.push_back(reinterpret_cast<PFNGETACTIVATIONFACTORY>(pfn));

                XWinePatchImport(dll, GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z", GetActivationFactoryRedirect);
            }
        }
    }
    if (auto dll = LoadLibraryW(L"winrt_x.dll"); dll != nullptr)
    {
        if (auto pfn = GetProcAddress(dll, "GetActivationFactory"); pfn != nullptr)
        {
            g_RoEntryPoints.push_back(reinterpret_cast<PFNGETACTIVATIONFACTORY>(pfn));

            XWinePatchImport(dll, GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z", GetActivationFactoryRedirect);
        }
    }
    if (auto dll = LoadLibraryW(L"windows.kinect.dll"); dll != nullptr)
    {
        if (auto pfn = GetProcAddress(dll, "GetActivationFactory"); pfn != nullptr)
        {
            g_RoEntryPoints.push_back(reinterpret_cast<PFNGETACTIVATIONFACTORY>(pfn));

            XWinePatchImport(dll, GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z", GetActivationFactoryRedirect);
        }
    }
}

static void WdRoInitializeClasses()
{

}

static BOOL WdRoInitialize(
    _Inout_ PINIT_ONCE InitOnce,
    _Inout_opt_ PVOID Parameter,
    _Out_opt_ PVOID *Context)
{
    WdRoInitializeLibraries();
    WdRoInitializeClasses();
    return TRUE;
}

static void WdRoEnsureInitialized()
{
    static volatile bool s_Initialized;
    static INIT_ONCE s_InitOnce = INIT_ONCE_STATIC_INIT;
    InitOnceExecuteOnce(&s_InitOnce, WdRoInitialize, nullptr, nullptr);
}

_Use_decl_annotations_
HRESULT WINAPI WdRoGetActivationFactoryCore(
    HSTRING activatableClassId,
    REFIID iid,
    void **factory)
{
    const wchar_t *rawString = WindowsGetStringRawBuffer(activatableClassId, nullptr);

    std::wstring rsws(rawString);
    std::string rss(rsws.begin(), rsws.end());

    if (rss == std::string("Windows.ApplicationModel.Core.CoreApplication"))
    {
        ComPtr<IActivationFactory> realFactory;

        HRESULT hr = RoGetActivationFactory(Microsoft::WRL::Wrappers::HStringReference::HStringReference(
                                                RuntimeClass_Windows_ApplicationModel_Core_CoreApplication)
                                                .Get(),
                                            IID_PPV_ARGS(&realFactory));

        if (FAILED(hr))
            return hr;

        ComPtr<CoreApplicationEra> wrappedFactory = Make<CoreApplicationEra>(realFactory);

        return wrappedFactory.CopyTo(iid, factory);
    }

    if (rss == std::string("Windows.UI.Core.CoreWindow"))
    {
        ComPtr<ICoreWindowStatic> coreWindowStatic;
        HRESULT hr = RoGetActivationFactory(
            Microsoft::WRL::Wrappers::HStringReference::HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(),
            IID_PPV_ARGS(&coreWindowStatic));
        if (FAILED(hr))
        {
            DebugBreak();
            return hr;
        }

        if (!TrueGetForCurrentThread)
        {
            *reinterpret_cast<void **>(&TrueGetForCurrentThread) = (*reinterpret_cast<void ***>(coreWindowStatic.Get()))[6];

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(reinterpret_cast<PVOID*>(&TrueGetForCurrentThread), EraGetForCurrentThread);
            DetourTransactionCommit();
        }

        return coreWindowStatic.CopyTo(iid, factory);
    }

    if (rss == std::string("Windows.ApplicationModel.Store.CurrentApp"))
    {
        HRESULT hr = g_RoGetActivationFactory(activatableClassId, iid, factory);

        if (FAILED(hr))
            return hr;

        if (!TrueActivateInstance) {
            TrueActivateInstance = GetVTableMethod<decltype(TrueActivateInstance)>(*factory, 6);

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(reinterpret_cast<PVOID*>(&TrueActivateInstance), EraAppActivateInstance);
            DetourTransactionCommit();
        }
    }

    for (auto pfn : g_RoEntryPoints)
    {
        ComPtr<IActivationFactory> temp;
        if (SUCCEEDED(pfn(activatableClassId, temp.GetAddressOf())))
        {
            HRESULT hr = temp.CopyTo(iid, factory);
            return hr;
        }
    }

    return g_RoGetActivationFactory(activatableClassId, iid, factory);
}

_Use_decl_annotations_
HRESULT WINAPI WdRoGetActivationFactory(
    HSTRING activatableClassId,
    REFIID iid,
    void **factory)
{
    winDurango = wd::common::WinDurango::GetInstance();
    if (!winDurango->inited())
    {
#ifndef CROSS_PLATFORM
        std::shared_ptr<wd::common::interfaces::storage::Directory> rootDir =
            std::make_shared<wd::impl::winrt::interfaces::storage::WinRTDirectory>("");
        winDurango->Init(rootDir);
#endif
    }
    WdRoEnsureInitialized();
    return WdRoGetActivationFactoryCore(activatableClassId, iid, factory);
}

HRESULT WINAPI GetActivationFactoryRedirect(PCWSTR str, REFIID riid, void **ppFactory)
{
    HRESULT hr = WdRoGetActivationFactory(HStringReference{str}.Get(), riid, ppFactory);

    if (FAILED(hr))
    {
        const wchar_t *rawString = WindowsGetStringRawBuffer(HStringReference{str}.Get(), nullptr);
        std::wstring rsws(rawString);
        std::string rss(rsws.begin(), rsws.end());
        winDurango->log.Log("WinDurango::KernelX", "EraRoGetActivationFactory: {}", rss); 
    }

    return hr;
}