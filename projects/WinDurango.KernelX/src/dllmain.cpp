#include "Hooks.h"
#include "kernelx.h"
#include "Logan.h"
#include "ForzaThreadHook.h"
#include "D3D11Peggle2Hook.h"

static DWORD ReasonForCall = 0;
#define RETURN_IF_FAILED(hr) if (FAILED(hr)) return hr

void KernelxInitialize(HINSTANCE hinstDLL)
{
    if (!GetConsoleWindow())
    {
        AllocConsole();
        FILE *f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
        freopen_s(&f, "CONIN$", "r", stdin);

        SetConsoleTitleW(L"WinDurango");
    }

    auto AppxManifestFile = ReadFile(L"AppxManifest.xml");
    auto TitleID = ExtractAttribute(AppxManifestFile, L"TitleId");
    auto Version = ExtractAttribute(AppxManifestFile, L"Version");

    if (ReasonForCall == DLL_PROCESS_ATTACH || ReasonForCall == DLL_THREAD_ATTACH)
    {
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        XWinePatchImport(GetModuleHandleW(nullptr), GetRuntimeModule(),
                         "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z",
                         GetActivationFactoryRedirect);

        //This is needed for DXVK.
        if (!User32) User32 = LoadLibraryA("user32.dll");
        if (User32)
        {
            FARPROC CreateWindowInBandEx = GetProcAddress(User32, "CreateWindowInBandEx");
            TrueCreateWindowInBandEx = reinterpret_cast<PCreateWindowInBandEx>(CreateWindowInBandEx);
            DetourAttach(&reinterpret_cast<PVOID &>(TrueCreateWindowInBandEx), EraCreateWindowInBandEx);
        }

        //Halo 5: Guardians
        if (TitleID == L"0D174C79")
        {
            HMODULE XboxLiveWrapper = LoadLibraryW(L"XboxLiveServicesWrapperLib_Release.dll");
            XWinePatchImport(XboxLiveWrapper, GetRuntimeModule(),
                         "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z",
                         GetActivationFactoryRedirect);

            *(void**)&P_Halo5VectoredExceptionHandler = (char*)GetModuleHandleW(nullptr) + 0xA54024;
            DetourAttach((void**)&P_Halo5VectoredExceptionHandler, &D_Halo5VectoredExceptionHandler);
        }

        //Forza Horizon 2 Demo
        if (TitleID == L"265E1020" && Version == L"1.0.0.5")
        {
            *(void**)&P_StartForzaThread = (char*)GetModuleHandleW(nullptr) + 0xFE6920;
            DetourAttach((void**)&P_StartForzaThread, &D_StartForzaThread);
        }

        //Forza Horizon 2
        if (TitleID == L"1A96545B" && Version == L"1.0.0.64")
        {
            *(void**)&P_StartForzaThread = (char*)GetModuleHandleW(nullptr) + 0x1081A90;
            DetourAttach((void**)&P_StartForzaThread, &D_StartForzaThread);
            *(void**)&P_FmodThreadProc = (char*)GetModuleHandleW(nullptr) + 0x19D3F80;
            DetourAttach((void**)&P_FmodThreadProc, &D_FmodThreadProc);
        }

        //Forza Horizon 2 Presents Fast & Furious
        if (TitleID == L"5A9771A4" && Version == L"1.0.0.6")
        {
            *(void**)&P_StartForzaThread = (char*)GetModuleHandleW(nullptr) + 0x10A7C00;
            DetourAttach((void**)&P_StartForzaThread, &D_StartForzaThread);
        }

        //Peggle 2
        if (TitleID == L"32966611" && Version == L"1.0.7.0")
        {
            HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&g_pFactory));
            if (FAILED(hr)) printf("Peggle 2: Failed to create the DXGI Factory object! Error: 0x%X\n", hr);
            g_lpIDXGIFactory2Vtbl = *reinterpret_cast<IDXGIFactory2Vtbl**>(g_pFactory);
            pCreateSwapChainForCoreWindow = g_lpIDXGIFactory2Vtbl->CreateSwapChainForCoreWindow;
            DetourAttach(reinterpret_cast<PVOID*>(&pCreateSwapChainForCoreWindow), &CreateSwapChainForCoreWindow_Hook);

            HMODULE hD3D11;
            hD3D11 = LoadLibraryW(L"d3d11.dll");
            reinterpret_cast<PVOID&>(pD3D11CreateDevice) = GetProcAddress(hD3D11, "D3D11CreateDevice");
            DetourAttach(reinterpret_cast<PVOID*>(&pD3D11CreateDevice), &D3D11CreateDevice_Hook);
        }

        DetourAttach(&reinterpret_cast<PVOID&>(TrueCoCreateInstance), EraCoCreateInstance);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCoCreateInstanceEx), EraCoCreateInstanceEx);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueDeviceIoControl), EraDeviceIoControl);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryA), EraCreateDirectoryA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryW), EraCreateDirectoryW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFileW), EraCreateFileW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFile2), EraCreateFile2);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFileA), EraCreateFileA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), EraGetFileAttributesW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesA), EraGetFileAttributesA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueSetFileAttributesA), EraSetFileAttributesA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), EraGetFileAttributesExW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), EraFindFirstFileW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueFindFirstFileA), EraFindFirstFileA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueFindNextFileA), EraFindNextFileA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueFindNextFileW), EraFindNextFileW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), EraDeleteFileW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryW), EraLoadLibraryW);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExA), EraLoadLibraryExA);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileInformationByHandleEx), EraGetFileInformationByHandleEx);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueReadFile), EraReadFile);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueWriteFile), EraWriteFile);
        DetourAttach(&reinterpret_cast<PVOID&>(TrueGetProcAddress), EraGetProcAddress);
        DetourTransactionCommit();
    }
    else if (ReasonForCall == DLL_PROCESS_DETACH || ReasonForCall == DLL_THREAD_DETACH)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCoCreateInstance), EraCoCreateInstance);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCoCreateInstanceEx), EraCoCreateInstanceEx);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueDeviceIoControl), EraDeviceIoControl);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryA), EraCreateDirectoryA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryW), EraCreateDirectoryW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFileW), EraCreateFileW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFile2), EraCreateFile2);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFileA), EraCreateFileA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), EraGetFileAttributesW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesA), EraGetFileAttributesA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueSetFileAttributesA), EraSetFileAttributesA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), EraGetFileAttributesExW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), EraFindFirstFileW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueFindFirstFileA), EraFindFirstFileA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueFindNextFileA), EraFindNextFileA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueFindNextFileW), EraFindNextFileW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), EraDeleteFileW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryW), EraLoadLibraryW);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExA), EraLoadLibraryExA);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileInformationByHandleEx), EraGetFileInformationByHandleEx);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueReadFile), EraReadFile);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueWriteFile), EraWriteFile);
        DetourDetach(&reinterpret_cast<PVOID&>(TrueGetProcAddress), EraGetProcAddress);
        DetourTransactionCommit();
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    InitializeCriticalSection(&XmpAllocationHookLock);
    if (DetourIsHelperProcess()) return TRUE;

    ReasonForCall = ul_reason_for_call;

    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
    {
        ReasonForCall = ul_reason_for_call;
        return TRUE;
    }

    return QueueUserAPC([](ULONG_PTR dwParam) { KernelxInitialize(reinterpret_cast<HINSTANCE>(dwParam)); },
                        GetCurrentThread(), reinterpret_cast<ULONG_PTR>(hModule)) != 0;
}