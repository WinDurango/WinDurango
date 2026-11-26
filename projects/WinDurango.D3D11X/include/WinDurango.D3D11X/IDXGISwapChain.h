#pragma once
#include "ID3D11Resource.h"
#include "d3d11_x.g.h"

template <abi_t ABI> class DXGISwapChain1 : public gfx::IDXGISwapChain1<ABI>
{
public:
    IDXGISwapChain1 *m_pFunction{};
    DXGISwapChain1(::IDXGISwapChain1 *pSwapChain)
    {
        m_pFunction = pSwapChain;
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
    // IDXGIDeviceSubObject
    //
    HRESULT GetDevice(REFIID riid, void **ppDevice);

    //
    // IDXGISwapChain
    //
    HRESULT Present(uint32_t SyncInterval, uint32_t Flags);
    HRESULT GetBuffer(UINT Buffer, REFIID riid, void **ppSurface);
    HRESULT SetFullscreenState(bool Fullscreen, gfx::IDXGIOutput<ABI> *pTarget);
    HRESULT GetFullscreenState(bool *pFullscreen, gfx::IDXGIOutput<ABI> **ppTarget);
    HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc);
    HRESULT ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat,
                          uint32_t SwapChainFlags);
    HRESULT ResizeTarget(DXGI_MODE_DESC const *pNewTargetParameters);
    HRESULT GetContainingOutput(gfx::IDXGIOutput<ABI> **ppOutput);
    HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats);
    HRESULT GetLastPresentCount(uint32_t *pLastPresentCount);

    //
    // IDXGISwapChain1
    //
    HRESULT GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc);
    HRESULT GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc);
    HRESULT GetHwnd(HWND *pHwnd);
    HRESULT GetCoreWindow(REFIID refiid, void **ppUnk);
    HRESULT Present1(uint32_t SyncInterval, uint32_t PresentFlags, DXGI_PRESENT_PARAMETERS const *pPresentParameters);
    bool IsTemporaryMonoSupported();
    HRESULT GetRestrictToOutput(gfx::IDXGIOutput<ABI> **ppRestrictToOutput);
    HRESULT SetBackgroundColor(DXGI_RGBA const *pColor);
    HRESULT GetBackgroundColor(DXGI_RGBA *pColor);
    HRESULT SetRotation(DXGI_MODE_ROTATION Rotation);
    HRESULT GetRotation(DXGI_MODE_ROTATION *pRotation);

private:
    bool m_wasIMGUIinitialized = false;
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) DXGISwapChain1<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);



class FPSLimiter
{
public:
    FPSLimiter(FLOAT fps)
    {
        ZeroMemory(&m_Frequency, sizeof(m_Frequency));
        QueryPerformanceFrequency(&m_Frequency);

        m_Target = 1.0 / fps;

        QueryPerformanceCounter(&m_Last);
        m_Accumulator = 0.0;
    }

    void BeginFrame()
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        FLOAT delta = FLOAT(now.QuadPart - m_Last.QuadPart) / m_Frequency.QuadPart;

        m_Last = now;
        m_Accumulator += delta;

        if (m_Accumulator > 0.25)
            m_Accumulator = m_Target;
    }

    void Wait()
    {
        while (m_Accumulator < m_Target)
        {
            Sleep(0);

            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);

            FLOAT delta = FLOAT(now.QuadPart - m_Last.QuadPart) / m_Frequency.QuadPart;

            m_Last = now;
            m_Accumulator += delta;
        }

        m_Accumulator -= m_Target;
    }

private:
    LARGE_INTEGER m_Frequency;
    LARGE_INTEGER m_Last;
    FLOAT m_Accumulator;
    FLOAT m_Target;
};