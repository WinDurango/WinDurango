#include "IDXGIFactory.h"
#include "EraCoreWindow.h"
#include "ID3D11Device.h"
#include "IDXGISwapChain.h"
#include <CoreWindow.h>
#include <windows.applicationmodel.core.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/windows.storage.provider.h>
#include "ID3D11Runtime.h"
#include "d3d11.x.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT DXGIFactory2<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG DXGIFactory2<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG DXGIFactory2<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// IDXGIObject
//
template <abi_t ABI> HRESULT DXGIFactory2<ABI>::SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &Name, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData)
{
    return m_pFunction->GetPrivateData(Name, pDataSize, pData);
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::GetParent(_GUID const &riid, void **ppParent)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIFactory
//
template <abi_t ABI> HRESULT DXGIFactory2<ABI>::EnumAdapters(UINT Adapter, gfx::IDXGIAdapter<ABI> **ppAdapter)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::GetWindowAssociation(HWND *pWindowHandle)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::CreateSwapChain(xbox::IGraphicsUnknown<ABI> *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc,
                                           gfx::IDXGISwapChain<ABI> **ppSwapChain)
{
    /*
     * idk what im doing here
    */
    auto pDesc2 = *pDesc;

    if (!pDesc2.OutputWindow)
    {
        ComPtr<ICoreWindowStatic> pWindowStatic;
        RoGetActivationFactory(Microsoft::WRL::Wrappers::HStringReference::HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&pWindowStatic));

        ComPtr<ICoreWindow> Window;
        pWindowStatic->GetForCurrentThread(&Window);

        ICoreWindowInterop *interop;
        Window->QueryInterface(IID_PPV_ARGS(&interop));
        interop->get_WindowHandle(&pDesc2.OutputWindow);
    }

    IDXGISwapChain *SwapChain{};
    IUnknown *pRealDevice = static_cast<D3D11DeviceX<ABI> *>(pDevice)->m_pFunction;
    HRESULT hr = m_pFunction->CreateSwapChain(pRealDevice, &pDesc2, &SwapChain);

    if (SwapChain)
    {
        *ppSwapChain = reinterpret_cast<gfx::IDXGISwapChain<ABI>*>(SwapChain);
    }
    return hr;
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::CreateSoftwareAdapter(HMODULE Module, gfx::IDXGIAdapter<ABI> **ppAdapter)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// IDXGIFactory1
//
template <abi_t ABI> HRESULT DXGIFactory2<ABI>::EnumAdapters1(UINT Adapter, gfx::IDXGIAdapter1<ABI> **ppAdapter)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> bool DXGIFactory2<ABI>::IsCurrent()
{
    IMPLEMENT_STUB();
    return {};
}

//
// IDXGIFactory2
//
template <abi_t ABI> bool DXGIFactory2<ABI>::IsWindowedStereoEnabled()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::CreateSwapChainForHwnd(xbox::IGraphicsUnknown<ABI> *pDevice, HWND hWnd,
                                                  DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                                  DXGI_SWAP_CHAIN_FULLSCREEN_DESC const *pFullscreenDesc,
                                                  IDXGIOutput *pRestrictToOutput,
                                                  gfx::IDXGISwapChain1<ABI> **ppSwapChain)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::CreateSwapChainForCoreWindow(xbox::IGraphicsUnknown<ABI> *pDevice, IUnknown *pWindow,
                                                        DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput,
                                                        gfx::IDXGISwapChain1<ABI> **ppSwapChain)
{
    auto pDesc2 = *pDesc;
    pDesc2.Scaling = DXGI_SCALING_STRETCH;
    pDesc2.Flags = 0;
    IUnknown *dev{};
    HRESULT hr = 0;

    if (pDesc->SwapEffect == DXGI_SWAP_EFFECT_DISCARD || pDesc->SwapEffect == DXGI_SWAP_EFFECT_SEQUENTIAL)
    {
        if (pDesc->SwapEffect == DXGI_SWAP_EFFECT_DISCARD)
            pDesc2.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        else if (pDesc->SwapEffect == DXGI_SWAP_EFFECT_SEQUENTIAL)
            pDesc2.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    }

    if (pDevice)
    {
        pDevice->QueryInterface(__uuidof(xbox::IGraphicsUnwrap), (void **)&dev);
    }
    else
    {
        pDevice = new D3D11DeviceX<ABI>(pDev2);
        pDevice->QueryInterface(__uuidof(xbox::IGraphicsUnwrap), (void **)&dev);
    }

    if (!pWindow)
    {
        ComPtr<ICoreWindowStatic> pWindowStatic;
        RoGetActivationFactory(Microsoft::WRL::Wrappers::HStringReference::HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&pWindowStatic));

        ComPtr<ICoreWindow> Window;
        pWindowStatic->GetForCurrentThread(&Window);

        ICoreWindowInterop *interop;
        Window->QueryInterface(IID_PPV_ARGS(&interop));
        HWND hwnd;
        interop->get_WindowHandle(&hwnd);

        IDXGISwapChain1 *SwapChain{};
        hr = m_pFunction->CreateSwapChainForHwnd(dev, hwnd, &pDesc2, NULL, NULL, &SwapChain);

        if (SwapChain)
        {
            *ppSwapChain = new DXGISwapChain1<ABI>(SwapChain);
        }

        return hr;
    }

    ICoreWindow* Window = reinterpret_cast<CoreWindowEra*>(pWindow)->m_realWindow;
    ICoreWindowInterop *interop;
    Window->QueryInterface(IID_PPV_ARGS(&interop));
    HWND hwnd;
    interop->get_WindowHandle(&hwnd);

    IDXGISwapChain1 *SwapChain{};
    hr = m_pFunction->CreateSwapChainForHwnd(dev, hwnd, &pDesc2, NULL, NULL, &SwapChain);

    if (SwapChain)
    {
        *ppSwapChain = new DXGISwapChain1<ABI>(SwapChain);
    }

    return hr;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::GetSharedResourceAdapterLuid(void *hResource, _LUID *pLuid)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::RegisterStereoStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::RegisterStereoStatusEvent(void *hEvent, uint32_t *pdwCookie)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void DXGIFactory2<ABI>::UnregisterStereoStatus(uint32_t dwCookie)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::RegisterOcclusionStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT DXGIFactory2<ABI>::RegisterOcclusionStatusEvent(void *hEvent, uint32_t *pdwCookie)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void DXGIFactory2<ABI>::UnregisterOcclusionStatus(uint32_t dwCookie)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT DXGIFactory2<ABI>::CreateSwapChainForComposition(xbox::IGraphicsUnknown<ABI> *pDevice,
                                                         DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                                         IDXGIOutput *pRestrictToOutput,
                                                         gfx::IDXGISwapChain1<ABI> **ppSwapChain)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGIFactory2<ABI>
D3D11_DECLARE_ABI_TEMPLATES();