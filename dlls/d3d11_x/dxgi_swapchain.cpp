#include "dxgi_swapchain.h"

#include "resource.hpp"
#include "overlay/overlay.h"

HRESULT wd::dxgi_swapchain::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == __uuidof(wdi::IDXGISwapChain1))
	{
		*ppvObject = this;
		AddRef( );
		return S_OK;
	}

	if (riid == __uuidof(wdi::IGraphicsUnwrap))
	{
		*ppvObject = wrapped_interface;
		return S_OK;
	}

	TRACE_INTERFACE_NOT_HANDLED("dxgi_swapchain");
	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

HRESULT wd::dxgi_swapchain::GetParent(const IID& riid, void** ppParent)
{
	return wrapped_interface->GetParent(riid, ppParent);
}

HRESULT wd::dxgi_swapchain::GetDevice(const IID& riid, void** ppDevice)
{
	return wrapped_interface->GetDevice(riid, ppDevice);
}

HRESULT wd::dxgi_swapchain::Present(UINT SyncInterval, UINT Flags)
{
	if (wd::g_Overlay)
		wd::g_Overlay->Present( );

	return wrapped_interface->Present(SyncInterval, Flags);
}

HRESULT wd::dxgi_swapchain::GetBuffer(UINT Buffer, const IID& riid, void** ppSurface)
{
	bool incRef = false;

	if (riid == __uuidof(ID3D11Texture1D))
	{
		ID3D11Texture1D* texture1d = nullptr;
		HRESULT hr = wrapped_interface->GetBuffer(Buffer, IID_PPV_ARGS(&texture1d));
		*ppSurface = new texture_1d(texture1d);
		incRef = true;
	}
	else if (riid == __uuidof(ID3D11Texture2D))
	{
		ID3D11Texture2D* texture2d = nullptr;
		HRESULT hr = wrapped_interface->GetBuffer(Buffer, IID_PPV_ARGS(&texture2d));
		*ppSurface = new texture_2d(texture2d);
		incRef = true;
	}
	else if (riid == __uuidof(ID3D11Texture3D))
	{
		ID3D11Texture3D* texture3d = nullptr;
		HRESULT hr = wrapped_interface->GetBuffer(Buffer, IID_PPV_ARGS(&texture3d));
		*ppSurface = new texture_3d(texture3d);
		incRef = true;
	}

	if (incRef)
	{
		AddRef( );
		return S_OK;
	}

	TRACE_INTERFACE_NOT_HANDLED("dxgi_swapchain - GetBuffer");
	*ppSurface = nullptr;
	return E_NOINTERFACE;
}

HRESULT wd::dxgi_swapchain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
	return wrapped_interface->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT wd::dxgi_swapchain::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
	return wrapped_interface->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT wd::dxgi_swapchain::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
	return wrapped_interface->GetDesc(pDesc);
}

HRESULT wd::dxgi_swapchain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat,
	UINT SwapChainFlags)
{
	return wrapped_interface->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT wd::dxgi_swapchain::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
	return wrapped_interface->ResizeTarget(pNewTargetParameters);
}

HRESULT wd::dxgi_swapchain::GetContainingOutput(IDXGIOutput** ppOutput)
{
	return wrapped_interface->GetContainingOutput(ppOutput);
}

HRESULT wd::dxgi_swapchain::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
	return wrapped_interface->GetFrameStatistics(pStats);
}

HRESULT wd::dxgi_swapchain::GetLastPresentCount(UINT* pLastPresentCount)
{
	return wrapped_interface->GetLastPresentCount(pLastPresentCount);
}

HRESULT wd::dxgi_swapchain::GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc)
{
	return wrapped_interface->GetDesc1(pDesc);
}

HRESULT wd::dxgi_swapchain::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc)
{
	return wrapped_interface->GetFullscreenDesc(pDesc);
}

HRESULT wd::dxgi_swapchain::GetHwnd(HWND* pHwnd)
{
	return wrapped_interface->GetHwnd(pHwnd);
}

HRESULT wd::dxgi_swapchain::GetCoreWindow(const IID& refiid, void** ppUnk)
{
	return wrapped_interface->GetCoreWindow(refiid, ppUnk);
}

HRESULT wd::dxgi_swapchain::Present1(UINT SyncInterval, UINT PresentFlags,
	const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	if (wd::g_Overlay)
		wd::g_Overlay->Present( );

	return wrapped_interface->Present1(SyncInterval, PresentFlags, pPresentParameters);
}

BOOL wd::dxgi_swapchain::IsTemporaryMonoSupported()
{
	return wrapped_interface->IsTemporaryMonoSupported( );
}

HRESULT wd::dxgi_swapchain::GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput)
{
	return wrapped_interface->GetRestrictToOutput(ppRestrictToOutput);
}

HRESULT wd::dxgi_swapchain::SetBackgroundColor(const DXGI_RGBA* pColor)
{
	return wrapped_interface->SetBackgroundColor(pColor);
}

HRESULT wd::dxgi_swapchain::GetBackgroundColor(DXGI_RGBA* pColor)
{
	return wrapped_interface->GetBackgroundColor(pColor);
}

HRESULT wd::dxgi_swapchain::SetRotation(DXGI_MODE_ROTATION Rotation)
{
	return wrapped_interface->SetRotation(Rotation);
}

HRESULT wd::dxgi_swapchain::GetRotation(DXGI_MODE_ROTATION* pRotation)
{
	return wrapped_interface->GetRotation(pRotation);
}
