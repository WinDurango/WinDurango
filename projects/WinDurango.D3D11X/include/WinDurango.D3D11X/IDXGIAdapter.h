#pragma once
#include "d3d11_x.g.h"

template <abi_t ABI> class DXGIAdapter1 : public gfx::IDXGIAdapter1<ABI>
{
public:
    IDXGIAdapter1 *m_pFunction{};
    DXGIAdapter1(IDXGIAdapter1 *pAdapter)
    {
        m_pFunction = pAdapter;
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
    // IDXGIAdapter
    //
    HRESULT EnumOutputs(UINT Output, gfx::IDXGIOutput<ABI> **ppOutput);
    HRESULT GetDesc(DXGI_ADAPTER_DESC *pDesc);
    HRESULT CheckInterfaceSupport(_GUID const &InterfaceName, LARGE_INTEGER *pUMDVersion);

    //
    // IDXGIAdapter1
    //
    HRESULT GetDesc1(DXGI_ADAPTER_DESC1 *pDesc);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGIAdapter1<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);