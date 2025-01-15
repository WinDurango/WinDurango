#include "pch.h"
#include "d3d11_x_device.h"
#include "d3d_x.hpp"
#include "../IDXGIWrappers.h"
#include "../ID3DWrappers.h"

#pragma region ID3D11DeviceX

// QueryInterface need to be in the cpp file because of circular dependency for IDXGIDeviceWrapper :}

#define TEXTURE_MISCFLAGS_MASK (D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_SHARED | D3D11_RESOURCE_MISC_TEXTURECUBE | \
								D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS | D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS | D3D11_RESOURCE_MISC_BUFFER_STRUCTURED | \
								D3D11_RESOURCE_MISC_RESOURCE_CLAMP | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX | D3D11_RESOURCE_MISC_GDI_COMPATIBLE | \
								D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_RESTRICTED_CONTENT | D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE | \
								D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER | D3D11_RESOURCE_MISC_GUARDED | \
								D3D11_RESOURCE_MISC_TILED | D3D11_RESOURCE_MISC_HW_PROTECTED | D3D11_RESOURCE_MISC_SHARED_DISPLAYABLE | D3D11_RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER)

#define ERROR_LOG_FUNC() if(FAILED(hr)) { printf("[%s] hresult fail 0x%X\n", __func__, hr); }
#define ERROR_LOG_HRES(res) printf("[%s] hresult fail 0x%X\n", __func__, res);

HRESULT d3d11x::D3D11DeviceXWrapperX::QueryInterface(REFIID riid, void** ppvObject)
{
    // note from unixian: for debugging purposes
    char iidstr[ sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}") ];
    OLECHAR iidwstr[ sizeof(iidstr) ];
    StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
    WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
    printf("[D3D11DeviceXWrapperX] QueryInterface: %s\n", iidstr);

    if (riid == __uuidof(ID3D11DeviceX) || riid == __uuidof(ID3D11Device2) ||
        riid == __uuidof(ID3D11Device1) || riid == __uuidof(ID3D11Device))
    {
        *ppvObject = static_cast<ID3D11DeviceX*>(this);
        AddRef( );
        return S_OK;
    }
    else if (riid == __uuidof(ID3D11PerformanceDeviceX))
    {
        *ppvObject = reinterpret_cast<ID3D11PerformanceDeviceX*>(this);
        AddRef( );
        return S_OK;
    }

    if (riid == __uuidof(IDXGIDevice) ||
        riid == __uuidof(IDXGIDevice1))
    {
        HRESULT hr = m_realDevice->QueryInterface(__uuidof(IDXGIDevice1), ppvObject);
        *ppvObject = new IDXGIDeviceWrapper(static_cast<IDXGIDevice1*>(*ppvObject));
        return S_OK;
    }

    return m_realDevice->QueryInterface(riid, ppvObject);
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateTexture1D(
            const D3D11_TEXTURE1D_DESC* pDesc,
            const D3D11_SUBRESOURCE_DATA* pInitialData,
            ID3D11Texture1D_X** ppTexture1D) {

    ID3D11Texture1D* texture1d = nullptr;
    HRESULT hr = m_realDevice->CreateTexture1D(pDesc, pInitialData, &texture1d);

    printf("[CreateTexture1D] created texture at 0x%llX\n", texture1d);

    ERROR_LOG_FUNC( );
    if (ppTexture1D != nullptr)
    {
        *ppTexture1D = SUCCEEDED(hr) ? new ID3D11Texture1DWrapper(texture1d) : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateTexture2D(
			D3D11_TEXTURE2D_DESC* pDesc,
            const D3D11_SUBRESOURCE_DATA* pInitialData,
            ID3D11Texture2D_X** ppTexture2D) {

    ID3D11Texture2D* texture2d = nullptr;
	pDesc->MiscFlags &= TEXTURE_MISCFLAGS_MASK; // remove all flags that are xbox-one only flags

    if (pDesc->Usage == D3D11_USAGE_DYNAMIC)
		pDesc->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = m_realDevice->CreateTexture2D(pDesc, pInitialData, &texture2d);

    printf("[CreateTexture2D] created texture at 0x%llX\n", texture2d);

    ERROR_LOG_FUNC( );
    if (ppTexture2D != nullptr)
    {
        *ppTexture2D = SUCCEEDED(hr) ? new ID3D11Texture2DWrapper(texture2d) : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateTexture3D(
            const D3D11_TEXTURE3D_DESC* pDesc,
            const D3D11_SUBRESOURCE_DATA* pInitialData,
            ID3D11Texture3D_X** ppTexture3D) {

    ID3D11Texture3D* texture3d = nullptr;
    HRESULT hr = m_realDevice->CreateTexture3D(pDesc, pInitialData, &texture3d);

    printf("[CreateTexture3D] created texture at 0x%llX\n", texture3d);

    ERROR_LOG_FUNC( );
    if (ppTexture3D != nullptr)
    {
        *ppTexture3D = SUCCEEDED(hr) ? new ID3D11Texture3DWrapper(texture3d) : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateShaderResourceView(
            ID3D11Resource* pResource,
            const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
            ID3D11ShaderResourceView_X** ppSRView)  {

    ::ID3D11ShaderResourceView* target = nullptr;
    HRESULT hr = m_realDevice->CreateShaderResourceView(reinterpret_cast<ID3D11ResourceWrapperX*>(pResource)->m_realResource, pDesc, &target);

    ERROR_LOG_FUNC( );
    if (ppSRView != nullptr)
    {
        *ppSRView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11ShaderResourceView_X*>(new ID3D11ShaderResourceViewWrapper(target))
            : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateUnorderedAccessView(
            ID3D11Resource* pResource,
            const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc,
            ID3D11UnorderedAccessView_X** ppUAView) {

    ::ID3D11UnorderedAccessView* target = nullptr;
    HRESULT hr = m_realDevice->CreateUnorderedAccessView(reinterpret_cast<ID3D11ResourceWrapperX*>(pResource)->m_realResource, pDesc, &target);

    ERROR_LOG_FUNC( );
    if (ppUAView != nullptr)
    {
        *ppUAView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11UnorderedAccessView_X*>(new ID3D11UnorderedAccessViewWrapper(target))
            : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateRenderTargetView(
            ID3D11Resource* pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
            ID3D11RenderTargetView_X** ppRTView) {

    ::ID3D11RenderTargetView* target = nullptr;
    HRESULT hr = m_realDevice->CreateRenderTargetView(reinterpret_cast<ID3D11ResourceWrapperX*>(pResource)->m_realResource, pDesc, &target);

    ERROR_LOG_FUNC( );
    if (ppRTView != nullptr)
    {
        *ppRTView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11RenderTargetView_X*>(new ID3D11RenderTargetViewWrapper(target))
            : nullptr;
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateDepthStencilView(
            ID3D11Resource* pResource,
            const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
            ID3D11DepthStencilView_X** ppDepthStencilView) {

    ::ID3D11DepthStencilView* target = nullptr;
    HRESULT hr = m_realDevice->CreateDepthStencilView(reinterpret_cast<ID3D11ResourceWrapperX*>(pResource)->m_realResource, pDesc, &target);

    ERROR_LOG_FUNC( );
    if (ppDepthStencilView != nullptr)
    {
        *ppDepthStencilView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11DepthStencilView_X*>(new ID3D11DepthStencilViewWrapper(target))
            : nullptr;
    }

    return hr;
}

void d3d11x::D3D11DeviceXWrapperX::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext)
{
    ::ID3D11DeviceContext* ctx{};
    m_realDevice->GetImmediateContext(&ctx);

    if (!ctx) return;

    ::ID3D11DeviceContext2* ctx2{};
    ctx->QueryInterface(IID_PPV_ARGS(&ctx2));

    *ppImmediateContext = reinterpret_cast<d3d11x::ID3D11DeviceContext*>(new d3d11x::ID3D11DeviceContextXWrapper(ctx2));
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateDeferredContext(UINT ContextFlags, d3d11x::ID3D11DeviceContext** ppDeferredContext)
{
    ::ID3D11DeviceContext* ctx{};
    HRESULT hr = m_realDevice->CreateDeferredContext(ContextFlags, &ctx);

    ERROR_LOG_FUNC( );
    if (ppDeferredContext != nullptr && SUCCEEDED(hr))
    {
        ::ID3D11DeviceContext2* ctx2{};
        ctx->QueryInterface(IID_PPV_ARGS(&ctx2));

        *ppDeferredContext = reinterpret_cast<d3d11x::ID3D11DeviceContext*>(new d3d11x::ID3D11DeviceContextXWrapper(ctx2));
    }

    return hr;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateBuffer(
               const D3D11_BUFFER_DESC* pDesc,
               const D3D11_SUBRESOURCE_DATA* pInitialData,
               d3d11x::ID3D11Buffer_X** ppBuffer)
{
    ID3D11Buffer* buffer = nullptr;
    HRESULT hr = m_realDevice->CreateBuffer(pDesc, pInitialData, &buffer);

    ERROR_LOG_FUNC( );
    if (ppBuffer != nullptr)
    {
        *ppBuffer = SUCCEEDED(hr) ? new ID3D11BufferWrapper(buffer) : nullptr;
    }

    return hr;
}


void d3d11x::D3D11DeviceXWrapperX::GetImmediateContextX(
    _Out_ ID3D11DeviceContextX** ppImmediateContextX)
{
    printf("[D3D11DeviceXWrapperX] GetImmediateContextX");
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateCounterSet(
    _In_ const D3D11X_COUNTER_SET_DESC* pCounterSetDesc,
    _Out_opt_ ID3D11CounterSetX** ppCounterSet)
{
    printf("[D3D11DeviceXWrapperX] CreateCounterSet");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateCounterSample(
    _Out_opt_ ID3D11CounterSampleX** ppCounterSample)
{
    printf("[D3D11DeviceXWrapperX] CreateCounterSample");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::SetDriverHint(
    _In_ UINT Feature,
    _In_ UINT Value)
{
    printf("[D3D11DeviceXWrapperX] SetDriverHint");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateDmaEngineContext(
    _In_ const D3D11_DMA_ENGINE_CONTEXT_DESC* pDmaEngineContextDesc,
    _Out_ d3d11x::ID3D11DmaEngineContextX** ppDmaDeviceContext)
{
    printf("[D3D11DeviceXWrapperX] CreateDmaEngineContext");
    return E_NOTIMPL;
}

BOOL d3d11x::D3D11DeviceXWrapperX::IsFencePending(UINT64 Fence)
{
    printf("[D3D11DeviceXWrapperX] IsFencePending");
    return E_NOTIMPL;
}

BOOL d3d11x::D3D11DeviceXWrapperX::IsResourcePending(
    _In_ ID3D11Resource* pResource)
{
    printf("[D3D11DeviceXWrapperX] IsResourcePending");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreatePlacementBuffer(
    _In_ const D3D11_BUFFER_DESC* pDesc,
    _In_ void* pAddress,
    _Out_opt_ ID3D11Buffer** ppBuffer)
{
    printf("[D3D11DeviceXWrapperX] CreatePlacementBuffer");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreatePlacementTexture1D(
    _In_ const D3D11_TEXTURE1D_DESC* pDesc,
    _In_ UINT TileModeIndex,
    _In_ UINT Pitch,
    _In_ void* pAddress,
    _Out_opt_ ID3D11Texture1D** ppTexture1D)
{
    printf("[D3D11DeviceXWrapperX] CreatePlacementTexture1D");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreatePlacementTexture2D(
    _In_ const D3D11_TEXTURE2D_DESC* pDesc,
    _In_ UINT TileModeIndex,
    _In_ UINT Pitch,
    _In_ void* pAddress,
    _Out_opt_ ID3D11Texture2D** ppTexture2D)
{
    printf("[D3D11DeviceXWrapperX] CreatePlacementTexture2D");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreatePlacementTexture3D(
    _In_ const D3D11_TEXTURE3D_DESC* pDesc,
    _In_ UINT TileModeIndex,
    _In_ UINT Pitch,
    _In_ void* pAddress,
    _Out_opt_ ID3D11Texture3D** ppTexture3D)
{
    printf("[D3D11DeviceXWrapperX] CreatePlacementTexture3D");
    return E_NOTIMPL;
}

void d3d11x::D3D11DeviceXWrapperX::GetTimestamps(
    _Out_ UINT64* pGpuTimestamp,
    _Out_ UINT64* pCpuRdtscTimestamp)
{
    printf("[D3D11DeviceXWrapperX] GetTimestamps");
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateSamplerStateX(
    _In_ const d3d11x::D3D11X_SAMPLER_DESC* pSamplerDesc,
    _Out_opt_ ID3D11SamplerState** ppSamplerState)
{
    printf("[D3D11DeviceXWrapperX] CreateSamplerStateX");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateDeferredContextX(
    UINT ContextFlags,
    _Out_ d3d11x::ID3D11DeviceContextX** ppDeferredContext)
{
    printf("[D3D11DeviceXWrapperX] CreateDeferredContextX");
    return E_NOTIMPL;
}

void d3d11x::D3D11DeviceXWrapperX::GarbageCollect(
    _In_ UINT Flags)
{
    printf("[D3D11DeviceXWrapperX] GarbageCollect");
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateDepthStencilStateX(
    _In_ const D3D11_DEPTH_STENCIL_DESC* pDepthStencilStateDescX,
    _Out_opt_ ID3D11DepthStencilState** ppDepthStencilState)
{
    printf("[D3D11DeviceXWrapperX] CreateDepthStencilStateX");
    return E_NOTIMPL;
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreatePlacementRenderableTexture2D(
    _In_ const D3D11_TEXTURE2D_DESC* pDesc,
    _In_ UINT TileModeIndex,
    _In_ UINT Pitch,
    _In_ const D3D11X_RENDERABLE_TEXTURE_ADDRESSES* pAddresses,
    _Out_opt_ ID3D11Texture2D** ppTexture2D)
{
    printf("[D3D11DeviceXWrapperX] CreatePlacementRenderableTexture2D");
    return E_NOTIMPL;
}

void d3d11x::D3D11DeviceXWrapperX::GetDriverStatistics(
    _In_ UINT StructSize,
    _Out_ D3D11X_DRIVER_STATISTICS* pStatistics)
{
    printf("[D3D11DeviceXWrapperX] GetDriverStatistics");
}

HRESULT d3d11x::D3D11DeviceXWrapperX::CreateComputeContextX(
    _In_ const d3d11x::D3D11_COMPUTE_CONTEXT_DESC* pComputeContextDesc,
    _Out_ d3d11x::ID3D11ComputeContextX** ppComputeContext)
{
    printf("[D3D11DeviceXWrapperX] CreateComputeContextX");
    return E_NOTIMPL;
}

void d3d11x::D3D11DeviceXWrapperX::ComposeShaderResourceView(
    _In_ const D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
    _In_opt_ const d3d11x::D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
    _Out_ d3d11x::D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW* pDescriptorSrv)
{
    printf("[D3D11DeviceXWrapperX] ComposeShaderResourceView");
}

void d3d11x::D3D11DeviceXWrapperX::ComposeUnorderedAccessView(
    _In_ const D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
    _In_opt_ const D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
    _Out_ d3d11x::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW* pDescriptorUav)
{
    printf("[D3D11DeviceXWrapperX] ComposeUnorderedAccessView");
}

void d3d11x::D3D11DeviceXWrapperX::ComposeConstantBufferView(
    _In_ const D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
    _In_opt_ const D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
    _Out_ D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW* pDescriptorCb)
{
    printf("[D3D11DeviceXWrapperX] ComposeConstantBufferView");
}

void d3d11x::D3D11DeviceXWrapperX::ComposeVertexBufferView(
    _In_ const D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
    _In_opt_ const D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
    _Out_ D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW* pDescriptorVb)
{
    printf("[D3D11DeviceXWrapperX] ComposeVertexBufferView");
}

void d3d11x::D3D11DeviceXWrapperX::ComposeSamplerState(
    _In_opt_ const d3d11x::D3D11X_SAMPLER_STATE_DESC* pSamplerDesc,
    _Out_ d3d11x::D3D11X_DESCRIPTOR_SAMPLER_STATE* pDescriptorSamplerState)
{
    printf("[D3D11DeviceXWrapperX] ComposeSamplerState");
}

void d3d11x::D3D11DeviceXWrapperX::PlaceSwapChainView(
    _In_ ID3D11Resource* pSwapChainBuffer,
    _Inout_ ID3D11View* pView)
{
    printf("[D3D11DeviceXWrapperX] PlaceSwapChainView");
}

void d3d11x::D3D11DeviceXWrapperX::SetDebugFlags(
    _In_ UINT Flags)
{
    printf("[D3D11DeviceXWrapperX] SetDebugFlags");
}

UINT d3d11x::D3D11DeviceXWrapperX::GetDebugFlags( )
{
    printf("[D3D11DeviceXWrapperX] GetDebugFlags");
    return {};
}

void d3d11x::D3D11DeviceXWrapperX::SetHangCallbacks(
    _In_ d3d11x::D3D11XHANGBEGINCALLBACK pBeginCallback,
    _In_ d3d11x::D3D11XHANGPRINTCALLBACK pPrintCallback,
    _In_ d3d11x::D3D11XHANGDUMPCALLBACK pDumpCallback)
{
    printf("[D3D11DeviceXWrapperX] SetHangCallbacks");
}

void d3d11x::D3D11DeviceXWrapperX::ReportGpuHang(
    _In_ UINT Flags)
{
    printf("[D3D11DeviceXWrapperX] ReportGpuHang");
}

HRESULT d3d11x::D3D11DeviceXWrapperX::SetGpuMemoryPriority(
    _In_ UINT Priority)
{
    printf("[D3D11DeviceXWrapperX] SetGpuMemoryPriority");
    return E_NOTIMPL;
}

void d3d11x::D3D11DeviceXWrapperX::GetGpuHardwareConfiguration(
    _Out_ d3d11x::D3D11X_GPU_HARDWARE_CONFIGURATION* pGpuHardwareConfiguration)
{
    static d3d11x::D3D11X_GPU_HARDWARE_CONFIGURATION dummyHardwareConfig = { 0, D3D11X_HARDWARE_VERSION_XBOX_ONE, 0 };
    printf("[D3D11DeviceXWrapperX] GetGpuHardwareConfiguration\n");
	*pGpuHardwareConfiguration = dummyHardwareConfig;
}
#pragma endregion