#include "ID3D11View.h"
#include "ID3D11Resource.h"
#include "d3d11.x.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11View<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG D3D11View<ABI>::AddRef()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> ULONG D3D11View<ABI>::Release()
{
    IMPLEMENT_STUB();
    return {};
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11View<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11View<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11View<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11View<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11View<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11View
//
template <abi_t ABI> void D3D11View<ABI>::GetResource(gfx::ID3D11Resource<ABI> **ppResource)
{
    IMPLEMENT_STUB();
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11View<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11RenderTargetView<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<ID3D11RenderTargetView>() || riid == xcom::guid_of<ID3D11View>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    if (riid == xcom::guid_of<ID3D11DepthStencilView>())
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11RenderTargetView<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11RenderTargetView<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11RenderTargetView<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11RenderTargetView<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11RenderTargetView<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11RenderTargetView<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11RenderTargetView<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                    xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11View
//
template <abi_t ABI> void D3D11RenderTargetView<ABI>::GetResource(gfx::ID3D11Resource<ABI> **ppResource)
{
    D3D11_RENDER_TARGET_VIEW_DESC desc;
    m_pFunction->GetDesc(&desc);

    if (desc.ViewDimension == D3D11_RTV_DIMENSION_BUFFER)
    {
        ID3D11Buffer *Buffer{};
        m_pFunction->GetResource(reinterpret_cast<ID3D11Resource **>(&Buffer));
        *reinterpret_cast<D3D11Buffer<ABI> **>(ppResource) = new D3D11Buffer<ABI>(Buffer);
    }
    if (desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE1D || desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE1DARRAY)
    {
        ID3D11Texture1D *Tex1D{};
        m_pFunction->GetResource(reinterpret_cast<ID3D11Resource **>(&Tex1D));
        *reinterpret_cast<D3D11Texture1D<ABI> **>(ppResource) = new D3D11Texture1D<ABI>(Tex1D);
    }
    if (desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2D ||
        desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2DARRAY ||
        desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2DMS ||
        desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY)
    {
        ID3D11Texture2D *Tex2D{};
        m_pFunction->GetResource(reinterpret_cast<ID3D11Resource **>(&Tex2D));
        *reinterpret_cast<D3D11Texture2D<ABI> **>(ppResource) = new D3D11Texture2D<ABI>(Tex2D);
    }
    if (desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE3D)
    {
        ID3D11Texture3D *Tex3D{};
        m_pFunction->GetResource(reinterpret_cast<ID3D11Resource **>(&Tex3D));
        *reinterpret_cast<D3D11Texture3D<ABI> **>(ppResource) = new D3D11Texture3D<ABI>(Tex3D);
    }
}

//
// ID3D11RenderTargetView
//
template <abi_t ABI> void D3D11RenderTargetView<ABI>::GetDesc(D3D11_RENDER_TARGET_VIEW_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11RenderTargetView<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11DepthStencilView<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<ID3D11DepthStencilView>() || riid == xcom::guid_of<ID3D11View>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11DepthStencilView<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11DepthStencilView<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11DepthStencilView<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DepthStencilView<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DepthStencilView<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11DepthStencilView<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DepthStencilView<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                    xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11View
//
template <abi_t ABI> void D3D11DepthStencilView<ABI>::GetResource(gfx::ID3D11Resource<ABI> **ppResource)
{
    IMPLEMENT_STUB();
}

//
// ID3D11DepthStencilView
//
template <abi_t ABI> void D3D11DepthStencilView<ABI>::GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc)
{
    IMPLEMENT_STUB();
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DepthStencilView<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11ShaderResourceView<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG D3D11ShaderResourceView<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11ShaderResourceView<ABI>::Release()
{
    std::lock_guard<std::mutex> PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        for (UINT i = 0; i < D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; i++)
        {
            if (g_PSFastShaderResources<ABI>[i] == this)
                g_PSFastShaderResources<ABI>[i] = 0;
            else if (g_VSFastShaderResources<ABI>[i] == this)
                g_VSFastShaderResources<ABI>[i] = 0;
        }
        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11ShaderResourceView<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11ShaderResourceView<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11ShaderResourceView<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11ShaderResourceView<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11ShaderResourceView<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                      xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11View
//
template <abi_t ABI> void D3D11ShaderResourceView<ABI>::GetResource(gfx::ID3D11Resource<ABI> **ppResource)
{
    if (m_pBuffer)
    {
        *ppResource = m_pBuffer;
        return;
    }
    else if (m_pTexture1D)
    {
        *ppResource = m_pTexture1D;
        return;
    }
    else if (m_pTexture2D)
    {
        *ppResource = m_pTexture2D;
        return;
    }
    else if (m_pTexture3D)
    {
        *ppResource = m_pTexture3D;
        return;
    }
}

//
// ID3D11ShaderResourceView
//
template <abi_t ABI> void D3D11ShaderResourceView<ABI>::GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

template <abi_t ABI> void D3D11ShaderResourceView<ABI>::GetFormatX(gfx::D3D11X_SRV_FORMAT *pFormat)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> int32_t D3D11ShaderResourceView<ABI>::SetFormatX(gfx::D3D11X_SRV_FORMAT const *pFormat)
{
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ShaderResourceView<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11UnorderedAccessView<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<ID3D11UnorderedAccessView>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11UnorderedAccessView<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11UnorderedAccessView<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11UnorderedAccessView<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11UnorderedAccessView<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11UnorderedAccessView<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11UnorderedAccessView<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11UnorderedAccessView<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                       xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11View
//
template <abi_t ABI> void D3D11UnorderedAccessView<ABI>::GetResource(gfx::ID3D11Resource<ABI> **ppResource)
{
    if (m_pBuffer)
    {
        *ppResource = m_pBuffer;
        return;
    }
    else if (m_pTexture1D)
    {
        *ppResource = m_pTexture1D;
        return;
    }
    else if (m_pTexture2D)
    {
        *ppResource = m_pTexture2D;
        return;
    }
    else if (m_pTexture3D)
    {
        *ppResource = m_pTexture3D;
        return;
    }
}

//
// ID3D11UnorderedAccessView
//
template <abi_t ABI> void D3D11UnorderedAccessView<ABI>::GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc)
{
    IMPLEMENT_STUB();
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11UnorderedAccessView<ABI>
D3D11_DECLARE_ABI_TEMPLATES();