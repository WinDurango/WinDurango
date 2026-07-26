#pragma once
#include "d3d11_x.g.h"
#include <map>
#include <mutex>
#include <vector>

#define D3D11_MAP_FLAG_ALLOW_USAGE_DEFAULT 0x00200000

ID3D11DeviceContext2 *g_Context = nullptr;

static std::map<UINT64, int> D3D11X_HARDWARE_TO_TOPOLOGY_MAP = {
    {0x000001ffc0009e00, 0}, {0x000003ffc0009e00, 1}, {0x000005ffc0009e00, 2}, {0x000007ffc0009e00, 3},
    {0x000009ffc0009e00, 4}, {0x00000dffc0009e00, 5}, {0x00000bffc0009e00, 6}, {0x000001ffc0009e00, 7},
    {0x000001ffc0009e00, 8}, {0x000001ffc0009e00, 9}, {0x0000157fc0009e00, 10}, {0x0000177fc0009e00, 11},
    {0x0000197fc0009e00, 12}, {0x00001b7fc0009e00, 13}, {0x00001dffc0009e00, 14}, {0x00001fffc0009e00, 15},
    {0x000021ffc0009e00, 16}, {0x000023ffc0009e00, 17}, {0x000025ffc0009e00, 18}, {0x000027ffc0009e00, 19},
    {0x000029ffc0009e00, 20}, {0x00002bffc0009e00, 21}, {0x00002dffc0009e00, 22}, {0x00002fffc0009e00, 23},
    {0x000031ffc0009e00, 24}, {0x000033ffc0009e00, 25}, {0x000035ffc0009e00, 26}, {0x000037ffc0009e00, 27},
    {0x000039ffc0009e00, 28}, {0x000001ffc0009e00, 29}, {0x000001ffc0009e00, 30}, {0x000001ffc0009e00, 31},
    {0x000001ffc0009e00, 32}, {0x001013ffc0009e00, 33}, {0x0020137fc0009e00, 34}, {0x00301354c0009e00, 35},
    {0x0040133fc0009e00, 36}, {0x00501332c0009e00, 37}, {0x00601329c0009e00, 38}, {0x00701323c0009e00, 39},
    {0x0080131fc0009e00, 40}, {0x0090131bc0009e00, 41}, {0x00a01318c0009e00, 42}, {0x00b01316c0009e00, 43},
    {0x00c01314c0009e00, 44}, {0x00d01312c0009e00, 45}, {0x00e01311c0009e00, 46}, {0x00f01310c0009e00, 47},
    {0x0100130fc0009e00, 48}, {0x0110130ec0009e00, 49}, {0x0120130dc0009e00, 50}, {0x0130130cc0009e00, 51},
    {0x0140130bc0009e00, 52}, {0x0150130bc0009e00, 53}, {0x0160130ac0009e00, 54}, {0x0170130ac0009e00, 55},
    {0x01801309c0009e00, 56}, {0x01901309c0009e00, 57}, {0x01a01308c0009e00, 58}, {0x01b01308c0009e00, 59},
    {0x01c01308c0009e00, 60}, {0x01d01307c0009e00, 61}, {0x01e01307c0009e00, 62}, {0x01f01307c0009e00, 63},
    {0x02001307c0009e00, 64}
};

struct ID3D11BackgroundContext : IUnknown
{
    // Returns TRUE if the context has executed all of its commands
    virtual BOOL ExecuteContext() = 0;
};

template <abi_t ABI> class D3D11DeviceContextX : public gfx::ID3D11DeviceContextX<ABI>
{
public:
    ID3D11DeviceContext2 *m_pFunction;

    D3D11DeviceContextX(ID3D11DeviceContext2 *pContext)
    {
        if (this->m_RefCount != 0)
            this->m_RefCount = 0;
        m_pFunction = pContext;
        g_Context = m_pFunction;
        InterlockedIncrement(&this->m_RefCount);
        memcpy(&this->m_Function, *(void ***)this, sizeof(this->m_Function));
    }
    D3D11DeviceContextX()
    {
        if (this->m_RefCount != 0)
            this->m_RefCount = 0;
        m_pFunction = g_Context;
        InterlockedIncrement(&this->m_RefCount);
        memcpy(&this->m_Function, *(void ***)this, sizeof(this->m_Function));
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
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    std::vector<ID3D11BackgroundContext*> m_BkgContexts;
    std::mutex m_BkgCtxLock;

    //
    // ID3D11DeviceContext
    //
    void CheckDirtyFlags();
    void ExecuteBackgroundContexts();
    void AddBackgroundContext(ID3D11BackgroundContext *pContext);
    void RemoveBackgroundContext(ID3D11BackgroundContext *pContext);
    void UpdateShaderResources(gfx::ID3D11ShaderResourceView<ABI> **ppSRVs);
    void UpdateUnorderedAccessViews(gfx::ID3D11UnorderedAccessView<ABI> **ppUAVs);
    void UpdateConstantBuffers(gfx::ID3D11Buffer<ABI> **ppBuffers);
    void UpdateVertexBuffers(gfx::ID3D11Buffer<ABI> **ppBuffers);
    void UpdateIndexBuffer(gfx::ID3D11Buffer<ABI> *pBuffers);
    void ExecuteDrawBundles(gfx::ID3D11CommandList<ABI> *pCommandList);
    void VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void PSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void PSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader);
    void PSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader);
    void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
    void DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation);
    void Draw(UINT VertexCount, UINT StartVertexLocation);
    HRESULT Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags,
                D3D11_MAPPED_SUBRESOURCE *pMappedResource);
    void Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource);
    void PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void IASetInputLayout(gfx::ID3D11InputLayout<ABI> *pInputLayout);
    void IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers,
                            UINT const *pStrides, UINT const *pOffsets);
    void IASetIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT Offset);
    void IASetIndexBuffer(gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT hardwareIndexFormat, UINT Offset);
    void DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation,
                              INT BaseVertexLocation, UINT StartInstanceLocation);
    void DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance,
                              UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount);
    void DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation,
                       UINT StartInstanceLocation);
    void DrawInstanced(UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation,
                       UINT InstanceCount);
    void GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader);
    void IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology);
    void VSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void VSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void VSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void Begin(ID3D11Asynchronous *pAsync);
    void End(ID3D11Asynchronous *pAsync);
    HRESULT GetData(ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags);
    void SetPredication(ID3D11Predicate *pPredicate, BOOL PredicateValue);
    void GSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void GSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void GSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *,
                            gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView);
    void OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs,
                                                   gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews,
                                                   gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView,
                                                   UINT UAVStartSlot, UINT NumUAVs,
                                                   gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
                                                   UINT const *pUAVInitialCounts);
    void OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4], UINT SampleMask);
    void OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef);
    void SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets);
    void DrawAuto();
    void DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
    void DrawInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
    void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);
    void DispatchIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
    void RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState);
    void RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports);
    void RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects);
    void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY,
                               UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                               D3D11_BOX const *pSrcBox);
    void CopyResource(gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource);
    void UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox,
                           void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
    void CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                            gfx::ID3D11UnorderedAccessView<ABI> *pSrcView);
    void ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, FLOAT const ColorRGBA[4]);
    void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, UINT const Values[4]);
    void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                       FLOAT const Values[4]);
    void ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags, FLOAT Depth,
                               UINT8 Stencil);
    void GenerateMips(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void SetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD);
    FLOAT GetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource);
    void ResolveSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                            gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format);
    void ExecuteCommandList(gfx::ID3D11CommandList<ABI> *pCommandList, BOOL RestoreContextState);
    void HSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void HSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader);
    void HSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void DSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void DSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader);
    void DSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void CSSetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
    void CSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
    void CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs,
                                   gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
                                   UINT const *pUAVInitialCounts);
    void CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader);
    void CSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
    void CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
    void VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void PSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void PSGetShader(gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void VSGetShader(gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void IAGetInputLayout(gfx::ID3D11InputLayout<ABI> **ppInputLayout);
    void IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers, UINT *pStrides,
                            UINT *pOffsets);
    void IAGetIndexBuffer(gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset);
    void GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void GSGetShader(gfx::ID3D11GeometryShader<ABI> **ppGeometryShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY *pTopology);
    void VSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void GetPredication(ID3D11Predicate **ppPredicate, BOOL *pPredicateValue);
    void GSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                            gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView);
    void OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                                   gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView,
                                                   UINT UAVStartSlot, UINT NumUAVs,
                                                   gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
    void OMGetBlendState(gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4], UINT *pSampleMask);
    void OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState, UINT *pStencilRef);
    void SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets);
    void RSGetState(gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
    void RSGetViewports(UINT *pNumViewports, D3D11_VIEWPORT *pViewports);
    void RSGetScissorRects(UINT *pNumRects, D3D11_RECT *pRects);
    void HSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void HSGetShader(gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void DSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void DSGetShader(gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void CSGetShaderResources(UINT StartSlot, UINT NumViews,
                              gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
    void CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs,
                                   gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
    void CSGetShader(gfx::ID3D11ComputeShader<ABI> **ppComputeShader, ID3D11ClassInstance **ppClassInstances,
                     UINT *pNumClassInstances);
    void CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
    void CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
    void ClearState();
    void Flush();
    D3D11_DEVICE_CONTEXT_TYPE GetType();
    UINT GetContextFlags();
    HRESULT FinishCommandList(BOOL RestoreDeferredContextState, gfx::ID3D11CommandList<ABI> **ppCommandList);

    //
    // ID3D11DeviceContext1
    //
    void CopySubresourceRegion1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY,
                                UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                D3D11_BOX const *pSrcBox, UINT CopyFlags);
    void UpdateSubresource1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox,
                            void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags);
    void DiscardResource(gfx::ID3D11Resource<ABI> *pResource);
    void DiscardView(gfx::ID3D11View<ABI> *pResourceView);
    void VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                               UINT const *pFirstConstant, UINT const *pNumConstants);
    void VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers,
                               UINT *pFirstConstant, UINT *pNumConstants);
    void SwapDeviceContextState(ID3DDeviceContextState *pState, ID3DDeviceContextState **ppPreviousState);
    void ClearView(gfx::ID3D11View<ABI> *pView, FLOAT const Color[4], D3D11_RECT const *pRect, UINT NumRects);
    void DiscardView1(gfx::ID3D11View<ABI> *pResourceView, D3D11_RECT const *pRects, UINT NumRects);

    //
    // ID3D11DeviceContext2
    //
    HRESULT UpdateTileMappings(gfx::ID3D11Resource<ABI> *pTiledResource, UINT NumTiledResourceRegions,
                               D3D11_TILED_RESOURCE_COORDINATE const *pTiledResourceRegionStartCoordinates,
                               D3D11_TILE_REGION_SIZE const *pTiledResourceRegionSizes,
                               gfx::ID3D11Buffer<ABI> *pTilePool, UINT NumRanges, UINT const *pRangeFlags,
                               UINT const *pTilePoolStartOffsets, UINT const *pRangeTileCounts, UINT Flags);
    HRESULT CopyTileMappings(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                             D3D11_TILED_RESOURCE_COORDINATE const *pDestRegionStartCoordinate,
                             gfx::ID3D11Resource<ABI> *pSourceTiledResource,
                             D3D11_TILED_RESOURCE_COORDINATE const *pSourceRegionStartCoordinate,
                             D3D11_TILE_REGION_SIZE const *pTileRegionSize, UINT Flags);
    void CopyTiles(gfx::ID3D11Resource<ABI> *pTiledResource,
                   D3D11_TILED_RESOURCE_COORDINATE const *pTileRegionStartCoordinate,
                   D3D11_TILE_REGION_SIZE const *pTileRegionSize, gfx::ID3D11Buffer<ABI> *pBuffer,
                   UINT64 BufferStartOffsetInBytes, UINT Flags);
    void UpdateTiles(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                     D3D11_TILED_RESOURCE_COORDINATE const *pDestTileRegionStartCoordinate,
                     D3D11_TILE_REGION_SIZE const *pDestTileRegionSize, void const *pSourceTileData, UINT Flags);
    HRESULT ResizeTilePool(gfx::ID3D11Buffer<ABI> *pTilePool, UINT64 NewSizeInBytes);
    void TiledResourceBarrier(gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessBeforeBarrier,
                              gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessAfterBarrier);

    //
    // ID3D11DeviceContextX
    //
    INT PIXBeginEvent(LPCWSTR Name);
    INT PIXBeginEventEx(const void *pEvent, UINT Flags);
    INT PIXEndEvent();
    void PIXSetMarker(LPCWSTR Name);
    void PIXSetMarkerEx(const void *pMarker, UINT Flags);
    BOOL PIXGetStatus();
    HRESULT PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName);
    HRESULT PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName);
    HRESULT PIXGpuEndCapture();
    void StartCounters(gfx::ID3D11CounterSetX *pCounterSet);
    void SampleCounters(gfx::ID3D11CounterSampleX *pCounterSample);
    void StopCounters();
    HRESULT GetCounterData(gfx::ID3D11CounterSampleX *pCounterSample, gfx::D3D11X_COUNTER_DATA *pData,
                           UINT GetCounterDataFlags);
    void FlushGpuCaches(gfx::ID3D11Resource<ABI> *pResource);
    void FlushGpuCacheRange(UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes);
    void InsertWaitUntilIdle(UINT Flags);
    UINT64 InsertFence(UINT Flags);
    void InsertWaitOnFence(UINT Flags, UINT64 Fence);
    void RemapConstantBufferInheritance(gfx::D3D11_STAGE Stage, UINT Slot, gfx::D3D11_STAGE InheritStage,
                                        UINT InheritSlot);
    void RemapShaderResourceInheritance(gfx::D3D11_STAGE Stage, UINT Slot, gfx::D3D11_STAGE InheritStage,
                                        UINT InheritSlot);
    void RemapSamplerInheritance(gfx::D3D11_STAGE Stage, UINT Slot, gfx::D3D11_STAGE InheritStage, UINT InheritSlot);
    void RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot);
    void PSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void PSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void PSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void VSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void VSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void VSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void GSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void GSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void GSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void CSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void CSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void CSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void HSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void HSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void HSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void DSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
    void DSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
    void DSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
    void IASetFastVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride);
    void IASetFastIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer);
    void PSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void PSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void VSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void VSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void GSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void GSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void CSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void CSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void HSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void HSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void DSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
    void DSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                      void *pBaseAddress);
    void IASetPlacementVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, void *pBaseAddress, UINT Stride);
    void IASetPlacementIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, void *pBaseAddress);
    void HSSetTessellationParameters(gfx::D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters);
    void HSGetLastUsedTessellationParameters(gfx::D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters);
    void CSEnableAutomaticGpuFlush(BOOL Enable);
    void GpuSendPipelinedEvent(gfx::D3D11X_GPU_PIPELINED_EVENT Event);
    HRESULT Suspend(UINT Flags);
    HRESULT Resume();
    void BeginCommandListExecution(UINT Flags);
    void EndCommandListExecution();
    void SetGraphicsShaderLimits(gfx::D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits);
    void SetComputeShaderLimits(gfx::D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits);
    void SetPredicationBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags);
    void OMSetDepthBounds(FLOAT min, FLOAT max);
    void OMSetDepthStencilStateX(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState);
    void OMSetSampleMask(UINT64 QuadSampleMask);
    UINT32 *MakeCeSpace();
    void SetFastResources_Debug(UINT *pTableStart, UINT *pTableEnd);
    void BeginResourceBatch(void *pBuffer, UINT BufferSize);
    UINT EndResourceBatch(UINT *pSizeNeeded);
    void SetFastResourcesFromBatch_Debug(void *pBatch, UINT Size);
    void CSPlaceUnorderedAccessView(UINT Slot, gfx::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *const pDescriptor,
                                    UINT64 Offset);
    void WriteValueEndOfPipe(void *pDestination, UINT Value, UINT Flags);
    void CopyMemoryToMemory(void *pDstAddress, void *pSrcAddress, SIZE_T SizeBytes);
    void FillMemoryWithValue(void *pDstAddress, SIZE_T SizeBytes, UINT FillValue);
    void BeginProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource);
    void EndProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource);
    HRESULT StartThreadTrace(gfx::D3D11X_THREAD_TRACE_DESC const *pDesc, void *pDstAddressShaderEngine0,
                             void *pDstAddressShaderEngine1, SIZE_T BufferSizeBytes);
    void StopThreadTrace(void *pDstAddressTraceSize);
    void InsertThreadTraceMarker(UINT Marker);
    void IASetPrimitiveResetIndex(UINT ResetIndex);
    void SetShaderResourceViewMinLOD(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, FLOAT MinLOD);
    void InsertWaitOnPresent(UINT Flags, gfx::ID3D11Resource<ABI> *pBackBuffer);
    void ClearRenderTargetViewX(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, UINT Flags,
                                FLOAT const ColorRGBA[4]);
    UINT GetResourceCompression(gfx::ID3D11Resource<ABI> *pResource);
    UINT GetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource);
    void DecompressResource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                            gfx::D3D11X_POINT const *pDstPoint, gfx::ID3D11Resource<ABI> *pSrcResource,
                            UINT SrcSubresource, gfx::D3D11X_RECT const *pSrcRect,
                            DXGI_FORMAT DecompressFormat, UINT DecompressFlags);
    void DecompressResourceX(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDstResource, UINT DstSubresource,
                             gfx::D3D11X_POINT const *pDstPoint, gfx::D3D11X_DESCRIPTOR_RESOURCE *pSrcResource,
                             UINT SrcSubresource, gfx::D3D11X_RECT const *pSrcRect, gfx::D3D11X_FORMAT DecompressFormat,
                             UINT DecompressFlags);
    void GSSetParameters(gfx::D3D11X_GS_PARAMETERS const *pGsParameters);
    void GSGetLastUsedParameters(gfx::D3D11X_GS_PARAMETERS *pGsParameters);
    void MultiDrawIndexedInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                           UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
    void MultiDrawInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                    UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
    void MultiDrawIndexedInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                               UINT AlignedByteOffsetForPrimitiveCount,
                                               gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs,
                                               UINT StrideByteOffsetForArgs, UINT Flags);
    void MultiDrawInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                        UINT AlignedByteOffsetForPrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                        UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
    HRESULT RSGetMSAASettingsForQuality(gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS *pMSAASCSettings,
                                        gfx::D3D11X_MSAA_EQAA_SETTINGS *pEQAASettings,
                                        gfx::D3D11X_MSAA_SAMPLE_PRIORITIES *pCentroidPriorities,
                                        gfx::D3D11X_MSAA_SAMPLE_POSITIONS *pSamplePositions, UINT LogSampleCount,
                                        UINT SampleQuality);
    void RSSetScanConverterMSAASettings(gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS const *pMSAASCSettings);
    void RSSetEQAASettings(gfx::D3D11X_MSAA_EQAA_SETTINGS const *pEQAASettings);
    void RSSetSamplePositions(gfx::D3D11X_MSAA_SAMPLE_PRIORITIES const *pSamplesPriorities,
                              gfx::D3D11X_MSAA_SAMPLE_POSITIONS const *pSamplePositions);
    void SetResourceCompression(gfx::ID3D11Resource<ABI> *pResource, UINT Compression);
    void SetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource, UINT Compression);
    void SetGDSRange(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords);
    void WriteGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT const *pCounterValues,
                  UINT Flags);
    void ReadGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT *pCounterValues,
                 UINT Flags);
    void VSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void HSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void DSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void GSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void PSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void CSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void InsertWaitOnMemory(void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction,
                            UINT ReferenceValue, UINT Mask);
    void WriteTimestampToMemory(void *pDstAddress);
    void WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetBytes);
    void StoreConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes,
                          UINT CeRamOffsetInBytes, UINT SizeInBytes);
    void LoadConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes, UINT CeRamOffsetInBytes,
                         UINT SizeInBytes);
    void WriteQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer,
                    UINT OffsetInBytes, UINT StrideInBytes);
    void ResetQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags);
    void ConfigureQuery(D3D11_QUERY QueryType, void const *pConfiguration, UINT ConfigurationSize);
    void SetShaderUserData(gfx::D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters, UINT const *pData);
    void SetPixelShaderDepthForceZOrder(BOOL ForceOrder);
    void SetPredicationFromQuery(D3D11_QUERY QueryType, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes,
                                 UINT Flags);
    void SetBorderColorPalette(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags);
    void WriteValueEndOfPipe64(void *pDestination, UINT64 Value, UINT Flags);
    void InsertWaitOnMemory64(void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction,
                              UINT64 ReferenceValue);
    void LoadConstantRamImmediate(UINT Flags, void const *pBuffer, UINT CeRamOffsetInBytes, UINT SizeInBytes);
    void SetScreenExtentsQuery(UINT Value);
    void CollectScreenExtents(UINT Flags, UINT AddressCount, UINT64 const *pDestinationAddresses, USHORT ZMin,
                              USHORT ZMax);
    void FillResourceWithValue(gfx::ID3D11Resource<ABI> *pDstResource, UINT FillValue);
    void SetDrawBalancing(UINT BalancingMode, UINT Flags);
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DeviceContextX<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);