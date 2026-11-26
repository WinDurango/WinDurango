#pragma once
#include "d3d11_x.g.h"

template <abi_t ABI> class DXGIFactory2 : public gfx::IDXGIFactory2<ABI>
{
public:
    IDXGIFactory2 *m_pFunction{};
    DXGIFactory2(IDXGIFactory2 *pFactory)
    {
        m_pFunction = pFactory;
        if (this->m_RefCount != 0)
            this->m_RefCount = 0;
        InterlockedIncrement(&this->m_RefCount);
    }

    //
    // IUnknown
    //
    HRESULT QueryInterface(REFIID riid, void **ppvObject);
    ULONG AddRef();
    ULONG Release();

    //
    // IDXGIObject
    //
    HRESULT SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &Name, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData);
    HRESULT GetParent(_GUID const &riid, void **ppParent);

    //
    // IDXGIFactory
    //
    HRESULT EnumAdapters(UINT Adapter, gfx::IDXGIAdapter<ABI> **ppAdapter);
    HRESULT MakeWindowAssociation(HWND WindowHandle, UINT Flags);
    HRESULT GetWindowAssociation(HWND *pWindowHandle);
    HRESULT CreateSwapChain(xbox::IGraphicsUnknown<ABI> *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc,
                            gfx::IDXGISwapChain<ABI> **ppSwapChain);
    HRESULT CreateSoftwareAdapter(HMODULE Module, gfx::IDXGIAdapter<ABI> **ppAdapter);

    //
    // IDXGIFactory1
    //
    HRESULT EnumAdapters1(UINT Adapter, gfx::IDXGIAdapter1<ABI> **ppAdapter);
    bool IsCurrent();

    //
    // IDXGIFactory2
    //
    bool IsWindowedStereoEnabled();
    HRESULT CreateSwapChainForHwnd(xbox::IGraphicsUnknown<ABI> *pDevice, HWND hWnd, DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                   DXGI_SWAP_CHAIN_FULLSCREEN_DESC const *pFullscreenDesc,
                                   gfx::IDXGIOutput<ABI> *pRestrictToOutput, gfx::IDXGISwapChain1<ABI> **ppSwapChain);
    HRESULT CreateSwapChainForCoreWindow(xbox::IGraphicsUnknown<ABI> *pDevice, IUnknown *pWindow,
                                         DXGI_SWAP_CHAIN_DESC1 *pDesc, gfx::IDXGIOutput<ABI> *pRestrictToOutput,
                                         gfx::IDXGISwapChain1<ABI> **ppSwapChain);
    HRESULT GetSharedResourceAdapterLuid(void *hResource, _LUID *pLuid);
    HRESULT RegisterStereoStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie);
    HRESULT RegisterStereoStatusEvent(void *hEvent, uint32_t *pdwCookie);
    void UnregisterStereoStatus(uint32_t dwCookie);
    HRESULT RegisterOcclusionStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie);
    HRESULT RegisterOcclusionStatusEvent(void *hEvent, uint32_t *pdwCookie);
    void UnregisterOcclusionStatus(uint32_t dwCookie);
    HRESULT CreateSwapChainForComposition(xbox::IGraphicsUnknown<ABI> *pDevice, DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                          gfx::IDXGIOutput<ABI> *pRestrictToOutput, gfx::IDXGISwapChain1<ABI> **ppSwapChain);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGIFactory2<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);