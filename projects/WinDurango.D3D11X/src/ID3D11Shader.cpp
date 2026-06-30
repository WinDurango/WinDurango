#include "ID3D11Shader.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11VertexShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11VertexShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11VertexShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11VertexShader<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11VertexShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11VertexShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11VertexShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11VertexShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11VertexShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11VertexShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11PixelShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11PixelShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11PixelShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11PixelShader<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11PixelShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11PixelShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11PixelShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11PixelShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11PixelShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                               xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11PixelShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11ComputeShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11ComputeShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11ComputeShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11ComputeShader<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11ComputeShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11ComputeShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11ComputeShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11ComputeShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11ComputeShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                 xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ComputeShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11GeometryShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11GeometryShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11GeometryShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11GeometryShader<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11GeometryShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11GeometryShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11GeometryShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11GeometryShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11GeometryShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                  xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11GeometryShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11HullShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11HullShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11HullShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11HullShader<ABI>::Release()
{
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11HullShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11HullShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11HullShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11HullShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11HullShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                              xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11HullShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11DomainShader<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11DomainShader>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11DomainShader<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11DomainShader<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11DomainShader<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11DomainShader<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11DomainShader<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11DomainShader<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11DomainShader<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DomainShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES();

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11InputLayout<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11InputLayout>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11InputLayout<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11InputLayout<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11InputLayout<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11InputLayout<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI>
HRESULT D3D11InputLayout<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    return m_pFunction->SetPrivateData(guid, DataSize, pData);
}

template <abi_t ABI> HRESULT D3D11InputLayout<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11InputLayout<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11InputLayout<ABI>
D3D11_DECLARE_ABI_TEMPLATES();