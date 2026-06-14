#include "d3d11.x.h"
#include "IIDExports.h"
#include "d3d11_x.g.h"
#include "ID3D11Runtime.h"
#include "kernelx.h"

EXTERN_C HRESULT __stdcall EraD3D10CreateBlob()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall EraD3D11CreateDevice(void *pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software,
                                                UINT Flags, const D3D_FEATURE_LEVEL *pFeatureLevels, UINT FeatureLevels,
                                                UINT SDKVersion, void **ppDevice, D3D_FEATURE_LEVEL *pFeatureLevel,
                                                void **ppImmediateContext)
{
    ID3D11Runtime *pRuntime;
    d3d11CreateInstance<D3D11Runtime>(g_ABI, (void **)&pRuntime);
    auto hr = pRuntime->CreateDevice((void **)ppDevice, (void **)ppImmediateContext);
    return hr;
}

EXTERN_C HRESULT __stdcall EraD3D11CreateDeviceAndSwapChain()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

struct D3D11X_CREATE_DEVICE_PARAMETERS
{
    UINT Version;
    UINT Flags;
    void *pOffchipTessellationBuffer;
    void *pTessellationFactorsBuffer;
    UINT DeferredDeletionThreadAffinityMask;
    UINT ImmediateContextDeRingSizeBytes;
    UINT ImmediateContextCeRingSizeBytes;
    UINT ImmediateContextDeSegmentSizeBytes;
    UINT ImmediateContextCeSegmentSizeBytes;
};

EXTERN_C HRESULT __stdcall D3D11XCreateDeviceX(const D3D11X_CREATE_DEVICE_PARAMETERS *pParameters, void **ppDevice,
                                               void **ppImmediateContext)
{
    ID3D11Runtime *pRuntime;
    d3d11CreateInstance<D3D11Runtime>(g_ABI, (void **)&pRuntime);
    auto hr = pRuntime->CreateDevice((void **)ppDevice, (void **)ppImmediateContext);
    return hr;
}

EXTERN_C HRESULT __stdcall D3D11XCreateDeviceXAndSwapChain1(const D3D11X_CREATE_DEVICE_PARAMETERS *pParameters,
                                                            const DXGI_SWAP_CHAIN_DESC1 *pSwapChainDesc,
                                                            void **ppSwapChain, void **ppDevice,
                                                            void **ppImmediateContext)
{
    ID3D11Runtime *pRuntime;
    d3d11CreateInstance<D3D11Runtime>(g_ABI, (void **)&pRuntime);
    auto hr = pRuntime->CreateDevice((void **)ppDevice, (void **)ppImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = pRuntime->CreateSwapChain(ppSwapChain, (*ppDevice), pSwapChainDesc);
    return hr;
}

EXTERN_C HRESULT __stdcall D3DAllocateGraphicsMemory(SIZE_T dwSize, UINT64 a2, void *a3, int a4, void **a5)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall D3DConfigureVirtualMemory(UINT64 a1)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall D3DFreeGraphicsMemory(void *pAddress)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall D3DMapEsramMemory(UINT Flags, void *pVirtualAddress, UINT NumPages, const UINT *pPageList)
{
    DWORD flAllocationType = 0;

    if ((Flags & 1) != 0)
        flAllocationType = MEM_LARGE_PAGES;
    else if ((Flags & 2) != 0)
        flAllocationType = MEM_4MB_PAGES;

    return MapTitleEsramPages(pVirtualAddress, NumPages, flAllocationType, pPageList);
}

struct DXGIX_FRAME_STATISTICS
{
    UINT64 CPUTimePresentCalled;
    UINT64 CPUTimeAddedToQueue;
    UINT QueueLengthAddedToQueue;
    UINT64 CPUTimeFrameComplete;
    UINT64 GPUTimeFrameComplete;
    UINT64 GPUCountTitleUsed;
    UINT64 GPUCountSystemUsed;
    UINT64 CPUTimeVSync;
    UINT64 GPUTimeVSync;
    UINT64 CPUTimeFlip;
    UINT64 GPUTimeFlip;
    UINT64 VSyncCount;
    float PercentScanned;
    void *Cookie[2];
};

EXTERN_C HRESULT __stdcall DXGIXGetFrameStatistics(UINT NumberFramesRequested, DXGIX_FRAME_STATISTICS *pFrameStatistics)
{
    return S_OK;
}

struct DXGIX_PRESENTARRAY_PARAMETERS
{
    BOOL Disable;
    BOOL UsePreviousBuffer;
    D3D11_RECT SourceRect;
    POINT DestRectUpperLeft;
    FLOAT ScaleFactorVert;
    FLOAT ScaleFactorHorz;
    void *Cookie;
    UINT Flags;
};

EXTERN_C HRESULT __stdcall DXGIXPresentArray(UINT SyncInterval, UINT PresentImmediateThreshold, UINT Flags,
                                             UINT NumSwapChains, void **ppSwapChains,
                                             const DXGIX_PRESENTARRAY_PARAMETERS *pPresentParameters)
{
    if (!g_PresentArrayHelper)
    {
        d3d11CreateInstance<DXGIXPresentArrayHelper>(g_ABI, (void **)&g_PresentArrayHelper);
    }

    g_PresentArrayHelper->PresentArray(ppSwapChains, NumSwapChains, SyncInterval);
    return S_OK;
}

EXTERN_C HRESULT __stdcall DXGIXSetVLineNotification(UINT VLineCounter, UINT VLineNum, HANDLE hEvent)
{
    return S_OK;
}

#pragma comment(linker, "/export:D3D10CreateBlob=EraD3D10CreateBlob,@1")
#pragma comment(linker, "/export:D3D11CreateDevice=EraD3D11CreateDevice,@2")
#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=EraD3D11CreateDeviceAndSwapChain,@3")
#pragma comment(linker, "/export:D3D11XCreateDeviceX,@4")
#pragma comment(linker, "/export:D3D11XCreateDeviceXAndSwapChain1,@5")
#pragma comment(linker, "/export:D3DAllocateGraphicsMemory,@6")
#pragma comment(linker, "/export:D3DConfigureVirtualMemory,@7")
#pragma comment(linker, "/export:D3DFreeGraphicsMemory,@8")
#pragma comment(linker, "/export:D3DMapEsramMemory,@9")
#pragma comment(linker, "/export:DXGIXGetFrameStatistics,@10")
#pragma comment(linker, "/export:DXGIXPresentArray,@11")
#pragma comment(linker, "/export:DXGIXSetVLineNotification,@12")