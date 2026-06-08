#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "version.lib")
#include "unknown.g.h"
#include "xcom/base.h"
#include <Windows.h>
#include <bitset>
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <map>
#include <mutex>
#include <algorithm>
#include <cstdint>
#include <DirectXTex.h>
#include "WinDurango.Common/WinDurango.h"

extern std::shared_ptr<wd::common::WinDurango> p_wd;

// We use that to know the OS version.
abi_t g_ABI{};

// Immediate Context fence object.
BOOL m_Fence = TRUE;

// Multimap for placement update
std::multimap<void *, void *> g_ResourceMap;
std::mutex g_ResourceMapMutex;

#pragma comment(lib, "onecore.lib")
#pragma comment(lib, "kernel32.lib")

void GetCombaseVersion()
{
    DWORD FileVersionSize = GetFileVersionInfoSizeW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL);
    if (!FileVersionSize)
    {
        MessageBoxW(nullptr,
                    L"Couldn't get the combase version info size! Make sure you have EmbeddedXvd in the game "
                    L"root/Mount folder.",
                    L"D3D11.X Error!", MB_OK);
    }

    BYTE *Data = new BYTE[FileVersionSize];
    BOOL ret = GetFileVersionInfoW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL, FileVersionSize, Data);
    if (!ret)
    {
        MessageBoxW(
            nullptr,
            L"Couldn't get the combase version info! Make sure you have EmbeddedXvd in the game root/Mount folder.",
            L"D3D11.X Error!", MB_OK);
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
            L"D3D11.X Error!", MB_OK);
        delete[] Data;
    }

    DWORD major = HIWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD minor = LOWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD build = HIWORD(pFixedFileInfo->dwProductVersionLS);
    DWORD revision = LOWORD(pFixedFileInfo->dwProductVersionLS);

    g_ABI.Major = major;
    g_ABI.Minor = minor;
    g_ABI.Build = build;
    g_ABI.Revision = revision;
}

inline void CalculatePitch(uint32_t Width, uint32_t Height, DXGI_FORMAT Format, uint32_t* pRowPitch, uint32_t* pSlicePitch)
{;
    SIZE_T rowPitch = 0;
    SIZE_T slicePitch = 0;
    DirectX::ComputePitch(Format, Width, Height, rowPitch, slicePitch);

    (*pRowPitch) = rowPitch;
    (*pSlicePitch) = slicePitch;
}

inline bool IsFloatFormat(DXGI_FORMAT Format)
{
    switch (Format)
    {
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
    case DXGI_FORMAT_R32G32B32_FLOAT:
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
    case DXGI_FORMAT_R32G32_FLOAT:
    case DXGI_FORMAT_R11G11B10_FLOAT:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R16_FLOAT:
        return true;
    default:
        return false;
    }
}

inline bool IsUINTFormat(DXGI_FORMAT Format)
{
    switch (Format)
    {
    case DXGI_FORMAT_R32G32B32A32_UINT:
    case DXGI_FORMAT_R32G32B32_UINT:
    case DXGI_FORMAT_R16G16B16A16_UINT:
    case DXGI_FORMAT_R32G32_UINT:
    case DXGI_FORMAT_R10G10B10A2_UINT:
    case DXGI_FORMAT_R16G16_UINT:
    case DXGI_FORMAT_R32_UINT:
    case DXGI_FORMAT_R16_UINT:
    case DXGI_FORMAT_R8G8B8A8_UINT:
    case DXGI_FORMAT_R8G8_UINT:
    case DXGI_FORMAT_R8_UINT:
        return true;
    default:
        return false;
    }
}

inline bool IsUnormFormat(DXGI_FORMAT Format)
{
    switch (Format)
    {
    case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R16G16_UNORM:
    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_A8_UNORM:
    case DXGI_FORMAT_R1_UNORM:
    case DXGI_FORMAT_R8G8_B8G8_UNORM:
    case DXGI_FORMAT_G8R8_G8B8_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
        return true;
    default:
        return false;
    }
}
