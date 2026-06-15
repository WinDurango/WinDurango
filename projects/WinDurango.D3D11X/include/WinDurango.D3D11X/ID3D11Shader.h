#pragma once
#include "d3d11_x.g.h"

template <abi_t ABI> class D3D11VertexShader : public gfx::ID3D11VertexShader<ABI>
{
  public:
    ID3D11VertexShader *m_pFunction = nullptr;

    D3D11VertexShader(ID3D11VertexShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11VertexShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11PixelShader : public gfx::ID3D11PixelShader<ABI>
{
  public:
    ID3D11PixelShader *m_pFunction = nullptr;

    D3D11PixelShader(ID3D11PixelShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11PixelShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11ComputeShader : public gfx::ID3D11ComputeShader<ABI>
{
  public:
    ID3D11ComputeShader *m_pFunction = nullptr;

    D3D11ComputeShader(ID3D11ComputeShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ComputeShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11GeometryShader : public gfx::ID3D11GeometryShader<ABI>
{
  public:
    ID3D11GeometryShader *m_pFunction = nullptr;

    D3D11GeometryShader(ID3D11GeometryShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11GeometryShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11HullShader : public gfx::ID3D11HullShader<ABI>
{
  public:
    ID3D11HullShader *m_pFunction = nullptr;

    D3D11HullShader(ID3D11HullShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11HullShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11DomainShader : public gfx::ID3D11DomainShader<ABI>
{
  public:
    ID3D11DomainShader *m_pFunction = nullptr;

    D3D11DomainShader(ID3D11DomainShader *pShader)
    {
        m_pFunction = pShader;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DomainShader<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);

template <abi_t ABI> class D3D11InputLayout : public gfx::ID3D11InputLayout<ABI>
{
public:
    ID3D11InputLayout *m_pFunction = nullptr;

    D3D11InputLayout(ID3D11InputLayout *pLayout)
    {
        m_pFunction = pLayout;
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
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11InputLayout<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);
