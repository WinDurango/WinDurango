#pragma once
#include "d3d11_x.g.h"

#define D3D11X_MISC_FLAGS_MASK (0x4000000 | 0x8000000 | 0x20000 | 0x40000 | 0x80000 | 0x100000 | 0x200000)
#define D3D11_MISC_FLAGS_MASK                                                                                          \
    (D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_SHARED | D3D11_RESOURCE_MISC_TEXTURECUBE |                \
     D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS | D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS |                              \
     D3D11_RESOURCE_MISC_BUFFER_STRUCTURED | D3D11_RESOURCE_MISC_RESOURCE_CLAMP |                                      \
     D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX | D3D11_RESOURCE_MISC_GDI_COMPATIBLE |                                      \
     D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_RESTRICTED_CONTENT |                                    \
     D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE | D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER |              \
     D3D11_RESOURCE_MISC_GUARDED)
#define D3D11_CREATE_DEFERRED_CONTEXT_DRAW_BUNDLES 0x20000

inline UINT ConvertMiscFlags(UINT MiscFlags)
{
    UINT Flags = (MiscFlags & ~D3D11X_MISC_FLAGS_MASK) & D3D11_MISC_FLAGS_MASK;

    if (MiscFlags & 0x4000000)
        Flags |= D3D11_RESOURCE_MISC_TILE_POOL;

    if (MiscFlags & 0x8000000)
        Flags |= D3D11_RESOURCE_MISC_TILED;

    return Flags;
}

template <abi_t ABI> class D3D11DeviceX : public gfx::ID3D11DeviceX<ABI>
{
public:
    ID3D11Device2 *m_pFunction;

    D3D11DeviceX(ID3D11Device2* pDevice)
    {
        m_pFunction = pDevice;
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
    // ID3D11Device
    //
    HRESULT CreateBuffer(D3D11_BUFFER_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                         gfx::ID3D11Buffer<ABI> **ppBuffer);
    HRESULT CreateTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                            gfx::ID3D11Texture1D<ABI> **ppTexture1D);
    HRESULT CreateTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                            gfx::ID3D11Texture2D<ABI> **ppTexture2D);
    HRESULT CreateTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                            gfx::ID3D11Texture3D<ABI> **ppTexture3D);
    HRESULT CreateShaderResourceView(gfx::ID3D11Resource<ABI> *pResource, D3D11_SHADER_RESOURCE_VIEW_DESC const *pDesc,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppSRV);
    HRESULT CreateUnorderedAccessView(gfx::ID3D11Resource<ABI> *pResource,
                                      D3D11_UNORDERED_ACCESS_VIEW_DESC const *pDesc,
                                      gfx::ID3D11UnorderedAccessView<ABI> **ppUAV);
    HRESULT CreateRenderTargetView(gfx::ID3D11Resource<ABI> *pResource, D3D11_RENDER_TARGET_VIEW_DESC const *pDesc,
                                   gfx::ID3D11RenderTargetView<ABI> **ppRTV);
    HRESULT CreateDepthStencilView(gfx::ID3D11Resource<ABI> *pResource, D3D11_DEPTH_STENCIL_VIEW_DESC const *pDesc,
                                   gfx::ID3D11DepthStencilView<ABI> **ppDSV);
    HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC const *pDesc, uint32_t NumElements,
                              void const *pShaderBytecodeWithInputSignature, uint64_t BytecodeLength,
                              ID3D11InputLayout **ppInputLayout);
    HRESULT CreateVertexShader(void const *pBytecode, uint64_t BytecodeLength, ID3D11ClassLinkage *pClassLinkage,
                               gfx::ID3D11VertexShader<ABI> **ppVS);
    HRESULT CreateGeometryShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage,
                                 gfx::ID3D11GeometryShader<ABI> **ppGS);
    HRESULT CreateGeometryShaderWithStreamOutput(void const *pBytecode, uint64_t BytecodeLentgh,
                                                 D3D11_SO_DECLARATION_ENTRY const *pSODeclaration, uint32_t NumEntries,
                                                 uint32_t const *pStrides, uint32_t NumStides,
                                                 uint32_t RasterizedStream, ID3D11ClassLinkage *pClassLinkage,
                                                 gfx::ID3D11GeometryShader<ABI> **ppGS);
    HRESULT CreatePixelShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage,
                              gfx::ID3D11PixelShader<ABI> **ppPS);
    HRESULT CreateHullShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage,
                             gfx::ID3D11HullShader<ABI> **ppHS);
    HRESULT CreateDomainShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage,
                               gfx::ID3D11DomainShader<ABI> **ppDS);
    HRESULT CreateComputeShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage,
                                gfx::ID3D11ComputeShader<ABI> **ppCS);
    HRESULT CreateClassLinkage(ID3D11ClassLinkage **ppClassLinkage);
    HRESULT CreateBlendState(D3D11_BLEND_DESC const *pDesc, gfx::ID3D11BlendState<ABI> **ppBlendState);
    HRESULT CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC const *pDesc,
                                    gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState);
    HRESULT CreateRasterizerState(D3D11_RASTERIZER_DESC const *pDesc,
                                  gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
    HRESULT CreateSamplerState(D3D11_SAMPLER_DESC const *pDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState);
    HRESULT CreateQuery(D3D11_QUERY_DESC const *pDesc, ID3D11Query **ppQuery);
    HRESULT CreatePredicate(D3D11_QUERY_DESC const *pDesc, ID3D11Predicate **ppPrediticate);
    HRESULT CreateCounter(D3D11_COUNTER_DESC const *pDesc, ID3D11Counter **ppCounter);
    HRESULT CreateDeferredContext(uint32_t Flags, gfx::ID3D11DeviceContext<ABI> **ppDeferredContext);
    HRESULT OpenSharedResource(void *pResource, _GUID const &retInterface, void **ppResource);
    HRESULT CheckFormatSupport(DXGI_FORMAT Format, uint32_t *pFormatSupport);
    HRESULT CheckMultisampleQualityLevels(DXGI_FORMAT Format, uint32_t SampleCount, uint32_t *pNumQualityLevels);
    void CheckCounterInfo(D3D11_COUNTER_INFO *pCounterInfo);
    HRESULT CheckCounter(D3D11_COUNTER_DESC const *pDesc, D3D11_COUNTER_TYPE *pCounterType, uint32_t *pActiveCounters,
                         char *szName, uint32_t *pNameLength, char *szUnits, uint32_t *pUnitsLength,
                         char *szDescription, uint32_t *pDescriptionLength);
    HRESULT CheckFeatureSupport(D3D11_FEATURE Feature, void *pFeatureSupportData, uint32_t FeatureSupportDataSize);
    HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData);
    HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData);
    HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    D3D_FEATURE_LEVEL GetFeatureLevel();
    uint32_t GetCreationFlags();
    HRESULT GetDeviceRemovedReason();
    void GetImmediateContext(gfx::ID3D11DeviceContext<ABI> **ppImmediateContext);
    HRESULT SetExceptionMode(uint32_t ExceptionMode);
    uint32_t GetExceptionMode();

    //
    // ID3D11Device1
    //
    void GetImmediateContext1(gfx::ID3D11DeviceContext1<ABI> **ppImmediateContext);
    HRESULT CreateDeferredContext1(uint32_t Flags, gfx::ID3D11DeviceContext1<ABI> **ppDeferredContext1);
    HRESULT CreateBlendState1(D3D11_BLEND_DESC1 const *pDesc, ID3D11BlendState1 **ppBlendState);
    HRESULT CreateRasterizerState1(D3D11_RASTERIZER_DESC1 const *pDesc, ID3D11RasterizerState1 **ppRasterizerState);
    HRESULT CreateDeviceContextState(uint32_t Flags, D3D_FEATURE_LEVEL const *pFeatureLevels, uint32_t FeatureLevels,
                                     uint32_t SDKVersion, _GUID const &EmulatedInterface,
                                     D3D_FEATURE_LEVEL *pChosenFeatureLevel, ID3DDeviceContextState **ppContextState);
    HRESULT OpenSharedResource1(void *pResource, _GUID const &retInterface, void **ppResource);
    HRESULT OpenSharedResourceByName(wchar_t const *pName, uint32_t dwDesiredAccess, _GUID const &retInterface,
                                     void **ppResource);

    //
    // ID3D11Device2
    //
    void GetImmediateContext2(gfx::ID3D11DeviceContext2<ABI> **ppImmediateContext);
    HRESULT CreateDeferredContext2(uint32_t Flags, gfx::ID3D11DeviceContext2<ABI> **ppDeferredContext);
    void GetResourceTiling(gfx::ID3D11Resource<ABI> *pTiledResource, uint32_t *pNumTilesForEntireResource,
                           D3D11_PACKED_MIP_DESC *pPackedMipDesc, D3D11_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                           uint32_t *pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet,
                           D3D11_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips);
    HRESULT CheckMultisampleQualityLevels1(DXGI_FORMAT Format, uint32_t SampleCount, uint32_t Flags,
                                           uint32_t *pNumQualityLevels);

    //
    // ID3D11DeviceX
    //
    void GetImmediateContextX(gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX);
    HRESULT CreateCounterSet(gfx::D3D11X_COUNTER_SET_DESC const *pCounterSetDesc,
                             gfx::ID3D11CounterSetX **ppCounterSet);
    HRESULT CreateCounterSample(gfx::ID3D11CounterSampleX **ppCounterSample);
    HRESULT SetDriverHint(UINT Feature, UINT Value);
    HRESULT CreateDmaEngineContext(gfx::D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc,
                                   gfx::ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext);
    BOOL IsFencePending(UINT64 Fence);
    BOOL IsResourcePending(gfx::ID3D11Resource<ABI> *pResource);
    HRESULT CreatePlacementBuffer(D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress,
                                  gfx::ID3D11Buffer<ABI> **ppBuffer);
    HRESULT CreatePlacementTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                     void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D);
    HRESULT CreatePlacementTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                     void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D);
    HRESULT CreatePlacementTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                     void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D);
    void GetTimestamps(UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp);
    HRESULT CreateComputeContextX(gfx::D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc,
                                  gfx::ID3D11ComputeContextX **ppComputeContext);
    HRESULT CreateSamplerStateX(gfx::D3D11X_SAMPLER_DESC const *pSamplerDesc,
                                gfx::ID3D11SamplerState<ABI> **ppSamplerState);
    HRESULT CreateDeferredContextX(UINT Flags, gfx::ID3D11DeviceContextX<ABI> **ppDeferredContext);
    void GarbageCollect(UINT Flags);
    HRESULT CreateDepthStencilStateX(D3D11_DEPTH_STENCIL_DESC const *pDepthStencilStateDesc,
                                     gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState);
    HRESULT CreatePlacementRenderableTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                               gfx::D3D11X_RENDERABLE_TEXTURE_ADDRESSES const *pAddresses,
                                               gfx::ID3D11Texture2D<ABI> **ppTexture2D);
    void GetDriverStatistics(UINT StructSize, gfx::D3D11X_DRIVER_STATISTICS *pStatistics);
    HRESULT GetDescriptorSize(gfx::D3D11X_DESCRIPTOR_TYPE DescriptorType);
    void ComposeShaderResourceView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                   gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                   gfx::D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW *pDescriptorSrv);
    void ComposeUnorderedAccessView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                    gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                    gfx::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *pDescriptorUav);
    void ComposeConstantBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                   gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                   gfx::D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW *pDescriptorCb);
    void ComposeVertexBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                 gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                 gfx::D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW *pDescriptorVb);
    void ComposeSamplerState(gfx::D3D11X_SAMPLER_STATE_DESC const *pSamplerDesc,
                             gfx::D3D11X_DESCRIPTOR_SAMPLER_STATE *pDescriptorSamplerState);
    void PlaceSwapChainView(gfx::ID3D11Resource<ABI> *pSwapChainBuffer, gfx::ID3D11View<ABI> *pView);
    void SetDebugFlags(UINT Flags);
    uint32_t GetDebugFlags();
    void SetHangCallbacks(gfx::D3D11XHANGBEGINCALLBACK pBeginCallback, gfx::D3D11XHANGPRINTCALLBACK pPrintCallback,
                          gfx::D3D11XHANGDUMPCALLBACK pDumpCallback);
    void ReportGpuHang(UINT Flags);
    HRESULT SetGpuMemoryPriority(UINT Priority);
    void GetGpuHardwareConfiguration(gfx::D3D11X_GPU_HARDWARE_CONFIGURATION *pGpuHardwareConfiguration);

private:
        UINT m_DebugFlags = 0;
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DeviceX<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);