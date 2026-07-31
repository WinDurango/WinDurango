#include "IDXGISwapChain.h"
#include "d3d11.x.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG DXGISwapChain1<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG DXGISwapChain1<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// IDXGIObject
//
template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGISwapChain1<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &Name,
                                                             xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetParent(_GUID const &riid, void **ppParent)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIDeviceSubObject
//
template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetDevice(REFIID riid, void **ppDevice)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGISwapChain
//
template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::Present(uint32_t SyncInterval, uint32_t Flags)
{
    static FPSLimiter Limiter(60.0);
    Limiter.BeginFrame();

    if (!m_wasIMGUIinitialized)
    {
        ID3D11Device* pDevice = nullptr;
        ID3D11DeviceContext* pContext = nullptr;
        m_pFunction->GetDevice(IID_PPV_ARGS(&pDevice));
        pDevice->GetImmediateContext(&pContext);

        p_wd->gui.Initialize(pDevice, pContext, m_pFunction);
        m_wasIMGUIinitialized = true;
    }

    p_wd->gui.Render();

    Limiter.Wait();
    return m_pFunction->Present(SyncInterval, Flags);
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetBuffer(UINT Buffer, REFIID riid, void **ppSurface)
{
    if (riid == xcom::guid_of<gfx::ID3D11Texture1D>())
    {
        ::ID3D11Texture1D *tex1D{};
        HRESULT hr = m_pFunction->GetBuffer(Buffer, IID_PPV_ARGS(&tex1D));
        *ppSurface = new D3D11Texture1D<ABI>(tex1D);
        return hr;
    }
    else if (riid == xcom::guid_of<gfx::ID3D11Texture2D>())
    {
        ::ID3D11Texture2D *tex2D{};
        HRESULT hr = m_pFunction->GetBuffer(Buffer, IID_PPV_ARGS(&tex2D));
        *ppSurface = new D3D11Texture2D<ABI>(tex2D);
        return hr;
    }
    else if (riid == xcom::guid_of<gfx::ID3D11Texture3D>())
    {
        ::ID3D11Texture3D *tex3D{};
        HRESULT hr = m_pFunction->GetBuffer(Buffer, IID_PPV_ARGS(&tex3D));
        *ppSurface = new D3D11Texture3D<ABI>(tex3D);
        return hr;
    }
    else if (riid == xcom::guid_of<gfx::ID3D11Resource>())
    {
        ::ID3D11Resource *resource{};
        HRESULT hr = m_pFunction->GetBuffer(Buffer, IID_PPV_ARGS(&resource));
        *ppSurface = new D3D11Resource<ABI>(resource);
        return hr;
    }

    IMPLEMENT_STUB();
    return E_NOINTERFACE;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::SetFullscreenState(bool Fullscreen, IDXGIOutput *pTarget)
{
    return m_pFunction->SetFullscreenState(Fullscreen, pTarget);
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetFullscreenState(bool *pFullscreen, IDXGIOutput **ppTarget)
{
    return m_pFunction->GetFullscreenState((BOOL*)pFullscreen, ppTarget);
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc)
{
    return m_pFunction->GetDesc(pDesc);
}

template <abi_t ABI>
HRESULT DXGISwapChain1<ABI>::ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat,
                                           uint32_t SwapChainFlags)
{
    return m_pFunction->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::ResizeTarget(DXGI_MODE_DESC const *pNewTargetParameters)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetContainingOutput(IDXGIOutput **ppOutput)
{
    return m_pFunction->GetContainingOutput(ppOutput);
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetLastPresentCount(uint32_t *pLastPresentCount)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGISwapChain1
//
template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetHwnd(HWND *pHwnd)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetCoreWindow(REFIID refiid, void **ppUnk)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGISwapChain1<ABI>::Present1(uint32_t SyncInterval, uint32_t PresentFlags,
                                      DXGI_PRESENT_PARAMETERS const *pPresentParameters)
{
    static FPSLimiter Limiter(60.0);
    Limiter.BeginFrame();

    if (!m_wasIMGUIinitialized)
    {
        ID3D11Device* pDevice = nullptr;
        ID3D11DeviceContext* pContext = nullptr;
        m_pFunction->GetDevice(IID_PPV_ARGS(&pDevice));
        pDevice->GetImmediateContext(&pContext);

        p_wd->gui.Initialize(pDevice, pContext, m_pFunction);
        m_wasIMGUIinitialized = true;
    }

    p_wd->gui.Render();

    Limiter.Wait();

    if (!pPresentParameters)
        return m_pFunction->Present(SyncInterval, PresentFlags);
    else
        return m_pFunction->Present1(SyncInterval, PresentFlags, pPresentParameters);
}

template <abi_t ABI> bool DXGISwapChain1<ABI>::IsTemporaryMonoSupported()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::SetBackgroundColor(DXGI_RGBA const *pColor)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetBackgroundColor(DXGI_RGBA *pColor)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::SetRotation(DXGI_MODE_ROTATION Rotation)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGISwapChain1<ABI>::GetRotation(DXGI_MODE_ROTATION *pRotation)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGISwapChain1<ABI>
D3D11_DECLARE_ABI_TEMPLATES();