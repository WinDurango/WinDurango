#include "IDXGIDevice.h"
#include "IDXGIAdapter.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT DXGIDevice2<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG DXGIDevice2<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG DXGIDevice2<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// IDXGIObject
//
template <abi_t ABI> HRESULT DXGIDevice2<ABI>::SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIDevice2<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &Name, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(Name, pDataSize, pData);
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::GetParent(_GUID const &riid, void **ppParent)
{
    if (riid == __uuidof(IDXGIAdapter) || riid == __uuidof(IDXGIAdapter1))
    {
        m_pFunction->GetParent(riid, ppParent);
        *ppParent = new DXGIAdapter1<ABI>(static_cast<IDXGIAdapter1*>(*ppParent));
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIDevice
//
template <abi_t ABI> HRESULT DXGIDevice2<ABI>::GetAdapter(gfx::IDXGIAdapter<ABI> **pAdapter)
{
    ::IDXGIAdapter *Adapter{};
    ::IDXGIAdapter1 *Adapter1{};
    m_pFunction->GetAdapter(&Adapter);
    Adapter->QueryInterface(IID_PPV_ARGS(&Adapter1));
    Adapter->Release();

    if (Adapter)
    {
        *pAdapter = new DXGIAdapter1<ABI>(Adapter1);
    }

    return S_OK;
}

template <abi_t ABI>
HRESULT DXGIDevice2<ABI>::CreateSurface(DXGI_SURFACE_DESC const *pDesc, uint32_t NumSurfaces, DXGI_USAGE Usage,
                                        DXGI_SHARED_RESOURCE const *pSharedResource, IDXGISurface **ppSurface)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIDevice2<ABI>::QueryResourceResidency(xbox::IGraphicsUnknown<ABI> **ppResources,
                                                 DXGI_RESIDENCY *pResidencyStatus, uint32_t NumResources)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::SetGPUThreadPriority(int Priority)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::GetGPUThreadPriority(int *pPriority)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIDevice1
//
template <abi_t ABI> HRESULT DXGIDevice2<ABI>::SetMaximumFrameLatency(uint32_t MaxLatency)
{
    return m_pFunction->SetMaximumFrameLatency(MaxLatency);
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::GetMaximumFrameLatency(uint32_t *pMaxLatency)
{
    return m_pFunction->GetMaximumFrameLatency(pMaxLatency);
}

//
// IDXGIDevice2
//
template <abi_t ABI>
HRESULT DXGIDevice2<ABI>::OfferResources(uint32_t NumResources, IDXGIResource *const *ppResources,
                                         DXGI_OFFER_RESOURCE_PRIORITY Priority)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIDevice2<ABI>::ReclaimResources(uint32_t NumResources, IDXGIResource *const *ppResources, bool *pDiscarded)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIDevice2<ABI>::EnqueueSetEvent(void *hEvent)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGIDevice2<ABI>
D3D11_DECLARE_ABI_TEMPLATES();