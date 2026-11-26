#include "IDXGIAdapter.h"
#include "IDXGIFactory.h"
#include "IDXGIOutput.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == __uuidof(IDXGIAdapter) || riid == __uuidof(IDXGIAdapter1))
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(xbox::IGraphicsUnwrap))
    {
        *ppvObject = m_pFunction;
        return S_OK;
    }

    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG DXGIAdapter1<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG DXGIAdapter1<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// IDXGIObject
//
template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIAdapter1<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &Name, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::GetParent(_GUID const &riid, void **ppParent)
{
    if (riid == __uuidof(IDXGIFactory))
    {
        IDXGIFactory *factory{};
        m_pFunction->GetParent(IID_PPV_ARGS(&factory));
        *ppParent = new DXGIFactory2<ABI>(static_cast<IDXGIFactory2*>(factory));
        return S_OK;
    }

    if (riid == __uuidof(IDXGIFactory1))
    {
        IDXGIFactory1 *factory{};
        m_pFunction->GetParent(IID_PPV_ARGS(&factory));
        *ppParent = new DXGIFactory2<ABI>(static_cast<IDXGIFactory2*>(factory));
        return S_OK;
    }

    if (riid == __uuidof(IDXGIFactory2))
    {
        IDXGIFactory2 *factory{};
        m_pFunction->GetParent(IID_PPV_ARGS(&factory));
        *ppParent = new DXGIFactory2<ABI>(static_cast<IDXGIFactory2*>(factory));
        return S_OK;
    }

    return E_NOINTERFACE;
}

//
// IDXGIAdapter
//
template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::EnumOutputs(UINT Output, gfx::IDXGIOutput<ABI> **ppOutput)
{
    IDXGIOutput *pOutput = nullptr;
    HRESULT hr = m_pFunction->EnumOutputs(Output, &pOutput);
    if (SUCCEEDED(hr))
    {
        *ppOutput = new DXGIOutput<ABI>(pOutput);
    }
    return hr;
}

template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::GetDesc(DXGI_ADAPTER_DESC *pDesc)
{
    return m_pFunction->GetDesc(pDesc);
}

template <abi_t ABI>
HRESULT DXGIAdapter1<ABI>::CheckInterfaceSupport(_GUID const &InterfaceName, LARGE_INTEGER *pUMDVersion)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIAdapter1
//
template <abi_t ABI> HRESULT DXGIAdapter1<ABI>::GetDesc1(DXGI_ADAPTER_DESC1 *pDesc)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGIAdapter1<ABI>
D3D11_DECLARE_ABI_TEMPLATES();