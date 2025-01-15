#include "pch.h"

#include "ConnectedStorage/ConnectedStorage.h"

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);

    if (WinDurango::impl::s_userStorage == nullptr)
    {
        WinDurango::impl::s_userStorage = new WinDurango::impl::ConnectedStorage();
        WinDurango::impl::s_userStorage->InitializeStorage(L"UserStorage").get();
    }

    if (WinDurango::impl::s_machineStorage == nullptr)
    {
        WinDurango::impl::s_machineStorage = new WinDurango::impl::ConnectedStorage( );
        WinDurango::impl::s_machineStorage->InitializeStorage(L"MachineStorage").get( );
    }

    return 1;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID reserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        printf("[winrt_x] DllMain invoked");
        CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
    }

    return TRUE;
}