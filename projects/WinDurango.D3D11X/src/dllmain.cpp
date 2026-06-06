#include "d3d11.x.h"
#include "ID3D11GraphicsMemoryManager.h"
#include "unknown.g.h"
#include "d3d11_x.g.h"

std::shared_ptr<wd::common::WinDurango> p_wd;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // handle to DLL module
                    DWORD fdwReason,    // reason for calling function
                    LPVOID lpvReserved) // reserved
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        GetCombaseVersion();

        ID3D11GraphicsMemoryManager* MemoryManager;
        d3d11CreateInstance<D3D11GraphicsMemoryManager>(g_ABI, (void**)&MemoryManager);
        MemoryManager->RegisterVEH();

        p_wd = wd::common::WinDurango::GetInstance();
        return TRUE;
    }
}