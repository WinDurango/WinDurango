#pragma once
#include "d3d11_x.g.h"
#include <vector>
#include <utility>

enum class DrawBundlesCommandType
{
    DSSetShader,
    HSSetShader,
    GSSetShader,
    VSSetShader,
    PSSetShader,
    CSSetShader,
    VSSetFastConstantBuffer,
    PSSetFastConstantBuffer,
    VSSetFastShaderResource,
    PSSetFastShaderResource,
    HSSetFastSampler,
    DSSetFastSampler,
    GSSetFastSampler,
    PSSetFastSampler,
    CSSetFastSampler,
    VSSetFastSampler,
    IASetVertexBuffers,
    IASetIndexBufferPC,
    IASetIndexBufferXbox,
    IASetInputLayout,
    IASetPrimitiveTopology,
    RemapConstantBufferInheritance,
    RemapShaderResourceInheritance,
    VSSetShaderResourcesPC,
    PSSetShaderResourcesPC,
    DrawIndexedPC,
    DrawIndexedInstancedPC,
    DrawIndexedXbox,
    DrawIndexedInstancedXbox,
    DrawInstancedIndirect,
    DrawIndexedInstancedIndirect,
    Draw,
    ClearState,
    OMSetRenderTargets,
    OMSetBlendState,
    OMSetDepthStencilState,
    RSSetState,
    RSSetViewports,
    RSSetScissorRects,
};

template <abi_t ABI>
struct DSSetShaderCommand
{
    gfx::ID3D11DomainShader<ABI>* pDomainShader;
};

template <abi_t ABI>
struct HSSetShaderCommand
{
    gfx::ID3D11HullShader<ABI>* pHullShader;
};

template <abi_t ABI>
struct GSSetShaderCommand
{
    gfx::ID3D11GeometryShader<ABI>* pShader;
};

template <abi_t ABI>
struct VSSetShaderCommand
{
    gfx::ID3D11VertexShader<ABI>* pVertexShader;
};

template <abi_t ABI>
struct PSSetShaderCommand
{
    gfx::ID3D11PixelShader<ABI>* pPixelShader;
};

template <abi_t ABI>
struct CSSetShaderCommand
{
    gfx::ID3D11ComputeShader<ABI>* pComputeShader;
};

template <abi_t ABI>
struct VSSetFastConstantBufferCommand
{
    UINT Slot;
    gfx::ID3D11Buffer<ABI>* pConstantBuffer;
};

template <abi_t ABI>
struct PSSetFastConstantBufferCommand
{
    UINT Slot;
    gfx::ID3D11Buffer<ABI>* pConstantBuffer;
};

template <abi_t ABI>
struct PSSetFastShaderResourceCommand
{
    UINT Slot;
    gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView;
};

template <abi_t ABI>
struct VSSetFastShaderResourceCommand
{
    UINT Slot;
    gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView;
};

template <abi_t ABI>
struct HSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct DSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct GSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct PSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct CSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct VSSetFastSamplerCommand
{
    UINT Slot;
    gfx::ID3D11SamplerState<ABI>* pSampler;
};

template <abi_t ABI>
struct IASetVertexBuffersCommand
{
    UINT StartSlot;
    UINT NumBuffers;
    gfx::ID3D11Buffer<ABI>* const* ppVertexBuffers;
    const UINT* pStrides;
    const UINT* pOffsets;
};

template <abi_t ABI>
struct IASetIndexBufferPCCommand
{
    gfx::ID3D11Buffer<ABI>* pIndexBuffer;
    UINT HardwareIndexFormat;
    UINT Offset;
};

template <abi_t ABI>
struct IASetIndexBufferXboxCommand
{
    UINT HardwareIndexFormat;
    gfx::ID3D11Buffer<ABI>* pIndexBuffer;
    UINT Offset;
};

template <abi_t ABI>
struct IASetInputLayoutCommand
{
    gfx::ID3D11InputLayout<ABI>* pInputLayout;
};

struct IASetPrimitiveTopologyCommand
{
    D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
};

struct RemapConstantBufferInheritanceCommand
{
    gfx::D3D11_STAGE Stage;
    UINT Slot;
    gfx::D3D11_STAGE InheritStage;
    UINT InheritSlot;
};

struct RemapShaderResourceInheritanceCommand
{
    gfx::D3D11_STAGE Stage;
    UINT Slot;
    gfx::D3D11_STAGE InheritStage;
    UINT InheritSlot;
};

template <abi_t ABI>
struct VSSetShaderResourcesPCCommand
{
    UINT StartSlot;
    UINT NumViews;
    gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews;
};

template <abi_t ABI>
struct PSSetShaderResourcesPCCommand
{
    UINT StartSlot;
    UINT NumViews;
    gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews;
};

struct DrawIndexedPCCommand
{
    UINT IndexCount;
    UINT StartIndexLocation;
    INT BaseVertexLocation;
};

struct DrawIndexedInstancedPCCommand
{
    UINT IndexCountPerInstance;
    UINT InstanceCount;
    UINT StartIndexLocation;
    INT BaseVertexLocation;
    UINT StartInstanceLocation;
};

struct DrawIndexedXboxCommand
{
    UINT64 StartIndexLocationAndIndexCount;
    INT BaseVertexLocation;
};

struct DrawIndexedInstancedXboxCommand
{
    UINT64 StartIndexLocationAndIndexCountPerInstance;
    UINT64 BaseVertexLocationAndStartInstanceLocation;
    UINT InstanceCount;
};

template <abi_t ABI>
struct DrawInstancedIndirectCommand
{
    gfx::ID3D11Buffer<ABI>* pBufferForArgs;
    UINT AlignedByteOffsetForArgs;
};

template <abi_t ABI>
struct DrawIndexedInstancedIndirectCommand
{
    gfx::ID3D11Buffer<ABI>* pBufferForArgs;
    UINT AlignedByteOffsetForArgs;
};

struct DrawCommand
{
    UINT VertexCount;
    UINT StartVertexLocation;
};

struct ClearStateCommand
{

};

template <abi_t ABI>
struct OMSetRenderTargetsCommand
{
    UINT NumViews;
    gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews;
    gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView;
};

template <abi_t ABI>
struct OMSetBlendStateCommand
{
    gfx::ID3D11BlendState<ABI> *pBlendState;
    FLOAT BlendFactor[4];
    UINT SampleMask;
};

template <abi_t ABI>
struct OMSetDepthStencilStateCommand
{
    gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState;
    UINT StencilRef;
};

template <abi_t ABI>
struct RSSetStateCommand
{
    gfx::ID3D11RasterizerState<ABI> *pRasterizerState;
};

struct RSSetViewportsCommand
{
    UINT NumViewports;
    D3D11_VIEWPORT *pViewports;
};

struct RSSetScissorRectsCommand
{
    UINT NumRects;
    D3D11_RECT *pRects;
};

template <abi_t ABI>
struct DrawBundlesCommand
{
public:

    union
    {
        DSSetShaderCommand<ABI> DSSetShader;
        HSSetShaderCommand<ABI> HSSetShader;
        GSSetShaderCommand<ABI> GSSetShader;
        VSSetShaderCommand<ABI> VSSetShader;
        PSSetShaderCommand<ABI> PSSetShader;
        CSSetShaderCommand<ABI> CSSetShader;
        VSSetFastConstantBufferCommand<ABI> VSSetFastConstantBuffer;
        PSSetFastConstantBufferCommand<ABI> PSSetFastConstantBuffer;
        VSSetFastShaderResourceCommand<ABI> VSSetFastShaderResource;
        PSSetFastShaderResourceCommand<ABI> PSSetFastShaderResource;
        DSSetFastSamplerCommand<ABI> DSSetFastSampler;
        HSSetFastSamplerCommand<ABI> HSSetFastSampler;
        GSSetFastSamplerCommand<ABI> GSSetFastSampler;
        VSSetFastSamplerCommand<ABI> VSSetFastSampler;
        PSSetFastSamplerCommand<ABI> PSSetFastSampler;
        CSSetFastSamplerCommand<ABI> CSSetFastSampler;
        IASetVertexBuffersCommand<ABI> IASetVertexBuffers;
        IASetIndexBufferPCCommand<ABI> IASetIndexBufferPC;
        IASetIndexBufferXboxCommand<ABI> IASetIndexBufferXbox;
        IASetInputLayoutCommand<ABI> IASetInputLayout;
        IASetPrimitiveTopologyCommand IASetPrimitiveTopology;
        RemapConstantBufferInheritanceCommand RemapConstantBufferInheritance;
        RemapShaderResourceInheritanceCommand RemapShaderResourceInheritance;
        VSSetShaderResourcesPCCommand<ABI> VSSetShaderResourcesPC;
        PSSetShaderResourcesPCCommand<ABI> PSSetShaderResourcesPC;
        DrawIndexedPCCommand DrawIndexedPC;
        DrawIndexedXboxCommand DrawIndexedXbox;
        DrawIndexedInstancedPCCommand DrawIndexedInstancedPC;
        DrawIndexedInstancedXboxCommand DrawIndexedInstancedXbox;
        DrawInstancedIndirectCommand<ABI> DrawInstancedIndirect;
        DrawIndexedInstancedIndirectCommand<ABI> DrawIndexedInstancedIndirect;
        DrawCommand Draw;
        ClearStateCommand ClearState;
        OMSetRenderTargetsCommand<ABI> OMSetRenderTargets;
        OMSetBlendStateCommand<ABI> OMSetBlendState;
        OMSetDepthStencilStateCommand<ABI> OMSetDepthStencilState;
        RSSetStateCommand<ABI> RSSetState;
        RSSetViewportsCommand RSSetViewports;
        RSSetScissorRectsCommand RSSetScissorRects;
    };

    DrawBundlesCommandType m_CommandType;
};

template<abi_t ABI>
class D3D11CommandList : public gfx::ID3D11CommandList<ABI>
{
public:
    ID3D11CommandList* m_pFunction = nullptr;
    BOOL m_IsDrawBundle = FALSE;
    std::vector<DrawBundlesCommand<ABI>> m_Commands;

    D3D11CommandList(ID3D11CommandList* CmdList)
    {
        m_pFunction = CmdList;
        m_IsDrawBundle = FALSE;
        InterlockedIncrement(&this->m_RefCount);
    }
    D3D11CommandList(std::vector<DrawBundlesCommand<ABI>> Commands)
    {
        m_Commands = Commands;
        m_IsDrawBundle = TRUE;
        InterlockedIncrement(&this->m_RefCount);
    }

    //
    // IUnknown
    //
    HRESULT QueryInterface(REFIID riid, void** ppvObject);
    ULONG AddRef();
    ULONG Release();

    //
    // ID3D11DeviceChild
    //
    void GetDevice(gfx::ID3D11Device<ABI>** ppDevice);
    HRESULT GetPrivateData(_GUID const& guid, uint32_t* pDataSize, void* pData);
    HRESULT SetPrivateData(_GUID const& guid, uint32_t DataSize, void const* pData);
    HRESULT SetPrivateDataInterface(_GUID const& guid, IUnknown const* pData);
    HRESULT SetPrivateDataInterfaceGraphics(_GUID const& guid, xbox::IGraphicsUnknown<ABI> const* pData);
    HRESULT SetName(LPCWSTR pName)
    {
        IMPLEMENT_STUB();
        return E_NOTIMPL;
    }

    //
    // ID3D11CommandList
    //
    uint32_t GetContextFlags();
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11CommandList<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);