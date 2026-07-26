#pragma once
#include "d3d11_x.g.h"

template <abi_t ABI> class D3D11Resource : public gfx::ID3D11Resource<ABI>
{
public:
    ID3D11Resource *m_pFunction = nullptr;
    bool m_IsDirty = false;

    D3D11Resource(ID3D11Resource *pResource)
    {
        m_pFunction = pResource;
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
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI> **ppDevice);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT SetName(LPCWSTR pName)
    {
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    //
    // ID3D11Resource
    //
    void GetType(D3D11_RESOURCE_DIMENSION *pDimension);
    void SetEvictionPriority(uint32_t EvictionPriority);
    uint32_t GetEvictionPriority();
    void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Resource<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);


template <abi_t ABI> class D3D11Texture1D : public gfx::ID3D11Texture1D<ABI>
{
public:
    ID3D11Texture1D *m_pFunction = nullptr;
    bool m_IsDirty = false;

    D3D11Texture1D(ID3D11Texture1D *pResource)
    {
        m_pFunction = pResource;
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
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI> **ppDevice);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT SetName(LPCWSTR pName)
    {
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    //
    // ID3D11Resource
    //
    void GetType(D3D11_RESOURCE_DIMENSION *pDimension);
    void SetEvictionPriority(uint32_t EvictionPriority);
    uint32_t GetEvictionPriority();
    void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);

    //
    // ID3D11Texture1D
    //
    void GetDesc(D3D11_TEXTURE1D_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture1D<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);


template <abi_t ABI> class D3D11Texture2D : public gfx::ID3D11Texture2D<ABI>
{
  public:
    ID3D11Texture2D *m_pFunction = nullptr;
    bool m_IsDirty = false;
    UINT m_TileModeIndex = 0;
    UINT m_RowPitch = 0;
    UINT m_SlicePitch = 0;

    D3D11Texture2D(ID3D11Texture2D *pResource)
    {
        m_pFunction = pResource;
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
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI> **ppDevice);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT SetName(LPCWSTR pName)
    {
        return S_OK;
    }

    //
    // ID3D11Resource
    //
    void GetType(D3D11_RESOURCE_DIMENSION *pDimension);
    void SetEvictionPriority(uint32_t EvictionPriority);
    uint32_t GetEvictionPriority();
    void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);

    //
    // ID3D11Texture2D
    //
    void GetDesc(D3D11_TEXTURE2D_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture2D<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);


template <abi_t ABI> class D3D11Texture3D : public gfx::ID3D11Texture3D<ABI>
{
public:
    ID3D11Texture3D *m_pFunction = nullptr;
    bool m_IsDirty = false;

    D3D11Texture3D(ID3D11Texture3D *pResource)
    {
        m_pFunction = pResource;
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
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI> **ppDevice);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT SetName(LPCWSTR pName)
    {
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    //
    // ID3D11Resource
    //
    void GetType(D3D11_RESOURCE_DIMENSION *pDimension);
    void SetEvictionPriority(uint32_t EvictionPriority);
    uint32_t GetEvictionPriority();
    void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);

    //
    // ID3D11Texture3D
    //
    void GetDesc(D3D11_TEXTURE3D_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture3D<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);


template <abi_t ABI> class D3D11Buffer : public gfx::ID3D11Buffer<ABI>
{
public:
    ID3D11Buffer *m_pFunction = nullptr;
    bool m_IsDirty = false;

    D3D11Buffer(ID3D11Buffer *pResource)
    {
        m_pFunction = pResource;
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
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI> **ppDevice);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    HRESULT SetName(LPCWSTR pName)
    {
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    //
    // ID3D11Resource
    //
    void GetType(D3D11_RESOURCE_DIMENSION *pDimension);
    void SetEvictionPriority(uint32_t EvictionPriority);
    uint32_t GetEvictionPriority();
    void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);

    //
    // ID3D11Buffer
    //
    void GetDesc(D3D11_BUFFER_DESC *pDesc);
};

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_VSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_PSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_CSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_GSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_HSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_DSFastConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_IAFastVertexBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11Buffer<ABI> *g_IAFastIndexBuffer = nullptr;

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Buffer<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);
