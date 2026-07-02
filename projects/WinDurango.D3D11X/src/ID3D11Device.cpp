#pragma comment(lib, "d3dcompiler.lib")
#include "ID3D11Device.h"
#include "IDXGIDevice.h"
#include "ID3D11Resource.h"
#include "ID3D11View.h"
#include "ID3D11State.h"
#include "ID3D11Shader.h"
#include "ID3D11DeviceContext.h"
#include "ID3D11Runtime.h"
#include "ID3D11DMAEngineContext.h"
#include "d3d11.x.h"
#include <d3d12.h>
#include <d3dcompiler.h>
#include "ID3D11DrawBundlesContext.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11Device>() || riid == xcom::guid_of<gfx::ID3D11Device1>() ||
        riid == xcom::guid_of<gfx::ID3D11Device2>() || riid == xcom::guid_of<gfx::ID3D11DeviceX>() ||
        riid == xcom::guid_of<gfx::ID3D11PerformanceDeviceX>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == xcom::guid_of<gfx::IDXGIDevice>() || riid == xcom::guid_of<gfx::IDXGIDevice1>() ||
        riid == xcom::guid_of<gfx::IDXGIDevice2>())
    {
        m_pFunction->QueryInterface(__uuidof(IDXGIDevice2), ppvObject);
        *ppvObject = new DXGIDevice2<ABI>(static_cast<IDXGIDevice2 *>(*ppvObject));
        return S_OK;
    }

    if (riid == xcom::guid_of<xbox::IGraphicsUnwrap>())
    {
        *ppvObject = m_pFunction;
        return S_OK;
    }

    if (riid == __uuidof(ID3D11InfoQueue))
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    if (riid == __uuidof(ID3D12Device))
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11DeviceX<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11DeviceX<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11Device
//
template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateBuffer(D3D11_BUFFER_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                                        gfx::ID3D11Buffer<ABI> **ppBuffer)
{
    auto pDesc2 = *pDesc;
    pDesc2.MiscFlags = ConvertMiscFlags(pDesc->MiscFlags);

    HRESULT hr = 0;
    ID3D11Buffer *Buffer = nullptr;
    hr = m_pFunction->CreateBuffer(&pDesc2, pData, &Buffer);

    if (Buffer)
    {
        *ppBuffer = new D3D11Buffer<ABI>(Buffer);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                                           gfx::ID3D11Texture1D<ABI> **ppTexture1D)
{
    auto pDesc2 = *pDesc;
    pDesc2.MiscFlags = ConvertMiscFlags(pDesc->MiscFlags);

    HRESULT hr = 0;
    ID3D11Texture1D *Tex = nullptr;
    hr = m_pFunction->CreateTexture1D(&pDesc2, pData, &Tex);

    if (Tex)
    {
        *ppTexture1D = new D3D11Texture1D<ABI>(Tex);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                                           gfx::ID3D11Texture2D<ABI> **ppTexture2D)
{
    auto pDesc2 = *pDesc;
    pDesc2.MiscFlags = ConvertMiscFlags(pDesc->MiscFlags);
    pDesc2.SampleDesc.Quality = 0;

    if (pDesc->Usage == D3D11_USAGE_DYNAMIC)
    {
        if (!pDesc->CPUAccessFlags)
            pDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }

    HRESULT hr = 0;
    ID3D11Texture2D *Tex = nullptr;
    hr = m_pFunction->CreateTexture2D(&pDesc2, pData, &Tex);

    if (Tex)
    {
        *ppTexture2D = new D3D11Texture2D<ABI>(Tex);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData,
                                           gfx::ID3D11Texture3D<ABI> **ppTexture3D)
{
    auto pDesc2 = *pDesc;
    pDesc2.MiscFlags = ConvertMiscFlags(pDesc->MiscFlags);

    HRESULT hr = 0;
    ID3D11Texture3D *Tex = nullptr;
    hr = m_pFunction->CreateTexture3D(&pDesc2, pData, &Tex);

    if (Tex)
    {
        *ppTexture3D = new D3D11Texture3D<ABI>(Tex);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateShaderResourceView(gfx::ID3D11Resource<ABI> *pResource,
                                                    D3D11_SHADER_RESOURCE_VIEW_DESC const *pDesc,
                                                    gfx::ID3D11ShaderResourceView<ABI> **ppSRV)
{
    HRESULT hr = 0;

    D3D11_RESOURCE_DIMENSION Type{};
    pResource->GetType(&Type);

    ID3D11ShaderResourceView *pView = nullptr;

    if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        hr = m_pFunction->CreateShaderResourceView(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, pDesc,
                                                   &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
    {
        hr = m_pFunction->CreateShaderResourceView(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                   &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
    {
        if (pDesc)
        {
            D3D11_TEXTURE2D_DESC Desc{};
            static_cast<D3D11Texture2D<ABI> *>(pResource)->GetDesc(&Desc);

            if (IsFloatFormat(Desc.Format) && IsUINTFormat(pDesc->Format))
            {
                printf("D3D11 Warning: Game is trying to create an UINT SRV over a FLOAT resource!\n");
            }
            else if (IsUnormFormat(Desc.Format) && IsUINTFormat(pDesc->Format))
            {
                printf("D3D11 Warning: Game is trying to create an UINT SRV over an UNORM resource!\n");
            }
        }
        hr = m_pFunction->CreateShaderResourceView(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                   &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
    {
        hr = m_pFunction->CreateShaderResourceView(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                   &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
    {
        hr = m_pFunction->CreateShaderResourceView(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, pDesc,
                                                   &pView);
    }

    if (pView)
    {
        *ppSRV = new D3D11ShaderResourceView<ABI>(pView);
        if (pResource->m_pAllocationStart)
            (*ppSRV)->m_pAllocationStart = pResource->m_pAllocationStart;

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            static_cast<D3D11ShaderResourceView<ABI> *>(*ppSRV)->m_pBuffer = static_cast<D3D11Buffer<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            static_cast<D3D11ShaderResourceView<ABI> *>(*ppSRV)->m_pTexture1D =
                static_cast<D3D11Texture1D<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            static_cast<D3D11ShaderResourceView<ABI> *>(*ppSRV)->m_pTexture2D =
                static_cast<D3D11Texture2D<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            static_cast<D3D11ShaderResourceView<ABI> *>(*ppSRV)->m_pTexture3D =
                static_cast<D3D11Texture3D<ABI> *>(pResource);
        }
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateUnorderedAccessView(gfx::ID3D11Resource<ABI> *pResource,
                                                     D3D11_UNORDERED_ACCESS_VIEW_DESC const *pDesc,
                                                     gfx::ID3D11UnorderedAccessView<ABI> **ppUAV)
{
    HRESULT hr = 0;

    D3D11_RESOURCE_DIMENSION Type{};
    pResource->GetType(&Type);

    ID3D11UnorderedAccessView *pView = nullptr;

    if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        hr = m_pFunction->CreateUnorderedAccessView(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, pDesc,
                                                    &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
    {
        hr = m_pFunction->CreateUnorderedAccessView(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                    &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
    {
        hr = m_pFunction->CreateUnorderedAccessView(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                    &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
    {
        hr = m_pFunction->CreateUnorderedAccessView(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                    &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
    {
        hr = m_pFunction->CreateUnorderedAccessView(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, pDesc,
                                                    &pView);
    }

    if (pView)
    {
        *ppUAV = new D3D11UnorderedAccessView<ABI>(pView);

        (*ppUAV)->m_pAllocationStart = pResource->m_pAllocationStart;
        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            static_cast<D3D11UnorderedAccessView<ABI> *>(*ppUAV)->m_pBuffer =
                static_cast<D3D11Buffer<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            static_cast<D3D11UnorderedAccessView<ABI> *>(*ppUAV)->m_pTexture1D =
                static_cast<D3D11Texture1D<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            static_cast<D3D11UnorderedAccessView<ABI> *>(*ppUAV)->m_pTexture2D =
                static_cast<D3D11Texture2D<ABI> *>(pResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            static_cast<D3D11UnorderedAccessView<ABI> *>(*ppUAV)->m_pTexture3D =
                static_cast<D3D11Texture3D<ABI> *>(pResource);
        }
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateRenderTargetView(gfx::ID3D11Resource<ABI> *pResource,
                                                  D3D11_RENDER_TARGET_VIEW_DESC const *pDesc,
                                                  gfx::ID3D11RenderTargetView<ABI> **ppRTV)
{
    HRESULT hr = 0;

    D3D11_RESOURCE_DIMENSION Type{};
    pResource->GetType(&Type);

    ID3D11RenderTargetView *pView = nullptr;

    if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        hr =
            m_pFunction->CreateRenderTargetView(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, pDesc, &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
    {
        hr = m_pFunction->CreateRenderTargetView(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
    {
        hr = m_pFunction->CreateRenderTargetView(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
    {
        hr = m_pFunction->CreateRenderTargetView(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
    {
        hr = m_pFunction->CreateRenderTargetView(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }

    if (pView)
    {
        *ppRTV = new D3D11RenderTargetView<ABI>(pView);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDepthStencilView(gfx::ID3D11Resource<ABI> *pResource,
                                                  D3D11_DEPTH_STENCIL_VIEW_DESC const *pDesc,
                                                  gfx::ID3D11DepthStencilView<ABI> **ppDSV)
{
    HRESULT hr = 0;

    D3D11_RESOURCE_DIMENSION Type{};
    pResource->GetType(&Type);

    ID3D11DepthStencilView *pView = nullptr;

    if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        hr =
            m_pFunction->CreateDepthStencilView(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, pDesc, &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
    {
        hr = m_pFunction->CreateDepthStencilView(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
    {
        hr = m_pFunction->CreateDepthStencilView(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
    {
        hr = m_pFunction->CreateDepthStencilView(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }
    else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
    {
        hr = m_pFunction->CreateDepthStencilView(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, pDesc,
                                                 &pView);
    }

    if (pView)
    {
        *ppDSV = new D3D11DepthStencilView<ABI>(pView);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, uint32_t NumElements,
                                             const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength,
                                             gfx::ID3D11InputLayout<ABI> **ppInputLayout)
{
    ID3D11InputLayout *InputLayout = nullptr;
    HRESULT hr = m_pFunction->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, &InputLayout);
    if (InputLayout)
    {
        *ppInputLayout = new D3D11InputLayout<ABI>(InputLayout);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateVertexShader(void const *pBytecode, uint64_t BytecodeLength,
                                              ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11VertexShader<ABI> **ppVS)
{
    //Before some Unity versions create the swap chain, they pass
    //an invalid shader expecting this call to fail, but on PC, it
    //makes the D3D11 Device get removed.
    if (((uintptr_t)pBytecode == 0x00007ff60f7ce540 || (uintptr_t)pBytecode == 0x00007ff6f179e540) && BytecodeLength == 3028)
        return E_INVALIDARG;
    
    if (((uintptr_t)pBytecode == 0x00007ff7604168f0) && BytecodeLength == 3172)
        return E_INVALIDARG;

    ID3D11VertexShader *Shader{};
    HRESULT hr = m_pFunction->CreateVertexShader(pBytecode, BytecodeLength, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppVS = new D3D11VertexShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateGeometryShader(void const *pBytecode, uint64_t BytecodeLentgh,
                                                ID3D11ClassLinkage *pClassLinkage,
                                                gfx::ID3D11GeometryShader<ABI> **ppGS)
{
    ID3D11GeometryShader *Shader{};
    HRESULT hr = m_pFunction->CreateGeometryShader(pBytecode, BytecodeLentgh, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppGS = new D3D11GeometryShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateGeometryShaderWithStreamOutput(void const *pBytecode, uint64_t BytecodeLentgh,
                                                                D3D11_SO_DECLARATION_ENTRY const *pSODeclaration,
                                                                uint32_t NumEntries, uint32_t const *pStrides,
                                                                uint32_t NumStides, uint32_t RasterizedStream,
                                                                ID3D11ClassLinkage *pClassLinkage,
                                                                gfx::ID3D11GeometryShader<ABI> **ppGS)
{
    ID3D11GeometryShader *Shader{};
    HRESULT hr = m_pFunction->CreateGeometryShaderWithStreamOutput(pBytecode, BytecodeLentgh, pSODeclaration,
                                                                   NumEntries, pStrides, NumStides, RasterizedStream,
                                                                   pClassLinkage, &Shader);
    if (Shader)
    {
        *ppGS = new D3D11GeometryShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePixelShader(void const *pBytecode, uint64_t BytecodeLentgh,
                                             ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11PixelShader<ABI> **ppPS)
{
    ID3D11PixelShader *Shader{};
    HRESULT hr = m_pFunction->CreatePixelShader(pBytecode, BytecodeLentgh, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppPS = new D3D11PixelShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateHullShader(void const *pBytecode, uint64_t BytecodeLentgh,
                                            ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11HullShader<ABI> **ppHS)
{
    ID3D11HullShader *Shader{};
    HRESULT hr = m_pFunction->CreateHullShader(pBytecode, BytecodeLentgh, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppHS = new D3D11HullShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDomainShader(void const *pBytecode, uint64_t BytecodeLentgh,
                                              ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11DomainShader<ABI> **ppDS)
{
    ID3D11DomainShader *Shader{};
    HRESULT hr = m_pFunction->CreateDomainShader(pBytecode, BytecodeLentgh, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppDS = new D3D11DomainShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateComputeShader(void const *pBytecode, uint64_t BytecodeLentgh,
                                               ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11ComputeShader<ABI> **ppCS)
{
    ID3D11ComputeShader *Shader{};
    HRESULT hr = m_pFunction->CreateComputeShader(pBytecode, BytecodeLentgh, pClassLinkage, &Shader);
    if (Shader)
    {
        *ppCS = new D3D11ComputeShader<ABI>(Shader);
    }
    return hr;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::CreateClassLinkage(ID3D11ClassLinkage **ppClassLinkage)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateBlendState(D3D11_BLEND_DESC const *pDesc, gfx::ID3D11BlendState<ABI> **ppBlendState)
{
    ID3D11BlendState *State{};
    HRESULT hr = m_pFunction->CreateBlendState(pDesc, &State);
    if (State)
    {
        *ppBlendState = new D3D11BlendState<ABI>(State);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC const *pDesc,
                                                   gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState)
{
    ID3D11DepthStencilState *State{};
    HRESULT hr = m_pFunction->CreateDepthStencilState(pDesc, &State);
    if (State)
    {
        *ppDepthStencilState = new D3D11DepthStencilState<ABI>(State);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateRasterizerState(D3D11_RASTERIZER_DESC const *pDesc,
                                                 gfx::ID3D11RasterizerState<ABI> **ppRasterizerState)
{
    ID3D11RasterizerState *State{};
    HRESULT hr = m_pFunction->CreateRasterizerState(pDesc, &State);
    if (State)
    {
        *ppRasterizerState = new D3D11RasterizerState<ABI>(State);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateSamplerState(D3D11_SAMPLER_DESC const *pDesc,
                                              gfx::ID3D11SamplerState<ABI> **ppSamplerState)
{
    ID3D11SamplerState *State{};
    HRESULT hr = m_pFunction->CreateSamplerState(pDesc, &State);
    if (State)
    {
        *ppSamplerState = new D3D11SamplerState<ABI>(State);
    }
    return hr;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::CreateQuery(D3D11_QUERY_DESC const *pDesc, ID3D11Query **ppQuery)
{
    return m_pFunction->CreateQuery(pDesc, ppQuery);
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePredicate(D3D11_QUERY_DESC const *pDesc, ID3D11Predicate **ppPrediticate)
{
    return m_pFunction->CreatePredicate(pDesc, ppPrediticate);
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateCounter(D3D11_COUNTER_DESC const *pDesc, ID3D11Counter **ppCounter)
{
    return m_pFunction->CreateCounter(pDesc, ppCounter);
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDeferredContext(uint32_t Flags, gfx::ID3D11DeviceContext<ABI> **ppDeferredContext)
{
    if (Flags & D3D11_CREATE_DEFERRED_CONTEXT_DRAW_BUNDLES)
    {
        *ppDeferredContext = new D3D11DrawBundlesContext<ABI>(nullptr);
        return S_OK;
    }

    ID3D11DeviceContext* pContext{};
    ID3D11DeviceContext2* pContext2{};
    m_pFunction->CreateDeferredContext(0, &pContext);

    pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
    pContext->Release();

    *ppDeferredContext = new D3D11DeviceContextX<ABI>(pContext2);
    return S_OK;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::OpenSharedResource(void *pResource, _GUID const &retInterface, void **ppResource)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::CheckFormatSupport(DXGI_FORMAT Format, uint32_t *pFormatSupport)
{
    return m_pFunction->CheckFormatSupport(Format, pFormatSupport);
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CheckMultisampleQualityLevels(DXGI_FORMAT Format, uint32_t SampleCount,
                                                         uint32_t *pNumQualityLevels)
{
    return m_pFunction->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

template <abi_t ABI> void D3D11DeviceX<ABI>::CheckCounterInfo(D3D11_COUNTER_INFO *pCounterInfo)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CheckCounter(D3D11_COUNTER_DESC const *pDesc, D3D11_COUNTER_TYPE *pCounterType,
                                        uint32_t *pActiveCounters, char *szName, uint32_t *pNameLength, char *szUnits,
                                        uint32_t *pUnitsLength, char *szDescription, uint32_t *pDescriptionLength)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CheckFeatureSupport(D3D11_FEATURE Feature, void *pFeatureSupportData,
                                               uint32_t FeatureSupportDataSize)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    /*
     * IDK what Im doing here, rod plz help
    */
    return m_pFunction->GetPrivateData(guid, pDataSize, pData);
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    /*
     * IDK what Im doing here, rod plz help
    */
    return m_pFunction->SetPrivateDataInterface(guid, pData);
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> D3D_FEATURE_LEVEL D3D11DeviceX<ABI>::GetFeatureLevel()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> uint32_t D3D11DeviceX<ABI>::GetCreationFlags()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::GetDeviceRemovedReason()
{
    return m_pFunction->GetDeviceRemovedReason();
}

template <abi_t ABI> void D3D11DeviceX<ABI>::GetImmediateContext(gfx::ID3D11DeviceContext<ABI> **ppImmediateContext)
{
    ID3D11DeviceContext* pContext{};
    ID3D11DeviceContext2* pContext2{};
    m_pFunction->GetImmediateContext(&pContext);

    pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
    pContext->Release();

    *ppImmediateContext = new D3D11DeviceContextX<ABI>(pContext2);
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::SetExceptionMode(uint32_t ExceptionMode)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> uint32_t D3D11DeviceX<ABI>::GetExceptionMode()
{
    IMPLEMENT_STUB();
    return {};
}

//
// ID3D11Device1
//
template <abi_t ABI> void D3D11DeviceX<ABI>::GetImmediateContext1(gfx::ID3D11DeviceContext1<ABI> **ppImmediateContext)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDeferredContext1(uint32_t Flags, gfx::ID3D11DeviceContext1<ABI> **ppDeferredContext1)
{
    if (Flags & D3D11_CREATE_DEFERRED_CONTEXT_DRAW_BUNDLES)
    {
        *ppDeferredContext1 = new D3D11DrawBundlesContext<ABI>(nullptr);
        return S_OK;
    }

    ID3D11DeviceContext* pContext{};
    ID3D11DeviceContext2* pContext2{};
    m_pFunction->CreateDeferredContext(0, &pContext);

    pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
    pContext->Release();

    *ppDeferredContext1 = new D3D11DeviceContextX<ABI>(pContext2);
    return S_OK;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateBlendState1(D3D11_BLEND_DESC1 const *pDesc, ID3D11BlendState1 **ppBlendState)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateRasterizerState1(D3D11_RASTERIZER_DESC1 const *pDesc,
                                                  ID3D11RasterizerState1 **ppRasterizerState)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDeviceContextState(uint32_t Flags, D3D_FEATURE_LEVEL const *pFeatureLevels,
                                                    uint32_t FeatureLevels, uint32_t SDKVersion,
                                                    _GUID const &EmulatedInterface,
                                                    D3D_FEATURE_LEVEL *pChosenFeatureLevel,
                                                    ID3DDeviceContextState **ppContextState)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::OpenSharedResource1(void *pResource, _GUID const &retInterface, void **ppResource)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::OpenSharedResourceByName(wchar_t const *pName, uint32_t dwDesiredAccess,
                                                    _GUID const &retInterface, void **ppResource)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Device2
//
template <abi_t ABI> void D3D11DeviceX<ABI>::GetImmediateContext2(gfx::ID3D11DeviceContext2<ABI> **ppImmediateContext)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDeferredContext2(uint32_t Flags, gfx::ID3D11DeviceContext2<ABI> **ppDeferredContext)
{
    if (Flags & D3D11_CREATE_DEFERRED_CONTEXT_DRAW_BUNDLES)
    {
        *ppDeferredContext = new D3D11DrawBundlesContext<ABI>(nullptr);
        return S_OK;
    }

    ID3D11DeviceContext* pContext{};
    ID3D11DeviceContext2* pContext2{};
    m_pFunction->CreateDeferredContext(0, &pContext);

    pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
    pContext->Release();

    *ppDeferredContext = new D3D11DeviceContextX<ABI>(pContext2);
    return S_OK;
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::GetResourceTiling(gfx::ID3D11Resource<ABI> *pTiledResource,
                                          uint32_t *pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC *pPackedMipDesc,
                                          D3D11_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                                          uint32_t *pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet,
                                          D3D11_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CheckMultisampleQualityLevels1(DXGI_FORMAT Format, uint32_t SampleCount, uint32_t Flags,
                                                          uint32_t *pNumQualityLevels)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11DeviceX
//
template <abi_t ABI> void D3D11DeviceX<ABI>::GetImmediateContextX(gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateCounterSet(gfx::D3D11X_COUNTER_SET_DESC const *pCounterSetDesc,
                                            gfx::ID3D11CounterSetX **ppCounterSet)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::CreateCounterSample(gfx::ID3D11CounterSampleX **ppCounterSample)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::SetDriverHint(UINT Feature, UINT Value)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDmaEngineContext(gfx::D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc,
                                                  gfx::ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext)
{
    *ppDmaDeviceContext = new D3D11DMAEngineContextX<ABI>();
    return S_OK;
}

template <abi_t ABI> BOOL D3D11DeviceX<ABI>::IsFencePending(UINT64 Fence)
{
    return Fence > 0xFFFF && !*(BOOL*)Fence;
}

template <abi_t ABI> BOOL D3D11DeviceX<ABI>::IsResourcePending(gfx::ID3D11Resource<ABI> *pResource)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePlacementBuffer(D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress,
                                                 gfx::ID3D11Buffer<ABI> **ppBuffer)
{
    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
    D3D11_SUBRESOURCE_DATA initialData{};
    initialData.pSysMem = pVirtualAddress;
    initialData.SysMemPitch = 0;
    initialData.SysMemSlicePitch = 0;

    auto pDesc2 = *pDesc;
    if (pDesc2.Usage == D3D11_USAGE_IMMUTABLE)
    {
        pDesc2.Usage = D3D11_USAGE_DEFAULT;
    }

    if (pDesc2.Usage == D3D11_USAGE_DEFAULT)
    {
        if (pDesc2.BindFlags == D3D11_BIND_CONSTANT_BUFFER)
        {
            //EA, would you mind telling me why the fuck would a constant buffer with default usage need CPU write access?
            if (pDesc2.CPUAccessFlags > 0) pDesc2.CPUAccessFlags = 0;
        }
    }

    HRESULT hr = 0;
    if (!pVirtualAddress)
        hr = CreateBuffer(&pDesc2, nullptr, ppBuffer);
    else
        hr = CreateBuffer(&pDesc2, &initialData, ppBuffer);

    if (pVirtualAddress)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(pVirtualAddress, &mbi, sizeof(mbi));
        if (Result == sizeof(mbi) && mbi.AllocationBase)
        {
            (*ppBuffer)->m_pAllocationStart = pVirtualAddress;
            static_cast<D3D11Buffer<ABI> *>((*ppBuffer))->m_IsDirty = true;
            g_ResourceMap.insert({mbi.AllocationBase, (*ppBuffer)});
        }
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePlacementTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                                    void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D)
{
    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
    std::vector<D3D11_SUBRESOURCE_DATA> initialData(pDesc->ArraySize);
    UINT RowPitch = 0;
    UINT SlicePitch = 0;
    auto pDesc2 = *pDesc;
    pDesc2.MipLevels = 1;
    if (pDesc2.Usage == D3D11_USAGE_IMMUTABLE)
    {
        pDesc2.Usage = D3D11_USAGE_DEFAULT;
    }

    for (int i = 0; i < initialData.size(); i++)
    {
        initialData[i].pSysMem = pVirtualAddress;
        CalculatePitch(pDesc2.Width, 1, pDesc2.Format, &RowPitch, &SlicePitch);
        initialData[i].SysMemPitch = RowPitch;
        initialData[i].SysMemSlicePitch = SlicePitch;
    }

    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(pVirtualAddress, &mbi, sizeof(mbi)) || mbi.RegionSize < SlicePitch ||
        (mbi.State & MEM_COMMIT) != MEM_COMMIT || (mbi.Protect & (PAGE_READWRITE | PAGE_READONLY)) == 0)
    {
        HRESULT hr = CreateTexture1D(&pDesc2, 0, ppTexture1D);
        (*ppTexture1D)->m_pAllocationStart = pVirtualAddress;
        initialData.clear();
        return hr;
    }
    else
    {
        HRESULT hr = CreateTexture1D(&pDesc2, initialData.data(), ppTexture1D);
        (*ppTexture1D)->m_pAllocationStart = pVirtualAddress;
        initialData.clear();
        return hr;
    }

    return S_OK;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePlacementTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                                    void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D)
{
    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
    std::vector<D3D11_SUBRESOURCE_DATA> initialData(pDesc->ArraySize);
    UINT RowPitch = 0;
    UINT SlicePitch = 0;
    auto pDesc2 = *pDesc;
    pDesc2.MipLevels = 1;
    if (pDesc2.Usage == D3D11_USAGE_IMMUTABLE)
    {
        pDesc2.Usage = D3D11_USAGE_DEFAULT;
    }

    for (int i = 0; i < initialData.size(); i++)
    {
        initialData[i].pSysMem = pVirtualAddress;
        CalculatePitch(pDesc2.Width, pDesc2.Height, pDesc2.Format, &RowPitch, &SlicePitch);
        initialData[i].SysMemPitch = RowPitch;
        initialData[i].SysMemSlicePitch = SlicePitch;
    }

    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(pVirtualAddress, &mbi, sizeof(mbi)) || mbi.RegionSize < SlicePitch ||
        (mbi.State & MEM_COMMIT) != MEM_COMMIT || (mbi.Protect & (PAGE_READWRITE | PAGE_READONLY)) == 0)
    {
        HRESULT hr = CreateTexture2D(&pDesc2, 0, ppTexture2D);
        if (mbi.AllocationBase) (*ppTexture2D)->m_pAllocationStart = pVirtualAddress;
        if (mbi.AllocationBase) static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_TileModeIndex = TileModeIndex;
        if (mbi.AllocationBase) static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_IsDirty = true;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_RowPitch = RowPitch;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_SlicePitch = SlicePitch;
        if (mbi.AllocationBase) g_ResourceMap.insert({mbi.AllocationBase, (*ppTexture2D)});
        initialData.clear();
        return hr;
    }
    else if (pVirtualAddress && pDesc2.SampleDesc.Count > 1)
    {
        HRESULT hr = CreateTexture2D(&pDesc2, 0, ppTexture2D);
        (*ppTexture2D)->m_pAllocationStart = pVirtualAddress;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_TileModeIndex = TileModeIndex;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_IsDirty = true;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_RowPitch = RowPitch;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_SlicePitch = SlicePitch;
        g_ResourceMap.insert({mbi.AllocationBase, (*ppTexture2D)});
        initialData.clear();
        return hr;
    }
    else
    {
        HRESULT hr = CreateTexture2D(&pDesc2, initialData.data(), ppTexture2D);
        (*ppTexture2D)->m_pAllocationStart = pVirtualAddress;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_TileModeIndex = TileModeIndex;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_IsDirty = true;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_RowPitch = RowPitch;
        static_cast<D3D11Texture2D<ABI>*>((*ppTexture2D))->m_SlicePitch = SlicePitch;
        g_ResourceMap.insert({mbi.AllocationBase, (*ppTexture2D)});
        initialData.clear();
        return hr;
    }

    return S_OK;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePlacementTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch,
                                                    void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D)
{
    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
    std::vector<D3D11_SUBRESOURCE_DATA> initialData(1);
    UINT RowPitch = 0;
    UINT SlicePitch = 0;
    auto pDesc2 = *pDesc;
    pDesc2.MipLevels = 1;
    if (pDesc2.Usage == D3D11_USAGE_IMMUTABLE)
    {
        pDesc2.Usage = D3D11_USAGE_DEFAULT;
    }

    for (int i = 0; i < initialData.size(); i++)
    {
        initialData[i].pSysMem = pVirtualAddress;
        CalculatePitch(pDesc2.Width, pDesc2.Height, pDesc2.Format, &RowPitch, &SlicePitch);
        initialData[i].SysMemPitch = RowPitch;
        initialData[i].SysMemSlicePitch = SlicePitch;
    }

    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(pVirtualAddress, &mbi, sizeof(mbi)) || mbi.RegionSize < SlicePitch ||
        (mbi.State & MEM_COMMIT) != MEM_COMMIT || (mbi.Protect & (PAGE_READWRITE | PAGE_READONLY)) == 0)
    {
        HRESULT hr = CreateTexture3D(&pDesc2, 0, ppTexture3D);
        (*ppTexture3D)->m_pAllocationStart = pVirtualAddress;
        initialData.clear();
        return hr;
    }
    else
    {
        HRESULT hr = CreateTexture3D(&pDesc2, initialData.data(), ppTexture3D);
        (*ppTexture3D)->m_pAllocationStart = pVirtualAddress;
        initialData.clear();
        return hr;
    }

    return S_OK;
}

template <abi_t ABI> void D3D11DeviceX<ABI>::GetTimestamps(UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateComputeContextX(gfx::D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc,
                                                 gfx::ID3D11ComputeContextX **ppComputeContext)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateSamplerStateX(gfx::D3D11X_SAMPLER_DESC const *pSamplerDesc,
                                               gfx::ID3D11SamplerState<ABI> **ppSamplerState)
{
    D3D11_SAMPLER_DESC SamplerDesc{};
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerDesc.MaxAnisotropy = 1;
    SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    SamplerDesc.MinLOD = 0;
    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.BorderColor[0] = 0.0f;
    SamplerDesc.BorderColor[1] = 0.0f;
    SamplerDesc.BorderColor[2] = 0.0f;
    SamplerDesc.BorderColor[3] = 0.0f;

    ID3D11SamplerState *SamplerState;
    HRESULT hr = m_pFunction->CreateSamplerState(&SamplerDesc, &SamplerState);

    if (SamplerState)
    {
        *ppSamplerState = new D3D11SamplerState<ABI>(SamplerState);
    }

    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDeferredContextX(UINT Flags, gfx::ID3D11DeviceContextX<ABI> **ppDeferredContext)
{
    if (Flags & D3D11_CREATE_DEFERRED_CONTEXT_DRAW_BUNDLES)
    {
        *ppDeferredContext = reinterpret_cast<gfx::ID3D11DeviceContextX<ABI>*>(new D3D11DrawBundlesContext<ABI>(nullptr));
        return S_OK;
    }

    ID3D11DeviceContext* pContext{};
    ID3D11DeviceContext2* pContext2{};
    m_pFunction->CreateDeferredContext(0, &pContext);

    pContext->QueryInterface(IID_PPV_ARGS(&pContext2));
    pContext->Release();

    *ppDeferredContext = new D3D11DeviceContextX<ABI>(pContext2);
    return S_OK;
}

template <abi_t ABI> void D3D11DeviceX<ABI>::GarbageCollect(UINT Flags)
{

}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreateDepthStencilStateX(D3D11_DEPTH_STENCIL_DESC const *pDepthStencilStateDesc,
                                                    gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState)
{
    ID3D11DepthStencilState *State{};
    HRESULT hr = m_pFunction->CreateDepthStencilState(pDepthStencilStateDesc, &State);
    if (State)
    {
        *ppDepthStencilState = new D3D11DepthStencilState<ABI>(State);
    }
    return hr;
}

template <abi_t ABI>
HRESULT D3D11DeviceX<ABI>::CreatePlacementRenderableTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex,
                                                              UINT Pitch,
                                                              gfx::D3D11X_RENDERABLE_TEXTURE_ADDRESSES const *pAddresses,
                                                              gfx::ID3D11Texture2D<ABI> **ppTexture2D)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::GetDriverStatistics(UINT StructSize, gfx::D3D11X_DRIVER_STATISTICS *pStatistics)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::GetDescriptorSize(gfx::D3D11X_DESCRIPTOR_TYPE DescriptorType)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::ComposeShaderResourceView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                                  gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                                  gfx::D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW *pDescriptorSrv)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::ComposeUnorderedAccessView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                                   gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                                   gfx::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *pDescriptorUav)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::ComposeConstantBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                                  gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                                  gfx::D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW *pDescriptorCb)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::ComposeVertexBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource,
                                                gfx::D3D11X_RESOURCE_VIEW_DESC const *pViewDesc,
                                                gfx::D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW *pDescriptorVb)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::ComposeSamplerState(gfx::D3D11X_SAMPLER_STATE_DESC const *pSamplerDesc,
                                            gfx::D3D11X_DESCRIPTOR_SAMPLER_STATE *pDescriptorSamplerState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::PlaceSwapChainView(gfx::ID3D11Resource<ABI> *pSwapChainBuffer, gfx::ID3D11View<ABI> *pView)
{

}

template <abi_t ABI> void D3D11DeviceX<ABI>::SetDebugFlags(UINT Flags)
{
    m_DebugFlags = Flags;
}

template <abi_t ABI> uint32_t D3D11DeviceX<ABI>::GetDebugFlags()
{
    return m_DebugFlags;
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::SetHangCallbacks(gfx::D3D11XHANGBEGINCALLBACK pBeginCallback,
                                         gfx::D3D11XHANGPRINTCALLBACK pPrintCallback,
                                         gfx::D3D11XHANGDUMPCALLBACK pDumpCallback)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceX<ABI>::ReportGpuHang(UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11DeviceX<ABI>::SetGpuMemoryPriority(UINT Priority)
{
    /*
     * TODO: Impl
    */
    return S_OK;
}

template <abi_t ABI>
void D3D11DeviceX<ABI>::GetGpuHardwareConfiguration(gfx::D3D11X_GPU_HARDWARE_CONFIGURATION *pGpuHardwareConfiguration)
{
    IMPLEMENT_STUB();
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DeviceX<ABI>
D3D11_DECLARE_ABI_TEMPLATES();