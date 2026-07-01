#include "ID3D11DrawBundlesContext.h"
#include "ID3D11Device.h"
#include "ID3D11View.h"
#include "ID3D11Resource.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11DeviceContext>() || riid == xcom::guid_of<gfx::ID3D11DeviceContext1>() ||
        riid == xcom::guid_of<gfx::ID3D11DeviceContext2>() || riid == xcom::guid_of<gfx::ID3D11DeviceContextX>() ||
        riid == xcom::guid_of<gfx::ID3D11PerformanceContextX>() || riid == xcom::guid_of<gfx::ID3D11UserDefinedAnnotationX>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    if (riid == xcom::guid_of<xbox::IGraphicsUnwrap>())
    {
        *ppvObject = m_pFunction;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11DrawBundlesContext<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11DrawBundlesContext<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        for (auto& command : m_CommandQueue)
        {
            if (command.m_CommandType == DrawBundlesCommandType::IASetVertexBuffers)
            {
                if (command.IASetVertexBuffers.ppVertexBuffers)
                {
                    delete[] command.IASetVertexBuffers.ppVertexBuffers;
                    command.IASetVertexBuffers.ppVertexBuffers = nullptr;
                }
                if (command.IASetVertexBuffers.pStrides)
                {
                    delete[] command.IASetVertexBuffers.pStrides;
                    command.IASetVertexBuffers.pStrides = nullptr;
                }
                if (command.IASetVertexBuffers.pOffsets)
                {
                    delete[] command.IASetVertexBuffers.pOffsets;
                    command.IASetVertexBuffers.pOffsets = nullptr;
                }
            }
            else if (command.m_CommandType == DrawBundlesCommandType::VSSetShaderResourcesPC)
            {
                if (command.VSSetShaderResourcesPC.ppShaderResourceViews)
                {
                    delete[] command.VSSetShaderResourcesPC.ppShaderResourceViews;
                    command.VSSetShaderResourcesPC.ppShaderResourceViews = nullptr;
                }
            }
            else if (command.m_CommandType == DrawBundlesCommandType::PSSetShaderResourcesPC)
            {
                if (command.PSSetShaderResourcesPC.ppShaderResourceViews)
                {
                    delete[] command.PSSetShaderResourcesPC.ppShaderResourceViews;
                    command.PSSetShaderResourcesPC.ppShaderResourceViews = nullptr;
                }
            }
        }

        m_CommandQueue.clear();
        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GetDevice(gfx::ID3D11Device<ABI>** ppDevice)
{
    if (ppDevice)
    {
        ID3D11Device* dev{};
        ID3D11Device2* dev2{};
        m_pFunction->GetDevice(&dev);
        dev->QueryInterface(&dev2);
        if (dev2) dev->Release();

        *ppDevice = new D3D11DeviceX<ABI>(dev2);
    }
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                  xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11DeviceContext
//
template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::PSSetShaderResourcesPC;
    Command.PSSetShaderResourcesPC.StartSlot = StartSlot;
    Command.PSSetShaderResourcesPC.NumViews = NumViews;
    auto SRVs = new gfx::ID3D11ShaderResourceView<ABI>*[NumViews];
    memcpy(SRVs, ppShaderResourceViews, NumViews * sizeof(*SRVs));
    Command.PSSetShaderResourcesPC.ppShaderResourceViews = SRVs;
    m_CommandQueue.push_back(Command);
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::PSSetShader;
    Command.PSSetShader.pPixelShader = pPixelShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::VSSetShader;
    Command.VSSetShader.pVertexShader = pVertexShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DrawIndexedPC;
    Command.DrawIndexedPC.IndexCount = IndexCount;
    Command.DrawIndexedPC.StartIndexLocation = StartIndexLocation;
    Command.DrawIndexedPC.BaseVertexLocation = BaseVertexLocation;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DrawIndexedXbox;
    Command.DrawIndexedXbox.StartIndexLocationAndIndexCount = StartIndexLocationAndIndexCount;
    Command.DrawIndexedXbox.BaseVertexLocation = BaseVertexLocation;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::Draw(UINT VertexCount, UINT StartVertexLocation)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::Draw;
    Command.Draw.VertexCount = VertexCount;
    Command.Draw.StartVertexLocation = StartVertexLocation;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType,
                                      UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource)
{
    IMPLEMENT_STUB();
    return S_OK;
}

template <abi_t ABI> 
void D3D11DrawBundlesContext<ABI>::Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::IASetInputLayout(gfx::ID3D11InputLayout<ABI> *pInputLayout)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::IASetInputLayout;
    Command.IASetInputLayout.pInputLayout = pInputLayout;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers,
                                                  gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides,
                                                  UINT const *pOffsets)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::IASetVertexBuffers;
    Command.IASetVertexBuffers.StartSlot = StartSlot;
    Command.IASetVertexBuffers.NumBuffers = NumBuffers;

    auto VertexBuffers = new gfx::ID3D11Buffer<ABI>*[NumBuffers];
    memcpy(VertexBuffers, ppVertexBuffers, NumBuffers * sizeof(*VertexBuffers));
    Command.IASetVertexBuffers.ppVertexBuffers = VertexBuffers;

    auto Strides = new UINT[NumBuffers];
    memcpy(Strides, pStrides, NumBuffers * sizeof(*Strides));
    Command.IASetVertexBuffers.pStrides = Strides;

    auto Offsets = new UINT[NumBuffers];
    memcpy(Offsets, pOffsets, NumBuffers * sizeof(*Offsets));
    Command.IASetVertexBuffers.pOffsets = Offsets;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetIndexBuffer(gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat,
                                                UINT Offset)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::IASetIndexBufferPC;
    Command.IASetIndexBufferPC.pIndexBuffer = pIndexBuffer;
    Command.IASetIndexBufferPC.HardwareIndexFormat = HardwareIndexFormat;
    Command.IASetIndexBufferPC.Offset = Offset;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount,
                                                    UINT StartIndexLocation, INT BaseVertexLocation,
                                                    UINT StartInstanceLocation)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DrawIndexedInstancedPC;
    Command.DrawIndexedInstancedPC.IndexCountPerInstance = IndexCountPerInstance;
    Command.DrawIndexedInstancedPC.InstanceCount = InstanceCount;
    Command.DrawIndexedInstancedPC.StartIndexLocation = StartIndexLocation;
    Command.DrawIndexedInstancedPC.BaseVertexLocation = BaseVertexLocation;
    Command.DrawIndexedInstancedPC.StartInstanceLocation = StartInstanceLocation;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance,
                                                    UINT64 BaseVertexLocationAndStartInstanceLocation,
                                                    UINT InstanceCount)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DrawIndexedInstancedXbox;
    Command.DrawIndexedInstancedXbox.StartIndexLocationAndIndexCountPerInstance = StartIndexLocationAndIndexCountPerInstance;
    Command.DrawIndexedInstancedXbox.BaseVertexLocationAndStartInstanceLocation = BaseVertexLocationAndStartInstanceLocation;
    Command.DrawIndexedInstancedXbox.InstanceCount = InstanceCount;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation,
                                             UINT StartInstanceLocation)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawInstanced(UINT VertexCountPerInstance,
                                             UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer,
                                                UINT Offset)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::IASetIndexBufferXbox;
    Command.IASetIndexBufferXbox.pIndexBuffer = pIndexBuffer;
    Command.IASetIndexBufferXbox.HardwareIndexFormat = HardwareIndexFormat;
    Command.IASetIndexBufferXbox.Offset = Offset;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::GSSetShader;
    Command.GSSetShader.pShader = pShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::IASetPrimitiveTopology;
    Command.IASetPrimitiveTopology.PrimitiveTopology = PrimitiveTopology;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::VSSetShaderResourcesPC;
    Command.VSSetShaderResourcesPC.StartSlot = StartSlot;
    Command.VSSetShaderResourcesPC.NumViews = NumViews;
    auto SRVs = new gfx::ID3D11ShaderResourceView<ABI>*[NumViews];
    memcpy(SRVs, ppShaderResourceViews, NumViews * sizeof(*SRVs));
    Command.VSSetShaderResourcesPC.ppShaderResourceViews = SRVs;
    m_CommandQueue.push_back(Command);
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::Begin(ID3D11Asynchronous* pAsync)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::End(ID3D11Asynchronous* pAsync)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags)
{
    IMPLEMENT_STUB();
    return S_OK;
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
                                                  gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMSetRenderTargetsAndUnorderedAccessViews(
    UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView,
    UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
    UINT const *pUAVInitialCounts)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4],
                                               UINT SampleMask)
{
    IMPLEMENT_STUB();
}
template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState,
                                                      UINT StencilRef)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets,
                                            UINT const *pOffsets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawAuto()
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    DrawBundlesCommand<ABI> Command;
    Command.m_CommandType = DrawBundlesCommandType::DrawIndexedInstancedIndirect;
    Command.DrawIndexedInstancedIndirect.pBufferForArgs = pBufferForArgs;
    Command.DrawIndexedInstancedIndirect.AlignedByteOffsetForArgs = AlignedByteOffsetForArgs;
    m_CommandQueue.push_back(Command);
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DrawInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    DrawBundlesCommand<ABI> Command;
    Command.m_CommandType = DrawBundlesCommandType::DrawInstancedIndirect;
    Command.DrawInstancedIndirect.pBufferForArgs = pBufferForArgs;
    Command.DrawInstancedIndirect.AlignedByteOffsetForArgs = AlignedByteOffsetForArgs;
    m_CommandQueue.push_back(Command);
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DispatchIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                     UINT DstX, UINT DstY, UINT DstZ,
                                                     gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                     D3D11_BOX const *pSrcBox)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopyResource(gfx::ID3D11Resource<ABI> *pDstResource,
                                            gfx::ID3D11Resource<ABI> *pSrcResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                 D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch,
                                                 UINT SrcDepthPitch)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                                                  gfx::ID3D11UnorderedAccessView<ABI> *pSrcView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView,
                                                     FLOAT const ColorRGBA[4])
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                            UINT const Values[4])
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                             FLOAT const Values[4])
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView,
                                                     UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GenerateMips(gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource, FLOAT MinLOD)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
FLOAT D3D11DrawBundlesContext<ABI>::GetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource)
{
    IMPLEMENT_STUB();
    return 0.0f;
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ResolveSubresource(gfx::ID3D11Resource<ABI>* pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI>* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ExecuteCommandList(gfx::ID3D11CommandList<ABI> *pCommandList, BOOL RestoreContextState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::HSSetShader;
    Command.HSSetShader.pHullShader = pHullShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DSSetShader;
    Command.DSSetShader.pDomainShader = pDomainShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetUnorderedAccessViews(
    UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
    UINT const *pUAVInitialCounts)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::CSSetShader;
    Command.CSSetShader.pComputeShader = pComputeShader;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSGetShader(gfx::ID3D11PixelShader<ABI>** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSGetShader(gfx::ID3D11VertexShader<ABI>** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IAGetInputLayout(gfx::ID3D11InputLayout<ABI>** ppInputLayout)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppVertexBuffers, UINT* pStrides, UINT* pOffsets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IAGetIndexBuffer(gfx::ID3D11Buffer<ABI>** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSGetShader(gfx::ID3D11GeometryShader<ABI>** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMGetBlendState(gfx::ID3D11BlendState<ABI>** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI>** ppDepthStencilState, UINT* pStencilRef)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppSOTargets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSGetState(gfx::ID3D11RasterizerState<ABI>** ppRasterizerState)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetShader(gfx::ID3D11HullShader<ABI>** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSGetShader(gfx::ID3D11DomainShader<ABI>** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetShader(gfx::ID3D11ComputeShader<ABI>** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::ClearState()
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::ClearState;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::Flush()
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> D3D11_DEVICE_CONTEXT_TYPE D3D11DrawBundlesContext<ABI>::GetType()
{
    IMPLEMENT_STUB();
    return D3D11_DEVICE_CONTEXT_DEFERRED;
}

template <abi_t ABI> UINT D3D11DrawBundlesContext<ABI>::GetContextFlags()
{
    IMPLEMENT_STUB();
    return 0;
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::FinishCommandList(BOOL RestoreDeferredContextState, gfx::ID3D11CommandList<ABI> **ppCommandList)
{
    *ppCommandList = new D3D11CommandList<ABI>(std::move(m_CommandQueue));
    m_CommandQueue.clear();
    return S_OK;
}

//
// ID3D11DeviceContext1
//
template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopySubresourceRegion1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                      UINT DstX, UINT DstY, UINT DstZ,
                                                      gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                      D3D11_BOX const *pSrcBox, UINT CopyFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::UpdateSubresource1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                  D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch,
                                                  UINT SrcDepthPitch, UINT CopyFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::DiscardResource(gfx::ID3D11Resource<ABI> *pResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::DiscardView(gfx::ID3D11View<ABI> *pResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SwapDeviceContextState(ID3DDeviceContextState *pState,
                                                      ID3DDeviceContextState **ppPreviousState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearView(gfx::ID3D11View<ABI> *pView, FLOAT const Color[4], D3D11_RECT const *pRect,
                                         UINT NumRects)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DiscardView1(gfx::ID3D11View<ABI> *pResourceView, D3D11_RECT const *pRects,
                                            UINT NumRects)
{
    IMPLEMENT_STUB();
}

//
// ID3D11DeviceContext2
//
template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::UpdateTileMappings(
    gfx::ID3D11Resource<ABI> *pTiledResource, UINT NumTiledResourceRegions,
    D3D11_TILED_RESOURCE_COORDINATE const *pTiledResourceRegionStartCoordinates,
    D3D11_TILE_REGION_SIZE const *pTiledResourceRegionSizes, gfx::ID3D11Buffer<ABI> *pTilePool, UINT NumRanges,
    UINT const *pRangeFlags, UINT const *pTilePoolStartOffsets, UINT const *pRangeTileCounts, UINT Flags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::CopyTileMappings(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                                                   D3D11_TILED_RESOURCE_COORDINATE const *pDestRegionStartCoordinate,
                                                   gfx::ID3D11Resource<ABI> *pSourceTiledResource,
                                                   D3D11_TILED_RESOURCE_COORDINATE const *pSourceRegionStartCoordinate,
                                                   D3D11_TILE_REGION_SIZE const *pTileRegionSize, UINT Flags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopyTiles(gfx::ID3D11Resource<ABI> *pTiledResource,
                                         D3D11_TILED_RESOURCE_COORDINATE const *pTileRegionStartCoordinate,
                                         D3D11_TILE_REGION_SIZE const *pTileRegionSize, gfx::ID3D11Buffer<ABI> *pBuffer,
                                         UINT64 BufferStartOffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::UpdateTiles(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                                           D3D11_TILED_RESOURCE_COORDINATE const *pDestTileRegionStartCoordinate,
                                           D3D11_TILE_REGION_SIZE const *pDestTileRegionSize,
                                           void const *pSourceTileData, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::ResizeTilePool(gfx::ID3D11Buffer<ABI> *pTilePool, UINT64 NewSizeInBytes)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::TiledResourceBarrier(
    gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessBeforeBarrier,
    gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessAfterBarrier)
{
    IMPLEMENT_STUB();
}

//
// ID3D11DrawBundlesContext
//
template <abi_t ABI> INT D3D11DrawBundlesContext<ABI>::PIXBeginEvent(LPCWSTR Name)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> INT D3D11DrawBundlesContext<ABI>::PIXEndEvent()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::PIXSetMarker(LPCWSTR Name)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> BOOL D3D11DrawBundlesContext<ABI>::PIXGetStatus()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::PIXGpuEndCapture()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::StartCounters(gfx::ID3D11CounterSetX *pCounterSet)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SampleCounters(gfx::ID3D11CounterSampleX *pCounterSample)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::StopCounters()
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::GetCounterData(gfx::ID3D11CounterSampleX *pCounterSample,
                                                 gfx::D3D11X_COUNTER_DATA *pData,
                                                 UINT GetCounterDataFlags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::FlushGpuCaches(gfx::ID3D11Resource<ABI> *pResource)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::FlushGpuCacheRange(UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes)
{

}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::InsertWaitUntilIdle(UINT Flags)
{

}

template <abi_t ABI> UINT64 D3D11DrawBundlesContext<ABI>::InsertFence(UINT Flags)
{
    IMPLEMENT_STUB();
    return 0;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::InsertWaitOnFence(UINT Flags, UINT64 Fence)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RemapConstantBufferInheritance(gfx::D3D11_STAGE Stage, UINT Slot,
                                                              gfx::D3D11_STAGE InheritStage,
                                                              UINT InheritSlot)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::RemapConstantBufferInheritance;
    Command.RemapConstantBufferInheritance.Stage = Stage;
    Command.RemapConstantBufferInheritance.Slot = Slot;
    Command.RemapConstantBufferInheritance.InheritStage = InheritStage;
    Command.RemapConstantBufferInheritance.InheritSlot = InheritSlot;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RemapShaderResourceInheritance(gfx::D3D11_STAGE Stage, UINT Slot,
                                                              gfx::D3D11_STAGE InheritStage,
                                                              UINT InheritSlot)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::RemapShaderResourceInheritance;
    Command.RemapShaderResourceInheritance.Stage = Stage;
    Command.RemapShaderResourceInheritance.Slot = Slot;
    Command.RemapShaderResourceInheritance.InheritStage = InheritStage;
    Command.RemapShaderResourceInheritance.InheritSlot = InheritSlot;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RemapSamplerInheritance(gfx::D3D11_STAGE Stage, UINT Slot, gfx::D3D11_STAGE InheritStage,
                                                       UINT InheritSlot)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::PSSetFastConstantBuffer;
    Command.PSSetFastConstantBuffer.Slot = Slot;
    Command.PSSetFastConstantBuffer.pConstantBuffer = pConstantBuffer;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::PSSetFastShaderResource;
    Command.PSSetFastShaderResource.Slot = Slot;
    Command.PSSetFastShaderResource.pShaderResourceView = pShaderResourceView;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::PSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::PSSetFastSampler;
    Command.PSSetFastSampler.Slot = Slot;
    Command.PSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::VSSetFastConstantBuffer;
    Command.VSSetFastConstantBuffer.Slot = Slot;
    Command.VSSetFastConstantBuffer.pConstantBuffer = pConstantBuffer;
    m_CommandQueue.push_back(Command);
};

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::VSSetFastShaderResource;
    Command.VSSetFastShaderResource.Slot = Slot;
    Command.VSSetFastShaderResource.pShaderResourceView = pShaderResourceView;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::VSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::VSSetFastSampler;
    Command.VSSetFastSampler.Slot = Slot;
    Command.VSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::GSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::GSSetFastSampler;
    Command.GSSetFastSampler.Slot = Slot;
    Command.GSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::CSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::CSSetFastSampler;
    Command.CSSetFastSampler.Slot = Slot;
    Command.CSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::HSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::HSSetFastSampler;
    Command.HSSetFastSampler.Slot = Slot;
    Command.HSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::DSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DrawBundlesCommand<ABI> Command{};
    Command.m_CommandType = DrawBundlesCommandType::DSSetFastSampler;
    Command.DSSetFastSampler.Slot = Slot;
    Command.DSSetFastSampler.pSampler = pSampler;
    m_CommandQueue.push_back(Command);
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetFastVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetFastIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetPlacementVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer,
                                                          void *pBaseAddress, UINT Stride)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::IASetPlacementIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer,
                                                         void *pBaseAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetTessellationParameters(
    gfx::D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSGetLastUsedTessellationParameters(
    gfx::D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::CSEnableAutomaticGpuFlush(BOOL Enable)
{

}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::GpuSendPipelinedEvent(gfx::D3D11X_GPU_PIPELINED_EVENT Event)
{

}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::Suspend(UINT Flags)
{
    return S_OK;
}

template <abi_t ABI> HRESULT D3D11DrawBundlesContext<ABI>::Resume()
{
    return S_OK;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::BeginCommandListExecution(UINT Flags)
{

}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::EndCommandListExecution()
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetGraphicsShaderLimits(gfx::D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetComputeShaderLimits(gfx::D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetPredicationBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::OMSetDepthBounds(FLOAT min, FLOAT max)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::OMSetDepthStencilStateX(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::OMSetSampleMask(UINT64 QuadSampleMask)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> UINT32 *D3D11DrawBundlesContext<ABI>::MakeCeSpace()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SetFastResources_Debug(UINT *pTableStart, UINT *pTableEnd)
{
    UINT v10 = 0;
    UINT v11 = 0;
    UINT v12 = 0;
    UINT v14 = 0;
    UINT v16 = 0;
    UINT v17 = 0;
    UINT64 v23 = 0;
    UINT64 v26 = 0;
    int v27 = 0;
    int v51 = 0;
    UINT64 BaseAddress = 0;
    UINT64 BaseAddress2 = 0;
    UINT64 *ResourcePtr{};
    UINT v13 = 0;
    UINT Slot = 0;
    UINT64 Stride = 0;
    UINT D3D11X_SET_FAST_VALUE = 0;
    gfx::ID3D11ShaderResourceView<ABI> *SRV{};
    gfx::ID3D11Buffer<ABI> *Buffer{};
    gfx::ID3D11SamplerState<ABI> *Sampler{};

    for (bool i = pTableStart < pTableEnd; i; i = pTableStart < pTableEnd)
    {
        v10 = *pTableStart++;
        v11 = (*((WORD *)&(v10) + 0)) & 0x7FF;
        v12 = (UINT8)v10;
        v16 = (v10 >> 28) & 7;
        v13 = v10 >> 8;
        Slot = (UINT8)v13;
        v14 = (v10 >> 27) & 1;
        v17 = v10 >> 31;
        D3D11X_SET_FAST_VALUE = ((BYTE *)&v10)[2] & 0xF;

        if (v12)
        {
            while (1)
            {
                v23 = *((UINT64 *)pTableStart + 1);
                ResourcePtr = *(UINT64 **)pTableStart;
                pTableStart += 4;
                Stride = (v23 >> 48) & 0xFFFF;
                UINT64 Offset = v23 & 0x0000FFFFFFFFFFFF;
                v26 = v23 - ((UINT64)(UINT)Stride << 48);

                if (ResourcePtr)
                {
                    if (!v16)
                    {
                        v27 = v11 & 0x100;
                        if (v17 == 1)
                        {
                            if (!v14)
                            {
                                if ((v11 & 0x40) != 0)
                                {
                                    break;
                                }
                                BaseAddress = Offset;
                                if (v27)
                                {
                                    switch (D3D11X_SET_FAST_VALUE)
                                    {
                                    case 0:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        VSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    case 1:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        HSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    case 2:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        DSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    case 3:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        GSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    case 4:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        PSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    case 5:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        CSSetPlacementShaderResource(Slot, SRV, (void *)BaseAddress);
                                        break;
                                    }
                                }
                                else
                                {
                                    switch (D3D11X_SET_FAST_VALUE)
                                    {
                                    case 0:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        VSSetFastShaderResource(Slot, SRV);
                                        break;
                                    case 1:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        HSSetFastShaderResource(Slot, SRV);
                                        break;
                                    case 2:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        DSSetFastShaderResource(Slot, SRV);
                                        break;
                                    case 3:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        GSSetFastShaderResource(Slot, SRV);
                                        break;
                                    case 4:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        PSSetFastShaderResource(Slot, SRV);
                                        break;
                                    case 5:
                                        SRV = reinterpret_cast<gfx::ID3D11ShaderResourceView<ABI> *>(ResourcePtr);
                                        CSSetFastShaderResource(Slot, SRV);
                                        break;
                                    }
                                }
                            }
                        }

                        return;
                    }
                    if (v16 == 1)
                    {
                        if (v17 == 1)
                        {
                            v51 = v11 & 0x100;

                            BaseAddress2 = Offset;
                            if (v51)
                            {
                                if (D3D11X_SET_FAST_VALUE)
                                {
                                    switch (D3D11X_SET_FAST_VALUE)
                                    {
                                    case 1:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        HSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                        break;
                                    case 2:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        DSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                        break;
                                    case 3:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        GSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                        break;
                                    case 4:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        PSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                        break;
                                    case 5:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        CSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                        break;
                                    case 6:
                                        Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                        IASetPlacementVertexBuffer(Slot, Buffer, (void *)BaseAddress2, Stride);
                                        break;
                                    }
                                }
                                else
                                {
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    VSSetPlacementConstantBuffer(Slot, Buffer, (void *)BaseAddress2);
                                }
                            }
                            else if (D3D11X_SET_FAST_VALUE)
                            {
                                switch (D3D11X_SET_FAST_VALUE)
                                {
                                case 1:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    HSSetFastConstantBuffer(Slot, Buffer);
                                    break;
                                case 2:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    DSSetFastConstantBuffer(Slot, Buffer);
                                    break;
                                case 3:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    GSSetFastConstantBuffer(Slot, Buffer);
                                    break;
                                case 4:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    PSSetFastConstantBuffer(Slot, Buffer);
                                    break;
                                case 5:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    CSSetFastConstantBuffer(Slot, Buffer);
                                    break;
                                case 6:
                                    Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                    IASetFastVertexBuffer(Slot, Buffer, Stride);
                                    break;
                                }
                            }
                            else
                            {
                                Buffer = reinterpret_cast<gfx::ID3D11Buffer<ABI> *>(ResourcePtr);
                                VSSetFastConstantBuffer(Slot, Buffer);
                            }
                        }

                        return;
                    }
                    if (v17 == 1)
                    {
                        if (D3D11X_SET_FAST_VALUE)
                        {
                            switch (D3D11X_SET_FAST_VALUE)
                            {
                            case 1:
                                Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                                HSSetFastSampler(Slot, Sampler);
                                break;
                            case 2:
                                Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                                DSSetFastSampler(Slot, Sampler);
                                break;
                            case 3:
                                Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                                GSSetFastSampler(Slot, Sampler);
                                break;
                            case 4:
                                Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                                PSSetFastSampler(Slot, Sampler);
                                break;
                            case 5:
                                Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                                CSSetFastSampler(Slot, Sampler);
                                break;
                            }
                        }
                        else
                        {
                            Sampler = reinterpret_cast<gfx::ID3D11SamplerState<ABI> *>(ResourcePtr);
                            VSSetFastSampler(Slot, Sampler);
                        }

                        return;
                    }
                }

                return;
            }
        }
    }
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::BeginResourceBatch(void *pBuffer, UINT BufferSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> UINT D3D11DrawBundlesContext<ABI>::EndResourceBatch(UINT *pSizeNeeded)
{
    return 0;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SetFastResourcesFromBatch_Debug(void *pBatch, UINT Size)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSPlaceUnorderedAccessView(UINT Slot, gfx::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *const pDescriptor,
                                                          UINT64 Offset)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::WriteValueEndOfPipe(void* pDestination, UINT Value, UINT Flags)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CopyMemoryToMemory(void* pDstAddress, void* pSrcAddress, SIZE_T SizeBytes)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::FillMemoryWithValue(void* pDstAddress, SIZE_T SizeBytes, UINT FillValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::BeginProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::EndProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::StartThreadTrace(gfx::D3D11X_THREAD_TRACE_DESC const *pDesc,
                                                   void *pDstAddressShaderEngine0, void *pDstAddressShaderEngine1,
                                                   SIZE_T BufferSizeBytes)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::StopThreadTrace(void *pDstAddressTraceSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::InsertThreadTraceMarker(UINT Marker)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::IASetPrimitiveResetIndex(UINT ResetIndex)
{

}

template<abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetShaderResourceViewMinLOD(gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView, FLOAT MinLOD)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::InsertWaitOnPresent(UINT Flags, gfx::ID3D11Resource<ABI> *pBackBuffer)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ClearRenderTargetViewX(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, UINT Flags,
                                                      FLOAT const ColorRGBA[4])
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> UINT D3D11DrawBundlesContext<ABI>::GetResourceCompression(gfx::ID3D11Resource<ABI> *pResource)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
UINT D3D11DrawBundlesContext<ABI>::GetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DecompressResource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                  gfx::D3D11X_POINT const *pDstPoint,
                                                  gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                  gfx::D3D11X_RECT const *pSrcRect,
                                                  DXGI_FORMAT DecompressFormat, UINT DecompressFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DecompressResourceX(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDstResource, UINT DstSubresource,
                                                   gfx::D3D11X_POINT const *pDstPoint,
                                                   gfx::D3D11X_DESCRIPTOR_RESOURCE *pSrcResource, UINT SrcSubresource,
                                                   gfx::D3D11X_RECT const *pSrcRect,
                                                   gfx::D3D11X_FORMAT DecompressFormat,
                                                   UINT DecompressFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::GSSetParameters(gfx::D3D11X_GS_PARAMETERS const *pGsParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::GSGetLastUsedParameters(gfx::D3D11X_GS_PARAMETERS *pGsParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::MultiDrawIndexedInstancedIndirect(UINT PrimitiveCount,
                                                                 gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                                 UINT AlignedByteOffsetForArgs,
                                                                 UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::MultiDrawInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                          UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs,
                                                          UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::MultiDrawIndexedInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                                                     UINT AlignedByteOffsetForPrimitiveCount,
                                                                     gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                                     UINT AlignedByteOffsetForArgs,
                                                                     UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::MultiDrawInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                                              UINT AlignedByteOffsetForPrimitiveCount,
                                                              gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                              UINT AlignedByteOffsetForArgs,
                                                              UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DrawBundlesContext<ABI>::RSGetMSAASettingsForQuality(gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS *pMSAASCSettings,
                                                              gfx::D3D11X_MSAA_EQAA_SETTINGS *pEQAASettings,
                                                              gfx::D3D11X_MSAA_SAMPLE_PRIORITIES *pCentroidPriorities,
                                                              gfx::D3D11X_MSAA_SAMPLE_POSITIONS *pSamplePositions,
                                                              UINT LogSampleCount, UINT SampleQuality)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSSetScanConverterMSAASettings(
    gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS const *pMSAASCSettings)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSSetEQAASettings(gfx::D3D11X_MSAA_EQAA_SETTINGS const *pEQAASettings)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::RSSetSamplePositions(gfx::D3D11X_MSAA_SAMPLE_PRIORITIES const *pSamplesPriorities,
                                                    gfx::D3D11X_MSAA_SAMPLE_POSITIONS const *pSamplePositions)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetResourceCompression(gfx::ID3D11Resource<ABI> *pResource, UINT Compression)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource,
                                                       UINT Compression)
{

}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetGDSRange(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::WriteGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
                                        UINT const *pCounterValues, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ReadGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
                                       UINT *pCounterValues, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::VSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::HSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::DSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::GSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::PSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::InsertWaitOnMemory(void const *pAddress, UINT Flags,
                                                  D3D11_COMPARISON_FUNC ComparisonFunction, UINT ReferenceValue,
                                                  UINT Mask)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::WriteTimestampToMemory(void *pDstAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::StoreConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes,
                                                UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::LoadConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes,
                                               UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::WriteQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags,
                                          gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT StrideInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::ResetQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::ConfigureQuery(D3D11_QUERY QueryType, void const *pConfiguration, UINT ConfigurationSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetShaderUserData(gfx::D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters,
                                                 UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SetPixelShaderDepthForceZOrder(BOOL ForceOrder)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetPredicationFromQuery(D3D11_QUERY QueryType, gfx::ID3D11Buffer<ABI> *pBuffer,
                                                       UINT OffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::SetBorderColorPalette(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::WriteValueEndOfPipe64(void *pDestination, UINT64 Value, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::InsertWaitOnMemory64(void const *pAddress, UINT Flags,
                                                    D3D11_COMPARISON_FUNC ComparisonFunction, UINT64 ReferenceValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::LoadConstantRamImmediate(UINT Flags, void const *pBuffer, UINT CeRamOffsetInBytes,
                                                        UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SetScreenExtentsQuery(UINT Value)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::CollectScreenExtents(UINT Flags, UINT AddressCount, UINT64 const *pDestinationAddresses,
                                                    USHORT ZMin, USHORT ZMax)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DrawBundlesContext<ABI>::FillResourceWithValue(gfx::ID3D11Resource<ABI> *pDstResource, UINT FillValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DrawBundlesContext<ABI>::SetDrawBalancing(UINT BalancingMode, UINT Flags)
{
    IMPLEMENT_STUB();
}


#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DrawBundlesContext<ABI>
D3D11_DECLARE_ABI_TEMPLATES();