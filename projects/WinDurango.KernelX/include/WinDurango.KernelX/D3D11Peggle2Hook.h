#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <winrt/Windows.ApplicationModel.h>
#include <detours/detours.h>
#include <wrl.h>
#include <CoreWindow.h>
#include "EraCoreWindow.h"

using namespace Microsoft::WRL;

struct IUnknownVtbl : IUnknown
{
    HRESULT(*QueryInterface)(IUnknown* This, REFIID riid, void** ppvObject);
    ULONG(*AddRef)(IUnknown* This);
    ULONG(*Release)(IUnknown* This);
};

struct IDXGIObjectVtbl : IUnknownVtbl
{
    HRESULT(*SetPrivateData)(IDXGIObject* This, REFGUID Name, UINT DataSize, void const* pData);
    HRESULT(*SetPrivateDataInterface)(IDXGIObject* This, REFGUID Name, IUnknown const* pUnknown);
    HRESULT(*GetPrivateData)(IDXGIObject* This, REFGUID Name, UINT* pDataSize, void* pData);
    HRESULT(*GetParent)(IDXGIObject* This, REFGUID riid, void** ppParent);
};

struct IDXGIFactoryVtbl : IDXGIObjectVtbl
{
    HRESULT(*EnumAdapters)(IDXGIFactory* This, UINT Adapter, IDXGIAdapter** ppAdapter);
    HRESULT(*MakeWindowAssociation)(IDXGIFactory* This, HWND WindowHandle, UINT Flags);
    HRESULT(*GetWindowAssociation)(IDXGIFactory* This, HWND* pWindowHandle);
    HRESULT(*CreateSwapChain)(IDXGIFactory* This, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
    HRESULT(*CreateSoftwareAdapter)(IDXGIFactory* This, HMODULE Module, IDXGIAdapter** ppAdapter);
};

struct IDXGIFactory1Vtbl : IDXGIFactoryVtbl
{
    HRESULT(*EnumAdapters1)(IDXGIFactory1* This, UINT Adapter, IDXGIAdapter1** ppAdapter);
    BOOL(*IsCurrent)(IDXGIFactory1* This);
};

struct IDXGIFactory2Vtbl : IDXGIFactory1Vtbl
{
    HRESULT(*CreateSwapChainForHwnd)(IDXGIFactory2* This, IUnknown* pDevice, HWND hWnd, DXGI_SWAP_CHAIN_DESC1 const* pDesc, DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
    HRESULT(*CreateSwapChainForCoreWindow)(IDXGIFactory2* This, IUnknown* pDevice, IUnknown* pWindow, DXGI_SWAP_CHAIN_DESC1 const* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
    HRESULT(*GetSharedResourceAdapterLuid)(IDXGIFactory2* This, HANDLE hResource, LUID* pLuid);
    HRESULT(*RegisterStereoStatusWindow)(IDXGIFactory2* This, HWND WindowHandle, UINT wMsg, DWORD* pdwCookie);
    HRESULT(*RegisterStereoStatusEvent)(IDXGIFactory2* This, HANDLE hEvent, DWORD* pdwCookie);
    HRESULT(*UnregisterStereoStatus)(IDXGIFactory2* This, DWORD dwCookie);
    HRESULT(*RegisterOcclusionStatusWindow)(IDXGIFactory2* This, HWND WindowHandle, UINT wMsg, DWORD* pdwCookie);
    HRESULT(*RegisterOcclusionStatusEvent)(IDXGIFactory2* This, HANDLE hEvent, DWORD* pdwCookie);
    HRESULT(*UnregisterOcclusionStatus)(IDXGIFactory2* This, DWORD dwCookie);
    HRESULT(*CreateSwapChainForComposition)(IDXGIFactory2* This, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC1 const* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
};

static decltype(IDXGIFactory2Vtbl::CreateSwapChainForCoreWindow) pCreateSwapChainForCoreWindow;

static decltype(&D3D11CreateDevice) pD3D11CreateDevice;

IDXGIFactory2Vtbl* g_lpIDXGIFactory2Vtbl = nullptr;
IDXGIFactory2 *g_pFactory = nullptr;

#define CREATE_DEVICE_FLAG_MASK (D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SWITCH_TO_REF | \
        D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS | D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUGGABLE | \
        D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY | D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT | D3D11_CREATE_DEVICE_VIDEO_SUPPORT)

#define DXGI_SWAPCHAIN_FLAG_MASK (DXGI_SWAP_CHAIN_FLAG_NONPREROTATED | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE \
		| DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT | DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER | DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT \
		| DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER | DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO | DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO \
		| DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING \
		| DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS) 

HRESULT D3D11CreateDevice_Hook(
_In_opt_ IDXGIAdapter *pAdapter,
D3D_DRIVER_TYPE DriverType,
HMODULE Software,
UINT Flags,
_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL *pFeatureLevels,
UINT FeatureLevels,
UINT SDKVersion,
_COM_Outptr_opt_ ID3D11Device **ppDevice,
_Out_opt_ D3D_FEATURE_LEVEL *pFeatureLevel,
_COM_Outptr_opt_ ID3D11DeviceContext **ppImmediateContext)
{
    SDKVersion = D3D11_SDK_VERSION;
    D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
    auto flags = Flags & CREATE_DEVICE_FLAG_MASK;

    HRESULT hr = pD3D11CreateDevice(pAdapter, DriverType, Software, flags, featurelevels, 2, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    if (FAILED(hr))
    {
        printf("Peggle 2: Failed to create the D3D11 Device! Error: 0x%X\n", hr);
        printf("Peggle 2: D3D11 Device Creation Flags: 0x%X\n", Flags);
    }

    return hr;
}

HRESULT CreateSwapChainForCoreWindow_Hook(IDXGIFactory2 *This, IUnknown *pDevice, IUnknown *pWindow,
                                          const DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput,
                                          IDXGISwapChain1 **ppSwapChain)
{
    DXGI_SWAP_CHAIN_DESC1 desc = *pDesc;
    desc.Flags &= DXGI_SWAPCHAIN_FLAG_MASK;
    desc.Scaling = DXGI_SCALING_STRETCH;

    IUnknown *Window = reinterpret_cast<CoreWindowEra *>(pWindow)->m_realWindow;
    if (Window)
    {
        ICoreWindowInterop *Interop;
        Window->QueryInterface(IID_PPV_ARGS(&Interop));
        HWND hwnd;
        Interop->get_WindowHandle(&hwnd);

        HRESULT hr = g_pFactory->CreateSwapChainForHwnd(pDevice, hwnd, &desc, nullptr, nullptr, ppSwapChain);
        if (SUCCEEDED(hr))
        {
            printf("Peggle 2: Successfully created the D3D11 Swap Chain.\n");
        }
        if (FAILED(hr))
        {
            printf("Peggle 2: Failed to create the D3D11 Swap Chain! Error: 0x%X\n", hr);
        }

        g_pFactory->Release();

        return hr;
    }

    return !pWindow ? E_INVALIDARG : E_FAIL;
}
