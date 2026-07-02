#pragma once
#include "ID3D11Device.h"
#include "ID3D11DeviceContext.h"
#include "IDXGISwapChain.h"
#include <CoreWindow.h>
#include <windows.applicationmodel.core.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/windows.storage.provider.h>
#include "EraCoreWindow.h"

static ID3D11Device2 *pDev2 = nullptr;
static ID3D11DeviceContext2 *pCtx2 = nullptr;

struct ID3D11Runtime
{
    virtual HRESULT CreateDevice(void **ppDevice, void **ppContext) = 0;
    virtual HRESULT CreateSwapChain(void **ppSwapChain, void* pDevice, const DXGI_SWAP_CHAIN_DESC1* pSwapChainDesc) = 0;
};

template <abi_t ABI> struct D3D11Runtime : public ID3D11Runtime
{
    HRESULT CreateDevice(void **ppDevice, void **ppContext) override
    {
        ID3D11Device *pDevice = nullptr;
        ID3D11DeviceContext *pContext = nullptr;

        D3D_FEATURE_LEVEL FeatureLevels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
        UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        #ifdef _DEBUG
            Flags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        auto hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flags, FeatureLevels, 2, D3D11_SDK_VERSION,
                                    &pDevice, nullptr, &pContext);

        if (FAILED(hr))
        {
            hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, Flags, FeatureLevels, 2, D3D11_SDK_VERSION,
                                    &pDevice, nullptr, &pContext);
            if (FAILED(hr))
            {
                MessageBoxA(nullptr, "Failed to create the D3D11 Device!", "Error!", MB_OK);
            }
        }

        ID3D11Device2 *pDevice2 = nullptr;
        ID3D11DeviceContext2 *pContext2 = nullptr;

        pDevice->QueryInterface(IID_PPV_ARGS(&pDevice2));
        pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
        pDev2 = pDevice2;
        pCtx2 = pContext2;

        pDevice->Release();
        pContext->Release();

        *ppDevice = new D3D11DeviceX<ABI>(pDevice2);
        *ppContext = new D3D11DeviceContextX<ABI>(pContext2);

        return hr;
    };

    HRESULT CreateSwapChain(void** ppSwapChain, void* pDevice, const DXGI_SWAP_CHAIN_DESC1* pSwapChainDesc) override
    {
        IDXGIFactory2* Factory{};
        HRESULT hr = CreateDXGIFactory2(NULL, IID_PPV_ARGS(&Factory));

        if (FAILED(hr))
            return hr;

        ComPtr<ICoreWindowStatic> pWindowStatic;
        RoGetActivationFactory(Microsoft::WRL::Wrappers::HStringReference::HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&pWindowStatic));

        ComPtr<ICoreWindow> pWindow;
        pWindowStatic->GetForCurrentThread(&pWindow);

        if (pWindow)
        {
            ICoreWindowInterop *interop;
            pWindow->QueryInterface(IID_PPV_ARGS(&interop));
            HWND hwnd;
            interop->get_WindowHandle(&hwnd);

            auto desc = *pSwapChainDesc;
            desc.Scaling = DXGI_SCALING_STRETCH;

            if (pSwapChainDesc->SwapEffect != DXGI_SWAP_EFFECT_FLIP_DISCARD && pSwapChainDesc->SwapEffect != DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL)
            {
                if (pSwapChainDesc->SwapEffect == DXGI_SWAP_EFFECT_DISCARD)
                    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
                else if (pSwapChainDesc->SwapEffect == DXGI_SWAP_EFFECT_SEQUENTIAL)
                    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
            }

            IDXGISwapChain1* SwapChain{};
            hr = Factory->CreateSwapChainForHwnd(static_cast<D3D11DeviceX<ABI>*>(pDevice)->m_pFunction, hwnd, &desc, nullptr, nullptr, &SwapChain);
            if (FAILED(hr))
                return hr;

            if (SwapChain)
            {
                *ppSwapChain = new DXGISwapChain1<ABI>(SwapChain);
            }

            return hr;
        }
    }
};


struct IDXGIXPresentArrayHelper
{
    virtual void PresentArray(void **ppSwapChains, UINT NumSwapChains, UINT SyncInterval) = 0;
};

template <abi_t ABI> struct DXGIXPresentArrayHelper : public IDXGIXPresentArrayHelper
{
    void PresentArray(void **ppSwapChains, UINT NumSwapChains, UINT SyncInterval) override
    {
        for (UINT SwapChainIndex = 0; SwapChainIndex < NumSwapChains; SwapChainIndex++)
        {
            DXGISwapChain1<ABI> *SwapChain = static_cast<DXGISwapChain1<ABI> *>(ppSwapChains[SwapChainIndex]);
            SwapChain->Present(SyncInterval, 0);
        }
    }

};

static IDXGIXPresentArrayHelper *g_PresentArrayHelper = nullptr;