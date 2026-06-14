#pragma once
#include "ID3D11Resource.h"
#include "d3d11_x.g.h"

template <abi_t ABI> class D3D11View : public gfx::ID3D11View<ABI>
{
  public:
    ID3D11View *m_pFunction = nullptr;

    D3D11View(ID3D11View *pView)
    {
        m_pFunction = pView;
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
    // ID3D11View
    //
    void GetResource(gfx::ID3D11Resource<ABI> **ppResource);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11View<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11ShaderResourceView : public gfx::ID3D11ShaderResourceView<ABI>
{
  public:
    ID3D11ShaderResourceView *m_pFunction = nullptr;
    D3D11Buffer<ABI> *m_pBuffer = nullptr;
    D3D11Texture1D<ABI> *m_pTexture1D = nullptr;
    D3D11Texture2D<ABI> *m_pTexture2D = nullptr;
    D3D11Texture3D<ABI> *m_pTexture3D = nullptr;

    D3D11ShaderResourceView(ID3D11ShaderResourceView *pView)
    {
        m_pFunction = pView;
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
    // ID3D11View
    //
    void GetResource(gfx::ID3D11Resource<ABI> **ppResource);

    //
    // ID3D11ShaderResourceView
    //
    void GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc);
    void GetFormatX(gfx::D3D11X_SRV_FORMAT *);
    int32_t SetFormatX(gfx::D3D11X_SRV_FORMAT const *);
};

template <abi_t ABI>
gfx::ID3D11ShaderResourceView<ABI> *g_VSFastShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];

template <abi_t ABI>
gfx::ID3D11ShaderResourceView<ABI> *g_PSFastShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ShaderResourceView<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11RenderTargetView : public gfx::ID3D11RenderTargetView<ABI>
{
  public:
    ID3D11RenderTargetView *m_pFunction = nullptr;
    D3D11RenderTargetView(ID3D11RenderTargetView *pView)
    {
        m_pFunction = pView;
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
    // ID3D11View
    //
    void GetResource(gfx::ID3D11Resource<ABI> **ppResource);

    //
    // ID3D11RenderTargetView
    //
    void GetDesc(D3D11_RENDER_TARGET_VIEW_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11RenderTargetView<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11DepthStencilView : public gfx::ID3D11DepthStencilView<ABI>
{
  public:
    ID3D11DepthStencilView *m_pFunction = nullptr;

    D3D11DepthStencilView(ID3D11DepthStencilView *pView)
    {
        m_pFunction = pView;
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
    // ID3D11View
    //
    void GetResource(gfx::ID3D11Resource<ABI> **ppResource);

    //
    // ID3D11DepthStencilView
    //
    void GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DepthStencilView<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11UnorderedAccessView : public gfx::ID3D11UnorderedAccessView<ABI>
{
  public:
    ID3D11UnorderedAccessView *m_pFunction = nullptr;
    D3D11Buffer<ABI> *m_pBuffer = nullptr;
    D3D11Texture1D<ABI> *m_pTexture1D = nullptr;
    D3D11Texture2D<ABI> *m_pTexture2D = nullptr;
    D3D11Texture3D<ABI> *m_pTexture3D = nullptr;

    D3D11UnorderedAccessView(ID3D11UnorderedAccessView *pView)
    {
        m_pFunction = pView;
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
    // ID3D11View
    //
    void GetResource(gfx::ID3D11Resource<ABI> **ppResource);

    //
    // ID3D11UnorderedAccessView
    //
    void GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11UnorderedAccessView<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);