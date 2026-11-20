// WinDurango.D3D12X.cpp : Source file for your target.
//

#include "WinDurango.D3D12X.h"
#include "kernelx.h"
#include "WinDurango.Common/WinDurango.h"
#include <atomic>

// Logs a stub warning through WinDurango's logger only once per call site.
// Some of these (e.g. DXGIXPresentArray) run every frame, so a MessageBox or a log line per call
// would block or flood; the message accepts fmt arguments for the logged call's parameters.
// The call site is only marked as logged once the logger is initialized, so an early call
// doesn't swallow the warning.
#define D3D12X_STUB_ONCE(...)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        static std::atomic_bool s_stubLogged{false};                                                                   \
        if (!s_stubLogged.load(std::memory_order_relaxed))                                                             \
        {                                                                                                              \
            auto pWinDurango = wd::common::WinDurango::GetInstance();                                                  \
            if (pWinDurango->inited() && !s_stubLogged.exchange(true))                                                 \
                pWinDurango->log.Warn("WinDurango::D3D12X", __VA_ARGS__);                                              \
        }                                                                                                              \
    } while (0)

EXTERN_C HRESULT __stdcall EraD3D12CreateDevice(IUnknown* pAdapter, D3D_FEATURE_LEVEL MinimumFeatureLevel, const IID* const riid, void** ppDevice)
{
    D3D12X_STUB_ONCE("Unimplemented: D3D12CreateDevice (MinimumFeatureLevel=0x{:x})",
                     static_cast<unsigned>(MinimumFeatureLevel));
	return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall DXGIXSetVLineNotification(UINT VLineCounter, UINT VLineNum, HANDLE hEvent)
{
    //This stub was made based on how the function looks like in IDA
    D3D12X_STUB_ONCE("Unimplemented: DXGIXSetVLineNotification (VLineCounter={}, VLineNum={})", VLineCounter,
                     VLineNum);
    if (VLineCounter >= 2 || !VLineCounter && VLineNum || hEvent && VLineNum >= 0x465)
        return E_INVALIDARG;
    else
        return 0x1018 | 0x10000000;
}

EXTERN_C HRESULT __stdcall D3D12XboxSetProcessDebugFlags(UINT Flags)
{
    //DebugFlags should be (Flags | 0x700001) apparently
    D3D12X_STUB_ONCE("Unimplemented: D3D12XboxSetProcessDebugFlags (Flags=0x{:x})", Flags);
	return S_OK;
}

struct DXGIX_PRESENTARRAY_PARAMETERS
{
    BOOL Disable;
    BOOL UsePreviousBuffer;
    D3D12_RECT SourceRect;
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
    D3D12X_STUB_ONCE("Unimplemented: DXGIXPresentArray (NumSwapChains={}, SyncInterval={}, Flags=0x{:x})",
                     NumSwapChains, SyncInterval, Flags);
    return E_NOTIMPL;
}

EXTERN_C HRESULT __stdcall EraD3D12SerializeRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, D3D_ROOT_SIGNATURE_VERSION Version, ID3DBlob** ppBlob, ID3DBlob** ppErrorBlob)
{
    D3D12X_STUB_ONCE("Forwarding D3D12SerializeRootSignature to the desktop D3D12 runtime");
	return D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
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

EXTERN_C HRESULT __stdcall EraD3D12GetDebugInterface(const IID* riid, void** ppvDebug)

{
    D3D12X_STUB_ONCE("Forwarding D3D12GetDebugInterface to the desktop D3D12 runtime");

    if (!riid)
        return E_INVALIDARG;

    const IID &DebugInterfaceGUID = (*riid);
    return D3D12GetDebugInterface(DebugInterfaceGUID, ppvDebug);

}

#pragma comment(linker, "/export:D3D12CreateDevice=EraD3D12CreateDevice,@7")
#pragma comment(linker, "/export:D3D12GetDebugInterface=EraD3D12GetDebugInterface,@9")
#pragma comment(linker, "/export:D3D12SerializeRootSignature=EraD3D12SerializeRootSignature,@10")
#pragma comment(linker, "/export:D3D12XboxSetProcessDebugFlags,@11")
#pragma comment(linker, "/export:D3DMapEsramMemory,@16")
#pragma comment(linker, "/export:DXGIXPresentArray,@18")
#pragma comment(linker, "/export:DXGIXSetVLineNotification,@20")
