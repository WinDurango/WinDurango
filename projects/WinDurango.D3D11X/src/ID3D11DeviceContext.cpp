#include "ID3D11DeviceContext.h"
#include "ID3D11Device.h"
#include "ID3D11View.h"
#include "ID3D11Resource.h"
#include "ID3D11Shader.h"
#include "ID3D11State.h"
#include "d3d11.x.h"
#include "XG.h"
#include "ID3D11CommandList.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::QueryInterface(REFIID riid, void **ppvObject)
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

template <abi_t ABI> ULONG D3D11DeviceContextX<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11DeviceContextX<ABI>::Release()
{
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GetDevice(gfx::ID3D11Device<ABI>** ppDevice)
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
HRESULT D3D11DeviceContextX<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                                  xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11DeviceContext
//

template <abi_t ABI> 
void D3D11DeviceContextX<ABI>::CheckDirtyFlags()
{
    if constexpr (requires { this->m_ShaderUserDataManagerDraw; })
    {
        //if that's the case, it means that this->m_ShaderUserDataManagerDraw is likely corrupted
        //and must not be accessed, otherwise the game will likely crash. Shout out to Forza Horizon 2
        //for this dumbass crash.
        if (!D3D11X_HARDWARE_TO_TOPOLOGY_MAP.contains(this->m_ShaderUserDataManagerDraw.m_Topology))
        {
            return;
        }

        // Topology
        if (this->m_ShaderUserDataManagerDraw.m_DirtyFlags & 0x46)
        {
            this->m_ShaderUserDataManagerDraw.m_DirtyFlags &= ~0x46;
            int topology = D3D11X_HARDWARE_TO_TOPOLOGY_MAP.at(this->m_ShaderUserDataManagerDraw.m_Topology);
            m_pFunction->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
        }

        // Input Layout
        if (this->m_ShaderUserDataManagerDraw.m_DirtyFlags & 0x89)
        {
            this->m_ShaderUserDataManagerDraw.m_DirtyFlags &= ~0x89;
            IASetInputLayout(this->m_ShaderUserDataManagerDraw.m_pInputLayout);
        }

        // VS
        if (this->m_ShaderUserDataManagerDraw.m_DirtyFlags & 0x91)
        {
            this->m_ShaderUserDataManagerDraw.m_DirtyFlags &= ~0x91;
            VSSetShader(this->m_ShaderUserDataManagerDraw.m_pVs);
        }

        // PS
        if (this->m_ShaderUserDataManagerDraw.m_DirtyFlags & 0x121)
        {
            this->m_ShaderUserDataManagerDraw.m_DirtyFlags &= ~0x121;
            PSSetShader(this->m_ShaderUserDataManagerDraw.m_pPs);
        }
    }

    ExecuteBackgroundContexts();

    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    UpdateShaderResources(g_VSFastShaderResources<ABI>);
    UpdateShaderResources(g_PSFastShaderResources<ABI>);
    UpdateShaderResources(g_GSFastShaderResources<ABI>);
    UpdateShaderResources(g_HSFastShaderResources<ABI>);
    UpdateShaderResources(g_DSFastShaderResources<ABI>);
    UpdateShaderResources(g_CSFastShaderResources<ABI>);

    UpdateConstantBuffers(g_VSFastConstantBuffers<ABI>);
    UpdateConstantBuffers(g_PSFastConstantBuffers<ABI>);
    UpdateConstantBuffers(g_GSFastConstantBuffers<ABI>);
    UpdateConstantBuffers(g_HSFastConstantBuffers<ABI>);
    UpdateConstantBuffers(g_DSFastConstantBuffers<ABI>);
    UpdateConstantBuffers(g_CSFastConstantBuffers<ABI>);
}

template <abi_t ABI> 
void D3D11DeviceContextX<ABI>::ExecuteBackgroundContexts()
{
    std::lock_guard lock(m_BkgCtxLock);

    for (auto it = m_BkgContexts.begin(); it != m_BkgContexts.end();)
    {
        if ((*it)->ExecuteContext())
        {
            // This background context has finished executing, so we can remove
            // it from the array. If it starts executing again it will be re-added.
            it = m_BkgContexts.erase(it);
        }
        else
        {
            it++;
        }
    }
}

template <abi_t ABI> 
void D3D11DeviceContextX<ABI>::AddBackgroundContext(ID3D11BackgroundContext *pContext)
{
    std::lock_guard lock(m_BkgCtxLock);

    for (auto it : m_BkgContexts)
    {
        if (it == pContext)
        {
            // Context already exists
            return;
        }
    }

    m_BkgContexts.push_back(pContext);
}

template <abi_t ABI> 
void D3D11DeviceContextX<ABI>::RemoveBackgroundContext(ID3D11BackgroundContext *pContext)
{
    std::lock_guard lock(m_BkgCtxLock);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_VSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->VSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_PSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->PSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_PSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->PSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader)
{
    ID3D11PixelShader *Shader{};

    if (pPixelShader)
    {
        Shader = static_cast<D3D11PixelShader<ABI>*>(pPixelShader)->m_pFunction;
    }

    m_pFunction->PSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->PSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader)
{
    ID3D11VertexShader *Shader{};

    if (pVertexShader)
    {
        Shader = static_cast<D3D11VertexShader<ABI>*>(pVertexShader)->m_pFunction;
    }

    m_pFunction->VSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
    CheckDirtyFlags();
    m_pFunction->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation)
{
    CheckDirtyFlags();
    UINT StartIndexLocation = StartIndexLocationAndIndexCount & 0xFFFFFFFF;
    UINT IndexCount = (StartIndexLocationAndIndexCount >> 32) & 0xFFFFFFFF;
    m_pFunction->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::Draw(UINT VertexCount, UINT StartVertexLocation)
{
    CheckDirtyFlags();
    m_pFunction->Draw(VertexCount, StartVertexLocation);
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType,
                                      UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource)
{
    if (pResource)
    {
        D3D11_RESOURCE_DIMENSION Type{};
        pResource->GetType(&Type);

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            return m_pFunction->Map(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, Subresource, MapType,
                                    MapFlags, pMappedResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            return m_pFunction->Map(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, Subresource, MapType,
                                    MapFlags, pMappedResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            return m_pFunction->Map(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, Subresource, MapType,
                                    MapFlags, pMappedResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            return m_pFunction->Map(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, Subresource, MapType,
                                    MapFlags, pMappedResource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            return m_pFunction->Map(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, Subresource, MapType,
                                    MapFlags, pMappedResource);
        }
    }

    return E_INVALIDARG;
}

template <abi_t ABI> 
void D3D11DeviceContextX<ABI>::Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource)
{
    if (pResource)
    {
        D3D11_RESOURCE_DIMENSION Type{};
        pResource->GetType(&Type);

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            m_pFunction->Unmap(static_cast<D3D11Buffer<ABI> *>(pResource)->m_pFunction, Subresource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            m_pFunction->Unmap(static_cast<D3D11Texture1D<ABI> *>(pResource)->m_pFunction, Subresource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            m_pFunction->Unmap(static_cast<D3D11Texture2D<ABI> *>(pResource)->m_pFunction, Subresource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            m_pFunction->Unmap(static_cast<D3D11Texture3D<ABI> *>(pResource)->m_pFunction, Subresource);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            m_pFunction->Unmap(static_cast<D3D11Resource<ABI> *>(pResource)->m_pFunction, Subresource);
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_PSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->PSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::IASetInputLayout(gfx::ID3D11InputLayout<ABI> *pInputLayout)
{
    ID3D11InputLayout *InputLayout = nullptr;

    if (pInputLayout)
    {
        InputLayout = static_cast<D3D11InputLayout<ABI>*>(pInputLayout)->m_pFunction;
    }

    m_pFunction->IASetInputLayout(InputLayout);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers,
                                                  gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides,
                                                  UINT const *pOffsets)
{
    ID3D11Buffer *Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT]{};

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppVertexBuffers[i])
            Buffers[i] = 0;
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppVertexBuffers[i])->m_pFunction;
        }
    }

    m_pFunction->IASetVertexBuffers(StartSlot, NumBuffers, Buffers, pStrides, pOffsets);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetIndexBuffer(gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat,
                                                UINT Offset)
{
    ID3D11Buffer *Buffer{};

    if (pIndexBuffer)
    {
        Buffer = static_cast<D3D11Buffer<ABI> *>(pIndexBuffer)->m_pFunction;
    }

    m_pFunction->IASetIndexBuffer(Buffer, (DXGI_FORMAT)HardwareIndexFormat, Offset);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount,
                                                    UINT StartIndexLocation, INT BaseVertexLocation,
                                                    UINT StartInstanceLocation)
{
    CheckDirtyFlags();
    m_pFunction->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation,
                                      StartInstanceLocation);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance,
                                                    UINT64 BaseVertexLocationAndStartInstanceLocation,
                                                    UINT InstanceCount)
{
    CheckDirtyFlags();
    UINT StartInstanceLocation = (BaseVertexLocationAndStartInstanceLocation >> 32) & 0xFFFFFFFF;
    UINT BaseVertexLocation = BaseVertexLocationAndStartInstanceLocation & 0xFFFFFFFF;
    UINT IndexCountPerInstance = (StartIndexLocationAndIndexCountPerInstance >> 32) & 0xFFFFFFFF;
    UINT StartIndexLocation = StartIndexLocationAndIndexCountPerInstance & 0xFFFFFFFF;
    m_pFunction->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation,
                                      StartInstanceLocation);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation,
                                             UINT StartInstanceLocation)
{
    CheckDirtyFlags();
    m_pFunction->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawInstanced(UINT VertexCountPerInstance,
                                             UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount)
{
    CheckDirtyFlags();
    UINT StartInstanceLocation = (StartVertexLocationAndStartInstanceLocation >> 32) & 0xFFFFFFFF;
    UINT StartVertexLocation = StartVertexLocationAndStartInstanceLocation & 0xFFFFFFFF;
    m_pFunction->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer,
                                                UINT Offset)
{
    DXGI_FORMAT Format = HardwareIndexFormat != 0 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;

    ID3D11Buffer *Buffer{};

    if (pIndexBuffer)
    {
        Buffer = static_cast<D3D11Buffer<ABI> *>(pIndexBuffer)->m_pFunction;
    }

    m_pFunction->IASetIndexBuffer(Buffer, Format, Offset);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_GSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->GSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader)
{
    ID3D11GeometryShader *Shader{};

    if (pShader)
    {
        Shader = static_cast<D3D11GeometryShader<ABI>*>(pShader)->m_pFunction;
    }

    m_pFunction->GSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
    m_pFunction->IASetPrimitiveTopology(PrimitiveTopology);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_VSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->VSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_VSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->VSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->VSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::Begin(ID3D11Asynchronous* pAsync)
{
    m_pFunction->Begin(pAsync);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::End(ID3D11Asynchronous* pAsync)
{
    m_pFunction->End(pAsync);
}

template<abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags)
{
    return m_pFunction->GetData(pAsync, pData, DataSize, GetDataFlags);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue)
{
    m_pFunction->SetPredication(pPredicate, PredicateValue);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_GSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->GSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_GSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->GSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->GSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
                                                  gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView)
{
    ID3D11DepthStencilView *DepthStencilView{};
    ID3D11RenderTargetView *RenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};

    if (ppRTVs)
    {
        for (UINT i = 0; i < NumViews; i++)
        {
            if (!ppRTVs[i])
                RenderTargetViews[i] = 0;
            else
                RenderTargetViews[i] = static_cast<D3D11RenderTargetView<ABI> *>(ppRTVs[i])->m_pFunction;
        }
    }

    if (pDepthStencilView)
    {
        DepthStencilView = static_cast<D3D11DepthStencilView<ABI> *>(pDepthStencilView)->m_pFunction;
    }

    m_pFunction->OMSetRenderTargets(NumViews, RenderTargetViews, DepthStencilView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::OMSetRenderTargetsAndUnorderedAccessViews(
    UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView,
    UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
    UINT const *pUAVInitialCounts)
{
    ID3D11DepthStencilView *DepthStencilView{};
    ID3D11RenderTargetView *RenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
    ID3D11UnorderedAccessView *UnorderedAccessViews[D3D11_1_UAV_SLOT_COUNT]{};

    if (ppRTVs)
    {
        for (UINT i = 0; i < NumRTVs; i++)
        {
            if (!ppRTVs[i])
                RenderTargetViews[i] = 0;
            else
                RenderTargetViews[i] = static_cast<D3D11RenderTargetView<ABI> *>(ppRTVs[i])->m_pFunction;
        }
    }

    if (ppUnorderedAccessViews)
    {
        for (UINT i = 0; i < NumUAVs; i++)
        {
            if (!ppUnorderedAccessViews[i])
                UnorderedAccessViews[i] = 0;
            else
                UnorderedAccessViews[i] =
                    static_cast<D3D11UnorderedAccessView<ABI> *>(ppUnorderedAccessViews[i])->m_pFunction;
        }
    }

    if (pDepthStencilView)
    {
        DepthStencilView = static_cast<D3D11DepthStencilView<ABI> *>(pDepthStencilView)->m_pFunction;
    }

    m_pFunction->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, RenderTargetViews, DepthStencilView, UAVStartSlot,
                                                           NumUAVs, UnorderedAccessViews, pUAVInitialCounts);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4],
                                               UINT SampleMask)
{
    ID3D11BlendState *BlendState{};

    if (pBlendState)
    {
        BlendState = static_cast<D3D11BlendState<ABI> *>(pBlendState)->m_pFunction;
    }

    m_pFunction->OMSetBlendState(BlendState, BlendFactor, SampleMask);
}
template <abi_t ABI>
void D3D11DeviceContextX<ABI>::OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState,
                                                      UINT StencilRef)
{
    ID3D11DepthStencilState *State{};

    if (pDepthStencilState)
    {
        State = static_cast<D3D11DepthStencilState<ABI> *>(pDepthStencilState)->m_pFunction;
    }

    m_pFunction->OMSetDepthStencilState(State, StencilRef);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets,
                                            UINT const *pOffsets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawAuto()
{
    CheckDirtyFlags();
    m_pFunction->DrawAuto();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    CheckDirtyFlags();
    m_pFunction->DrawIndexedInstancedIndirect(static_cast<D3D11Buffer<ABI>*>(pBufferForArgs)->m_pFunction, AlignedByteOffsetForArgs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DrawInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    CheckDirtyFlags();
    m_pFunction->DrawInstancedIndirect(static_cast<D3D11Buffer<ABI>*>(pBufferForArgs)->m_pFunction, AlignedByteOffsetForArgs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
    CheckDirtyFlags();
    m_pFunction->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DispatchIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState)
{
    ID3D11RasterizerState *pState = nullptr;

    if (pRasterizerState)
    {
        pState = static_cast<D3D11RasterizerState<ABI>*>(pRasterizerState)->m_pFunction;
    }

    m_pFunction->RSSetState(pState);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports)
{
    m_pFunction->RSSetViewports(NumViewports, pViewports);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects)
{
    m_pFunction->RSSetScissorRects(NumRects, pRects);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                     UINT DstX, UINT DstY, UINT DstZ,
                                                     gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                     D3D11_BOX const *pSrcBox)
{
    if (pDstResource)
    {
        D3D11_RESOURCE_DIMENSION DstType{};
        D3D11_RESOURCE_DIMENSION SrcType{};
        pDstResource->GetType(&DstType);
        if (DstType == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopySubresourceRegion(
                    static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource, DstX, DstY, DstZ,
                    static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction, SrcSubresource, pSrcBox);
            }
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CopyResource(gfx::ID3D11Resource<ABI> *pDstResource,
                                            gfx::ID3D11Resource<ABI> *pSrcResource)
{
    if (pDstResource)
    {
        D3D11_RESOURCE_DIMENSION DstType{};
        D3D11_RESOURCE_DIMENSION SrcType{};
        pDstResource->GetType(&DstType);
        if (DstType == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopyResource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopyResource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopyResource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->CopyResource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Buffer<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture1D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture2D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->CopyResource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Texture3D<ABI> *>(pSrcResource)->m_pFunction);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->CopyResource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction,
                                          static_cast<D3D11Resource<ABI> *>(pSrcResource)->m_pFunction);
            }
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                 D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch,
                                                 UINT SrcDepthPitch)
{
    if (pDstResource && pSrcData)
    {
        D3D11_RESOURCE_DIMENSION Type{};
        pDstResource->GetType(&Type);

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            m_pFunction->UpdateSubresource(static_cast<D3D11Buffer<ABI> *>(pDstResource)->m_pFunction, DstSubresource,
                                           pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            m_pFunction->UpdateSubresource(static_cast<D3D11Texture1D<ABI> *>(pDstResource)->m_pFunction,
                                           DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            m_pFunction->UpdateSubresource(static_cast<D3D11Texture2D<ABI> *>(pDstResource)->m_pFunction,
                                           DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            m_pFunction->UpdateSubresource(static_cast<D3D11Texture3D<ABI> *>(pDstResource)->m_pFunction,
                                           DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            m_pFunction->UpdateSubresource(static_cast<D3D11Resource<ABI> *>(pDstResource)->m_pFunction, DstSubresource,
                                           pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                                                  gfx::ID3D11UnorderedAccessView<ABI> *pSrcView)
{
    if (pDstBuffer && pSrcView)
    {
        m_pFunction->CopyStructureCount(static_cast<D3D11Buffer<ABI>*>(pDstBuffer)->m_pFunction, DstAlignedByteOffset, static_cast<D3D11UnorderedAccessView<ABI>*>(pSrcView)->m_pFunction);
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView,
                                                     FLOAT const ColorRGBA[4])
{
    if (pRenderTargetView)
    {
        m_pFunction->ClearRenderTargetView(static_cast<D3D11RenderTargetView<ABI>*>(pRenderTargetView)->m_pFunction, ColorRGBA);
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                            UINT const Values[4])
{
    if (pUnorderedAccessView)
    {
        m_pFunction->ClearUnorderedAccessViewUint(static_cast<D3D11UnorderedAccessView<ABI> *>(pUnorderedAccessView)->m_pFunction, Values);
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                             FLOAT const Values[4])
{
    if (pUnorderedAccessView)
    {
        m_pFunction->ClearUnorderedAccessViewFloat(static_cast<D3D11UnorderedAccessView<ABI> *>(pUnorderedAccessView)->m_pFunction, Values);
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView,
                                                     UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
    if (pDepthStencilView)
    {
        m_pFunction->ClearDepthStencilView(static_cast<D3D11DepthStencilView<ABI>*>(pDepthStencilView)->m_pFunction, ClearFlags, Depth, Stencil);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GenerateMips(gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView)
{
    if (pShaderResourceView)
    {
        m_pFunction->GenerateMips(static_cast<D3D11ShaderResourceView<ABI>*>(pShaderResourceView)->m_pFunction);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::SetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource, FLOAT MinLOD)
{
    if (pResource)
    {
        D3D11_RESOURCE_DIMENSION Type{};
        pResource->GetType(&Type);

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            m_pFunction->SetResourceMinLOD(static_cast<D3D11Buffer<ABI>*>(pResource)->m_pFunction, MinLOD);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            m_pFunction->SetResourceMinLOD(static_cast<D3D11Texture1D<ABI>*>(pResource)->m_pFunction, MinLOD);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            m_pFunction->SetResourceMinLOD(static_cast<D3D11Texture2D<ABI>*>(pResource)->m_pFunction, MinLOD);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            m_pFunction->SetResourceMinLOD(static_cast<D3D11Texture3D<ABI>*>(pResource)->m_pFunction, MinLOD);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            m_pFunction->SetResourceMinLOD(static_cast<D3D11Resource<ABI>*>(pResource)->m_pFunction, MinLOD);
        }
    }
}

template<abi_t ABI>
FLOAT D3D11DeviceContextX<ABI>::GetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource)
{
    if (pResource)
    {
        D3D11_RESOURCE_DIMENSION Type{};
        pResource->GetType(&Type);

        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            return m_pFunction->GetResourceMinLOD(static_cast<D3D11Buffer<ABI>*>(pResource)->m_pFunction);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            return m_pFunction->GetResourceMinLOD(static_cast<D3D11Texture1D<ABI>*>(pResource)->m_pFunction);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            return m_pFunction->GetResourceMinLOD(static_cast<D3D11Texture2D<ABI>*>(pResource)->m_pFunction);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            return m_pFunction->GetResourceMinLOD(static_cast<D3D11Texture3D<ABI>*>(pResource)->m_pFunction);
        }
        else if (Type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            return m_pFunction->GetResourceMinLOD(static_cast<D3D11Resource<ABI>*>(pResource)->m_pFunction);
        }
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::ResolveSubresource(gfx::ID3D11Resource<ABI>* pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI>* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
    if (pDstResource)
    {
        D3D11_RESOURCE_DIMENSION DstType{};
        D3D11_RESOURCE_DIMENSION SrcType{};
        pDstResource->GetType(&DstType);
        if (DstType == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Buffer<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Buffer<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Buffer<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture1D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Buffer<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture2D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Buffer<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture3D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Buffer<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Resource<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture1D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Buffer<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture1D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture1D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture1D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture2D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture1D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture3D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture1D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Resource<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture2D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Buffer<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture2D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture1D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture2D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture2D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture2D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture3D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture2D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Resource<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture3D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Buffer<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture3D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture1D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture3D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture2D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture3D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture3D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Texture3D<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Resource<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
        }
        else if (DstType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            pSrcResource->GetType(&SrcType);
            if (SrcType == D3D11_RESOURCE_DIMENSION_BUFFER)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Resource<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Buffer<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Resource<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture1D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Resource<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture2D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Resource<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Texture3D<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
            else if (SrcType == D3D11_RESOURCE_DIMENSION_UNKNOWN)
            {
                m_pFunction->ResolveSubresource(static_cast<D3D11Resource<ABI>*>(pDstResource)->m_pFunction, DstSubresource, static_cast<D3D11Resource<ABI>*>(pSrcResource)->m_pFunction, SrcSubresource, Format);
            }
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ExecuteCommandList(gfx::ID3D11CommandList<ABI> *pCommandList, BOOL RestoreContextState)
{
    if (pCommandList)
    {
        D3D11CommandList<ABI> *CmdListWrapper = static_cast<D3D11CommandList<ABI> *>(pCommandList);
        if (!CmdListWrapper->m_IsDrawBundle)
        {
            ID3D11CommandList *CommandList = static_cast<D3D11CommandList<ABI> *>(pCommandList)->m_pFunction;
            m_pFunction->ExecuteCommandList(CommandList, RestoreContextState);
        }
        else
        {
            ExecuteDrawBundles(pCommandList);
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_HSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->HSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_HSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->HSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader)
{
    ID3D11HullShader *Shader{};

    if (pHullShader)
    {
        Shader = static_cast<D3D11HullShader<ABI>*>(pHullShader)->m_pFunction;
    }

    m_pFunction->HSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->HSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_HSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->HSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI> *>(ppShaderResourceViews[i])->m_pFunction;

            g_DSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->DSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_DSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->DSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader)
{
    ID3D11DomainShader *Shader{};

    if (pDomainShader)
    {
        Shader = static_cast<D3D11DomainShader<ABI> *>(pDomainShader)->m_pFunction;
    }

    m_pFunction->DSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->DSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_DSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->DSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetShaderResources(UINT StartSlot, UINT NumViews,
                                                    gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews)
{
    ID3D11ShaderResourceView *SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    UINT Slot = StartSlot;
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_CSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->CSSetShaderResources(StartSlot, NumViews, SRVs);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader)
{
    UINT NumViews = (PacketHeader >> 19) + 1;
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    for (UINT i = 0; i < NumViews; i++)
    {
        if (!ppShaderResourceViews[i])
        {
            SRVs[i] = nullptr;
        }
        else
        {
            SRVs[i] = static_cast<D3D11ShaderResourceView<ABI>*>(ppShaderResourceViews[i])->m_pFunction;

            g_CSFastShaderResources<ABI>[i] = ppShaderResourceViews[i];
        }
    }
    m_pFunction->CSSetShaderResources(StartSlot, NumViews, SRVs);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetUnorderedAccessViews(
    UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
    UINT const *pUAVInitialCounts)
{
 ID3D11UnorderedAccessView *UAVs[D3D11_1_UAV_SLOT_COUNT]{};
    for (UINT i = 0; i < NumUAVs; i++)
    {
        if (!ppUnorderedAccessViews[i])
            UAVs[i] = 0;
        else
        {
            UAVs[i] = static_cast<D3D11UnorderedAccessView<ABI>*>(ppUnorderedAccessViews[i])->m_pFunction;
        }
    }
    m_pFunction->CSSetUnorderedAccessViews(StartSlot, NumUAVs, UAVs, pUAVInitialCounts);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader)
{
    ID3D11ComputeShader *Shader{};

    if (pComputeShader)
    {
        Shader = static_cast<D3D11ComputeShader<ABI>*>(pComputeShader)->m_pFunction;
    }

    m_pFunction->CSSetShader(Shader, nullptr, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                             gfx::ID3D11SamplerState<ABI> *const *ppSamplers)
{
    ID3D11SamplerState *Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!ppSamplers[i])
            Samplers[i] = 0;
        else
            Samplers[i] = static_cast<D3D11SamplerState<ABI> *>(ppSamplers[i])->m_pFunction;
    }

    m_pFunction->CSSetSamplers(StartSlot, NumSamplers, Samplers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                                    gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers)
{
    ID3D11Buffer *Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!ppConstantBuffers[i])
        {
            Buffers[i] = 0;
        }
        else
        {
            Buffers[i] = static_cast<D3D11Buffer<ABI> *>(ppConstantBuffers[i])->m_pFunction;

            g_CSFastConstantBuffers<ABI>[StartSlot + i] = ppConstantBuffers[i];
        }
    }
    m_pFunction->CSSetConstantBuffers(StartSlot, NumBuffers, Buffers);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->VSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::PSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->PSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::PSGetShader(gfx::ID3D11PixelShader<ABI>** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->PSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::VSGetShader(gfx::ID3D11VertexShader<ABI>** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->PSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::IAGetInputLayout(gfx::ID3D11InputLayout<ABI>** ppInputLayout)
{
    ID3D11InputLayout *InputLayout = nullptr;
    m_pFunction->IAGetInputLayout(&InputLayout);

    if (InputLayout && ppInputLayout)
    {
        (*ppInputLayout) = new D3D11InputLayout<ABI>(InputLayout);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppVertexBuffers, UINT* pStrides, UINT* pOffsets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::IAGetIndexBuffer(gfx::ID3D11Buffer<ABI>** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->GSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GSGetShader(gfx::ID3D11GeometryShader<ABI>** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::VSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->VSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->VSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->GSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->GSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView)
{
    ID3D11DepthStencilView* pDepthStencilView{};
    ID3D11RenderTargetView* RenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
    m_pFunction->OMGetRenderTargets(NumViews, RenderTargetViews, &pDepthStencilView);

    if (ppRenderTargetViews)
    {
        for (UINT i = 0; i < NumViews; i++)
        {
            if (!RenderTargetViews[i])
                ppRenderTargetViews[i] = 0;
            else
                ppRenderTargetViews[i] = new D3D11RenderTargetView<ABI>(RenderTargetViews[i]);
        }
    }

    if (ppDepthStencilView && pDepthStencilView)
    {
        *ppDepthStencilView = new D3D11DepthStencilView<ABI>(pDepthStencilView);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::OMGetBlendState(gfx::ID3D11BlendState<ABI>** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask)
{
    if (ppBlendState)
    {
        ID3D11BlendState* BlendState{};
        m_pFunction->OMGetBlendState(&BlendState, BlendFactor, pSampleMask);

        if (BlendState)
        {
            *ppBlendState = new D3D11BlendState<ABI>(BlendState);
        }
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI>** ppDepthStencilState, UINT* pStencilRef)
{
    if (ppDepthStencilState)
    {
        ID3D11DepthStencilState* DepthStencilState{};
        m_pFunction->OMGetDepthStencilState(&DepthStencilState, pStencilRef);
        if (DepthStencilState)
        {
            *ppDepthStencilState = new D3D11DepthStencilState<ABI>(DepthStencilState);
        }
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppSOTargets)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::RSGetState(gfx::ID3D11RasterizerState<ABI>** ppRasterizerState)
{
    if (ppRasterizerState)
    {
        ID3D11RasterizerState* RS{};
        m_pFunction->RSGetState(&RS);

        if (RS)
        {
            *ppRasterizerState = new D3D11RasterizerState<ABI>(RS);
        }
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports)
{
    m_pFunction->RSGetViewports(pNumViewports, pViewports);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects)
{
    m_pFunction->RSGetScissorRects(pNumRects, pRects);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->HSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetShader(gfx::ID3D11HullShader<ABI>** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->HSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->HSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->DSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DSGetShader(gfx::ID3D11DomainShader<ABI>** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->DSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->DSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews)
{
    ID3D11ShaderResourceView* SRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
    m_pFunction->CSGetShaderResources(StartSlot, NumViews, SRVs);

    for (UINT i = 0; i < NumViews; i++)
    {
        if (!SRVs[i])
            ppShaderResourceViews[i] = 0;
        else
            ppShaderResourceViews[i] = new D3D11ShaderResourceView<ABI>(SRVs[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetShader(gfx::ID3D11ComputeShader<ABI>** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers)
{
    ID3D11SamplerState* Samplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT]{};
    m_pFunction->CSGetSamplers(StartSlot, NumSamplers, Samplers);

    for (UINT i = 0; i < NumSamplers; i++)
    {
        if (!Samplers[i])
            ppSamplers[i] = 0;
        else
            ppSamplers[i] = new D3D11SamplerState<ABI>(Samplers[i]);
    }
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers)
{
    ID3D11Buffer* Buffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT]{};
    m_pFunction->CSGetConstantBuffers(StartSlot, NumBuffers, Buffers);

    for (UINT i = 0; i < NumBuffers; i++)
    {
        if (!Buffers[i])
            ppConstantBuffers[i] = 0;
        else
            ppConstantBuffers[i] = new D3D11Buffer<ABI>(Buffers[i]);
    }
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::ClearState()
{
    m_pFunction->ClearState();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::Flush()
{
    m_pFunction->Flush();
}

template <abi_t ABI> D3D11_DEVICE_CONTEXT_TYPE D3D11DeviceContextX<ABI>::GetType()
{
    return m_pFunction->GetType();
}

template <abi_t ABI> UINT D3D11DeviceContextX<ABI>::GetContextFlags()
{
    return m_pFunction->GetContextFlags();
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::FinishCommandList(BOOL RestoreDeferredContextState, gfx::ID3D11CommandList<ABI> **ppCommandList)
{
    ID3D11CommandList *CommandList = nullptr;
    HRESULT hr = m_pFunction->FinishCommandList(RestoreDeferredContextState, &CommandList);

    if (CommandList)
    {
        (*ppCommandList) = new D3D11CommandList<ABI>(CommandList);
    }

    return hr;
}

//
// ID3D11DeviceContext1
//
template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CopySubresourceRegion1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                      UINT DstX, UINT DstY, UINT DstZ,
                                                      gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                      D3D11_BOX const *pSrcBox, UINT CopyFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::UpdateSubresource1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                  D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch,
                                                  UINT SrcDepthPitch, UINT CopyFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::DiscardResource(gfx::ID3D11Resource<ABI> *pResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::DiscardView(gfx::ID3D11View<ABI> *pResourceView)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers,
                                                     UINT const *pFirstConstant, UINT const *pNumConstants)
{
    //TODO: align offsets if needed
    CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
                                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant,
                                                     UINT *pNumConstants)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SwapDeviceContextState(ID3DDeviceContextState *pState,
                                                      ID3DDeviceContextState **ppPreviousState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearView(gfx::ID3D11View<ABI> *pView, FLOAT const Color[4], D3D11_RECT const *pRect,
                                         UINT NumRects)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DiscardView1(gfx::ID3D11View<ABI> *pResourceView, D3D11_RECT const *pRects,
                                            UINT NumRects)
{
    IMPLEMENT_STUB();
}

//
// ID3D11DeviceContext2
//
template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::UpdateTileMappings(
    gfx::ID3D11Resource<ABI> *pTiledResource, UINT NumTiledResourceRegions,
    D3D11_TILED_RESOURCE_COORDINATE const *pTiledResourceRegionStartCoordinates,
    D3D11_TILE_REGION_SIZE const *pTiledResourceRegionSizes, gfx::ID3D11Buffer<ABI> *pTilePool, UINT NumRanges,
    UINT const *pRangeFlags, UINT const *pTilePoolStartOffsets, UINT const *pRangeTileCounts, UINT Flags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::CopyTileMappings(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                                                   D3D11_TILED_RESOURCE_COORDINATE const *pDestRegionStartCoordinate,
                                                   gfx::ID3D11Resource<ABI> *pSourceTiledResource,
                                                   D3D11_TILED_RESOURCE_COORDINATE const *pSourceRegionStartCoordinate,
                                                   D3D11_TILE_REGION_SIZE const *pTileRegionSize, UINT Flags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CopyTiles(gfx::ID3D11Resource<ABI> *pTiledResource,
                                         D3D11_TILED_RESOURCE_COORDINATE const *pTileRegionStartCoordinate,
                                         D3D11_TILE_REGION_SIZE const *pTileRegionSize, gfx::ID3D11Buffer<ABI> *pBuffer,
                                         UINT64 BufferStartOffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::UpdateTiles(gfx::ID3D11Resource<ABI> *pDestTiledResource,
                                           D3D11_TILED_RESOURCE_COORDINATE const *pDestTileRegionStartCoordinate,
                                           D3D11_TILE_REGION_SIZE const *pDestTileRegionSize,
                                           void const *pSourceTileData, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::ResizeTilePool(gfx::ID3D11Buffer<ABI> *pTilePool, UINT64 NewSizeInBytes)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::TiledResourceBarrier(
    gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessBeforeBarrier,
    gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessAfterBarrier)
{
    IMPLEMENT_STUB();
}

//
// ID3D11DeviceContextX
//
template <abi_t ABI> INT D3D11DeviceContextX<ABI>::PIXBeginEvent(LPCWSTR Name)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> INT D3D11DeviceContextX<ABI>::PIXEndEvent()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::PIXSetMarker(LPCWSTR Name)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> BOOL D3D11DeviceContextX<ABI>::PIXGetStatus()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::PIXGpuEndCapture()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::StartCounters(gfx::ID3D11CounterSetX *pCounterSet)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SampleCounters(gfx::ID3D11CounterSampleX *pCounterSample)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::StopCounters()
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::GetCounterData(gfx::ID3D11CounterSampleX *pCounterSample,
                                                 gfx::D3D11X_COUNTER_DATA *pData,
                                                 UINT GetCounterDataFlags)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::FlushGpuCaches(gfx::ID3D11Resource<ABI> *pResource)
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::FlushGpuCacheRange(UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes)
{

}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::InsertWaitUntilIdle(UINT Flags)
{

}

template <abi_t ABI> UINT64 D3D11DeviceContextX<ABI>::InsertFence(UINT Flags)
{
    ExecuteBackgroundContexts();
    return (UINT64)&m_Fence;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::InsertWaitOnFence(UINT Flags, UINT64 Fence)
{
    if (Fence)
    {
        while (!*reinterpret_cast<BOOL volatile *>(Fence))
        {
            ExecuteBackgroundContexts();
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RemapConstantBufferInheritance(gfx::D3D11_STAGE Stage, UINT Slot,
                                                              gfx::D3D11_STAGE InheritStage,
                                                              UINT InheritSlot)
{
    gfx::ID3D11Buffer<ABI>* Buffer{};
    switch (InheritStage)
    {
    case gfx::D3D11_STAGE_VS:
        VSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    case gfx::D3D11_STAGE_PS:
        PSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    case gfx::D3D11_STAGE_GS:
        GSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    case gfx::D3D11_STAGE_HS:
        HSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    case gfx::D3D11_STAGE_CS:
        CSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    case gfx::D3D11_STAGE_DS:
        DSGetConstantBuffers(InheritSlot, 1, &Buffer);
        break;
    }

    UINT NumBuffers = Buffer != nullptr ? 1 : 0;

    switch (Stage)
    {
    case gfx::D3D11_STAGE_VS:
        VSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    case gfx::D3D11_STAGE_PS:
        PSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    case gfx::D3D11_STAGE_GS:
        GSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    case gfx::D3D11_STAGE_HS:
        HSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    case gfx::D3D11_STAGE_CS:
        CSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    case gfx::D3D11_STAGE_DS:
        DSSetConstantBuffers(Slot, NumBuffers, &Buffer);
        break;
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RemapShaderResourceInheritance(gfx::D3D11_STAGE Stage, UINT Slot,
                                                              gfx::D3D11_STAGE InheritStage,
                                                              UINT InheritSlot)
{
    gfx::ID3D11ShaderResourceView<ABI>* SRV{};
    switch (InheritStage)
    {
    case gfx::D3D11_STAGE_VS:
        VSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    case gfx::D3D11_STAGE_PS:
        PSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    case gfx::D3D11_STAGE_GS:
        GSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    case gfx::D3D11_STAGE_HS:
        HSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    case gfx::D3D11_STAGE_CS:
        CSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    case gfx::D3D11_STAGE_DS:
        DSGetShaderResources(InheritSlot, 1, &SRV);
        break;
    }

    UINT NumSRVs = SRV != nullptr ? 1 : 0;

    switch (Stage)
    {
    case gfx::D3D11_STAGE_VS:
        VSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    case gfx::D3D11_STAGE_PS:
        PSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    case gfx::D3D11_STAGE_GS:
        GSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    case gfx::D3D11_STAGE_HS:
        HSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    case gfx::D3D11_STAGE_CS:
        CSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    case gfx::D3D11_STAGE_DS:
        DSSetShaderResources(Slot, NumSRVs, &SRV);
        break;
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RemapSamplerInheritance(gfx::D3D11_STAGE Stage, UINT Slot, gfx::D3D11_STAGE InheritStage,
                                                       UINT InheritSlot)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    PSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    PSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::PSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    PSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    VSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    VSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::VSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    VSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    GSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    GSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::GSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    GSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    CSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    CSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::CSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    CSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    HSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    HSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::HSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    HSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer)
{
    DSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetFastShaderResource(UINT Slot,
                                                       gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView)
{
    DSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::DSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler)
{
    DSSetSamplers(Slot, 1, &pSampler);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetFastVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride)
{
    UINT Offset = 0;
    IASetVertexBuffers(Slot, 1, &pVertexBuffer, &Stride, &Offset);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetFastIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer)
{
    HardwareIndexFormat = HardwareIndexFormat != 0 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;

    IASetIndexBuffer(pIndexBuffer, HardwareIndexFormat, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    PSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    PSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    VSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    VSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    GSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    GSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    CSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    CSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    HSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    HSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer,
                                                            void *pBaseAddress)
{
    DSSetConstantBuffers(Slot, 1, &pConstantBuffer);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetPlacementShaderResource(UINT Slot,
                                                            gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView,
                                                            void *pBaseAddress)
{
    DSSetShaderResources(Slot, 1, &pShaderResourceView);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetPlacementVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer,
                                                          void *pBaseAddress, UINT Stride)
{
    UINT Offset = 0;
    IASetVertexBuffers(Slot, 1, &pVertexBuffer, &Stride, &Offset);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::IASetPlacementIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer,
                                                         void *pBaseAddress)
{
    HardwareIndexFormat = HardwareIndexFormat != 0 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;

    IASetIndexBuffer(pIndexBuffer, HardwareIndexFormat, 0);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetTessellationParameters(
    gfx::D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSGetLastUsedTessellationParameters(
    gfx::D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::CSEnableAutomaticGpuFlush(BOOL Enable)
{

}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::GpuSendPipelinedEvent(gfx::D3D11X_GPU_PIPELINED_EVENT Event)
{

}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::Suspend(UINT Flags)
{
    return S_OK;
}

template <abi_t ABI> HRESULT D3D11DeviceContextX<ABI>::Resume()
{
    return S_OK;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::BeginCommandListExecution(UINT Flags)
{

}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::EndCommandListExecution()
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetGraphicsShaderLimits(gfx::D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetComputeShaderLimits(gfx::D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetPredicationBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::OMSetDepthBounds(FLOAT min, FLOAT max)
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::OMSetDepthStencilStateX(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::OMSetSampleMask(UINT64 QuadSampleMask)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> UINT32 *D3D11DeviceContextX<ABI>::MakeCeSpace()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SetFastResources_Debug(UINT *pTableStart, UINT *pTableEnd)
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

template <abi_t ABI> void D3D11DeviceContextX<ABI>::BeginResourceBatch(void *pBuffer, UINT BufferSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> UINT D3D11DeviceContextX<ABI>::EndResourceBatch(UINT *pSizeNeeded)
{
    return 0;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SetFastResourcesFromBatch_Debug(void *pBatch, UINT Size)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSPlaceUnorderedAccessView(UINT Slot, gfx::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *const pDescriptor,
                                                          UINT64 Offset)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::WriteValueEndOfPipe(void* pDestination, UINT Value, UINT Flags)
{
    memcpy(pDestination, &Value, sizeof(Value));
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::CopyMemoryToMemory(void* pDstAddress, void* pSrcAddress, SIZE_T SizeBytes)
{
    memcpy(pDstAddress, pSrcAddress, SizeBytes);
}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::FillMemoryWithValue(void* pDstAddress, SIZE_T SizeBytes, UINT FillValue)
{
    memset(pDstAddress, FillValue, SizeBytes);
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::BeginProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::EndProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::StartThreadTrace(gfx::D3D11X_THREAD_TRACE_DESC const *pDesc,
                                                   void *pDstAddressShaderEngine0, void *pDstAddressShaderEngine1,
                                                   SIZE_T BufferSizeBytes)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::StopThreadTrace(void *pDstAddressTraceSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::InsertThreadTraceMarker(UINT Marker)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::IASetPrimitiveResetIndex(UINT ResetIndex)
{

}

template<abi_t ABI>
void D3D11DeviceContextX<ABI>::SetShaderResourceViewMinLOD(gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView, FLOAT MinLOD)
{
    gfx::ID3D11Resource<ABI>* resource{};
    pShaderResourceView->GetResource(&resource);

    if (resource)
    {
        D3D11_RESOURCE_DIMENSION type{};
        resource->GetType(&type);

        if (type == D3D11_RESOURCE_DIMENSION_BUFFER)
        {
            return SetResourceMinLOD(static_cast<gfx::ID3D11Buffer<ABI>*>(resource), MinLOD);
        }
        if (type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
        {
            return SetResourceMinLOD(static_cast<gfx::ID3D11Texture1D<ABI>*>(resource), MinLOD);
        }
        if (type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        {
            return SetResourceMinLOD(static_cast<gfx::ID3D11Texture2D<ABI>*>(resource), MinLOD);
        }
        if (type == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
        {
            return SetResourceMinLOD(static_cast<gfx::ID3D11Texture3D<ABI>*>(resource), MinLOD);
        }
        if (type == D3D11_RESOURCE_DIMENSION_UNKNOWN)
        {
            return SetResourceMinLOD(resource, MinLOD);
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::InsertWaitOnPresent(UINT Flags, gfx::ID3D11Resource<ABI> *pBackBuffer)
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ClearRenderTargetViewX(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, UINT Flags,
                                                      FLOAT const ColorRGBA[4])
{
    if (pRenderTargetView)
    {
        m_pFunction->ClearRenderTargetView(static_cast<D3D11RenderTargetView<ABI>*>(pRenderTargetView)->m_pFunction, ColorRGBA);
    }
}

template <abi_t ABI> UINT D3D11DeviceContextX<ABI>::GetResourceCompression(gfx::ID3D11Resource<ABI> *pResource)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
UINT D3D11DeviceContextX<ABI>::GetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource)
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DecompressResource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                                  gfx::D3D11X_POINT const *pDstPoint,
                                                  gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                                  gfx::D3D11X_RECT const *pSrcRect,
                                                  DXGI_FORMAT DecompressFormat, UINT DecompressFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DecompressResourceX(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDstResource, UINT DstSubresource,
                                                   gfx::D3D11X_POINT const *pDstPoint,
                                                   gfx::D3D11X_DESCRIPTOR_RESOURCE *pSrcResource, UINT SrcSubresource,
                                                   gfx::D3D11X_RECT const *pSrcRect,
                                                   gfx::D3D11X_FORMAT DecompressFormat,
                                                   UINT DecompressFlags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::GSSetParameters(gfx::D3D11X_GS_PARAMETERS const *pGsParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::GSGetLastUsedParameters(gfx::D3D11X_GS_PARAMETERS *pGsParameters)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::MultiDrawIndexedInstancedIndirect(UINT PrimitiveCount,
                                                                 gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                                 UINT AlignedByteOffsetForArgs,
                                                                 UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::MultiDrawInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                          UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs,
                                                          UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::MultiDrawIndexedInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                                                     UINT AlignedByteOffsetForPrimitiveCount,
                                                                     gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                                     UINT AlignedByteOffsetForArgs,
                                                                     UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::MultiDrawInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount,
                                                              UINT AlignedByteOffsetForPrimitiveCount,
                                                              gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                              UINT AlignedByteOffsetForArgs,
                                                              UINT StrideByteOffsetForArgs, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11DeviceContextX<ABI>::RSGetMSAASettingsForQuality(gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS *pMSAASCSettings,
                                                              gfx::D3D11X_MSAA_EQAA_SETTINGS *pEQAASettings,
                                                              gfx::D3D11X_MSAA_SAMPLE_PRIORITIES *pCentroidPriorities,
                                                              gfx::D3D11X_MSAA_SAMPLE_POSITIONS *pSamplePositions,
                                                              UINT LogSampleCount, UINT SampleQuality)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RSSetScanConverterMSAASettings(
    gfx::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS const *pMSAASCSettings)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RSSetEQAASettings(gfx::D3D11X_MSAA_EQAA_SETTINGS const *pEQAASettings)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::RSSetSamplePositions(gfx::D3D11X_MSAA_SAMPLE_PRIORITIES const *pSamplesPriorities,
                                                    gfx::D3D11X_MSAA_SAMPLE_POSITIONS const *pSamplePositions)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetResourceCompression(gfx::ID3D11Resource<ABI> *pResource, UINT Compression)
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource,
                                                       UINT Compression)
{

}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetGDSRange(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::WriteGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
                                        UINT const *pCounterValues, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ReadGDS(gfx::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
                                       UINT *pCounterValues, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::VSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::HSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::DSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::GSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::PSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::InsertWaitOnMemory(void const *pAddress, UINT Flags,
                                                  D3D11_COMPARISON_FUNC ComparisonFunction, UINT ReferenceValue,
                                                  UINT Mask)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::WriteTimestampToMemory(void *pDstAddress)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::StoreConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes,
                                                UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::LoadConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes,
                                               UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::WriteQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags,
                                          gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT StrideInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::ResetQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ConfigureQuery(D3D11_QUERY QueryType, void const *pConfiguration, UINT ConfigurationSize)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetShaderUserData(gfx::D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters,
                                                 UINT const *pData)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SetPixelShaderDepthForceZOrder(BOOL ForceOrder)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetPredicationFromQuery(D3D11_QUERY QueryType, gfx::ID3D11Buffer<ABI> *pBuffer,
                                                       UINT OffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::SetBorderColorPalette(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::WriteValueEndOfPipe64(void *pDestination, UINT64 Value, UINT Flags)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::InsertWaitOnMemory64(void const *pAddress, UINT Flags,
                                                    D3D11_COMPARISON_FUNC ComparisonFunction, UINT64 ReferenceValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::LoadConstantRamImmediate(UINT Flags, void const *pBuffer, UINT CeRamOffsetInBytes,
                                                        UINT SizeInBytes)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SetScreenExtentsQuery(UINT Value)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::CollectScreenExtents(UINT Flags, UINT AddressCount, UINT64 const *pDestinationAddresses,
                                                    USHORT ZMin, USHORT ZMax)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::FillResourceWithValue(gfx::ID3D11Resource<ABI> *pDstResource, UINT FillValue)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> void D3D11DeviceContextX<ABI>::SetDrawBalancing(UINT BalancingMode, UINT Flags)
{
    IMPLEMENT_STUB();
}


template <abi_t ABI>
void D3D11DeviceContextX<ABI>::UpdateShaderResources(gfx::ID3D11ShaderResourceView<ABI>** ppSRVs)
{
    for (UINT i = 0; i < D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        __try
        {
            if (ppSRVs[i])
            {
                gfx::ID3D11ShaderResourceView<ABI> *pSRV = ppSRVs[i];
                if (pSRV)
                {
                    if (pSRV->m_pAllocationStart)
                    {
                        gfx::ID3D11Resource<ABI> *pResource{};
                        pSRV->GetResource(&pResource);
                        if (pResource)
                        {
                            D3D11_RESOURCE_DIMENSION Type{};
                            pResource->GetType(&Type);

                            if (Type == D3D11_RESOURCE_DIMENSION_BUFFER)
                            {
                                D3D11_BUFFER_DESC Desc{};
                                gfx::ID3D11Buffer<ABI> *pBuffer = static_cast<gfx::ID3D11Buffer<ABI> *>(pResource);
                                if (static_cast<D3D11Buffer<ABI> *>(pBuffer)->m_IsDirty == true)
                                {
                                    pBuffer->GetDesc(&Desc);

                                    if (Desc.Usage == D3D11_USAGE_DEFAULT)
                                    {
                                        UpdateSubresource(pBuffer, 0, nullptr, pSRV->m_pAllocationStart, 0, 0);
                                        static_cast<D3D11Buffer<ABI> *>(pBuffer)->m_IsDirty = false;

                                        DWORD OldProtect = 0;
                                        VirtualProtect(pSRV->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
                                    }
                                    else
                                    {
                                        D3D11_MAPPED_SUBRESOURCE Mapped{};
                                        HRESULT hr = Map(pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Mapped);
                                        if (SUCCEEDED(hr))
                                        {
                                            memcpy(Mapped.pData, pSRV->m_pAllocationStart, Mapped.DepthPitch);
                                            Unmap(pBuffer, 0);
                                            static_cast<D3D11Buffer<ABI> *>(pBuffer)->m_IsDirty = false;

                                            DWORD OldProtect = 0;
                                            VirtualProtect(pSRV->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
                                        }
                                    }
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
                            {
                                gfx::ID3D11Texture2D<ABI> *pTexture =
                                    static_cast<gfx::ID3D11Texture2D<ABI> *>(pResource);
                                if (static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_IsDirty == true)
                                {
                                    D3D11_TEXTURE2D_DESC Desc{};
                                    pTexture->GetDesc(&Desc);

                                    UINT RowPitch = static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_RowPitch;
                                    UINT SlicePitch = static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_SlicePitch;

                                    BYTE *DetiledData = new BYTE[SlicePitch];
                                    HRESULT hr = DetileTexture2D(
                                        static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_TileModeIndex, &Desc,
                                        pSRV->m_pAllocationStart, &DetiledData, RowPitch, SlicePitch);
                                    if (SUCCEEDED(hr) && Desc.Usage == D3D11_USAGE_DEFAULT)
                                    {
                                        UpdateSubresource(pTexture, 0, nullptr, DetiledData, RowPitch, SlicePitch);
                                        delete[] DetiledData;
                                        static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_IsDirty = false;

                                        DWORD OldProtect = 0;
                                        VirtualProtect(pSRV->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
                                    }
                                    else if (SUCCEEDED(hr))
                                    {
                                        D3D11_MAPPED_SUBRESOURCE Mapped{};
                                        hr = Map(pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &Mapped);
                                        if (SUCCEEDED(hr))
                                        {
                                            memcpy(Mapped.pData, DetiledData, SlicePitch);
                                            Unmap(pTexture, 0);
                                            delete[] DetiledData;
                                            static_cast<D3D11Texture2D<ABI> *>(pTexture)->m_IsDirty = false;

                                            DWORD OldProtect = 0;
                                            VirtualProtect(pSRV->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
                                        }
                                    }
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            continue;
        }
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::UpdateConstantBuffers(gfx::ID3D11Buffer<ABI>** ppBuffers)
{
    for (UINT i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        auto* pBuffer = ppBuffers[i];
        if (!pBuffer) continue;

        auto* BufferWrapper = static_cast<D3D11Buffer<ABI>*>(pBuffer);
        if (!pBuffer->m_pAllocationStart || !BufferWrapper->m_IsDirty)
            continue;

        D3D11_BUFFER_DESC Desc{};
        pBuffer->GetDesc(&Desc);
        if (Desc.Usage == D3D11_USAGE_DEFAULT)
        {
            UpdateSubresource(pBuffer, 0, nullptr, pBuffer->m_pAllocationStart, 0, 0);
            DWORD OldProtect = 0;
            VirtualProtect(pBuffer->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
        }
        else
        {
            D3D11_MAPPED_SUBRESOURCE mapped{};
            if (SUCCEEDED(Map(pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
            {
                memcpy(mapped.pData, pBuffer->m_pAllocationStart, Desc.ByteWidth);
                Unmap(pBuffer, 0);
                DWORD OldProtect = 0;
                VirtualProtect(pBuffer->m_pAllocationStart, 1, PAGE_READONLY, &OldProtect);
            }
        }

        BufferWrapper->m_IsDirty = false;
    }
}

template <abi_t ABI>
void D3D11DeviceContextX<ABI>::ExecuteDrawBundles(gfx::ID3D11CommandList<ABI> *pCommandList)
{
    if (!pCommandList)
        return;

    D3D11CommandList<ABI>* Bundle = static_cast<D3D11CommandList<ABI>*>(pCommandList);
    for (UINT i = 0; i < Bundle->m_Commands.size(); ++i)
    {
        const DrawBundlesCommand<ABI>& cmd = Bundle->m_Commands[i];
        switch (cmd.m_CommandType)
        {
        case DrawBundlesCommandType::VSSetShaderResourcesPC:
            VSSetShaderResources(cmd.VSSetShaderResourcesPC.StartSlot, cmd.VSSetShaderResourcesPC.NumViews, cmd.VSSetShaderResourcesPC.ppShaderResourceViews);
            break;
        case DrawBundlesCommandType::PSSetShaderResourcesPC:
            PSSetShaderResources(cmd.PSSetShaderResourcesPC.StartSlot, cmd.PSSetShaderResourcesPC.NumViews, cmd.PSSetShaderResourcesPC.ppShaderResourceViews);
            break;
        case DrawBundlesCommandType::ClearState:
            ClearState();
            break;
        case DrawBundlesCommandType::DrawIndexedXbox:
            DrawIndexed(cmd.DrawIndexedXbox.StartIndexLocationAndIndexCount, cmd.DrawIndexedXbox.BaseVertexLocation);
            break;
        case DrawBundlesCommandType::DrawIndexedInstancedXbox:
            DrawIndexedInstanced(cmd.DrawIndexedInstancedXbox.StartIndexLocationAndIndexCountPerInstance, cmd.DrawIndexedInstancedXbox.BaseVertexLocationAndStartInstanceLocation, cmd.DrawIndexedInstancedXbox.InstanceCount);
            break;
        case DrawBundlesCommandType::DrawIndexedInstancedIndirect:
            DrawIndexedInstancedIndirect(cmd.DrawIndexedInstancedIndirect.pBufferForArgs, cmd.DrawIndexedInstancedIndirect.AlignedByteOffsetForArgs);
            break;
        case DrawBundlesCommandType::DrawInstancedIndirect:
            DrawInstancedIndirect(cmd.DrawInstancedIndirect.pBufferForArgs, cmd.DrawInstancedIndirect.AlignedByteOffsetForArgs);
            break;
        case DrawBundlesCommandType::DSSetShader:
            DSSetShader(cmd.DSSetShader.pDomainShader);
            break;
        case DrawBundlesCommandType::HSSetShader:
            HSSetShader(cmd.HSSetShader.pHullShader);
            break;
        case DrawBundlesCommandType::GSSetShader:
            GSSetShader(cmd.GSSetShader.pShader);
            break;
        case DrawBundlesCommandType::VSSetShader:
            VSSetShader(cmd.VSSetShader.pVertexShader);
            break;
        case DrawBundlesCommandType::PSSetShader:
            PSSetShader(cmd.PSSetShader.pPixelShader);
            break;
        case DrawBundlesCommandType::CSSetShader:
            CSSetShader(cmd.CSSetShader.pComputeShader);
            break;
        case DrawBundlesCommandType::IASetIndexBufferXbox:
            IASetIndexBuffer(cmd.IASetIndexBufferXbox.HardwareIndexFormat, cmd.IASetIndexBufferXbox.pIndexBuffer, cmd.IASetIndexBufferXbox.Offset);
            break;
        case DrawBundlesCommandType::IASetIndexBufferPC:
            IASetIndexBuffer(cmd.IASetIndexBufferPC.pIndexBuffer, cmd.IASetIndexBufferPC.HardwareIndexFormat, cmd.IASetIndexBufferPC.Offset);
            break;
        case DrawBundlesCommandType::IASetVertexBuffers:
            IASetVertexBuffers(cmd.IASetVertexBuffers.StartSlot, cmd.IASetVertexBuffers.NumBuffers, cmd.IASetVertexBuffers.ppVertexBuffers, cmd.IASetVertexBuffers.pStrides, cmd.IASetVertexBuffers.pOffsets);
            break;
        case DrawBundlesCommandType::RemapConstantBufferInheritance:
            RemapConstantBufferInheritance(cmd.RemapConstantBufferInheritance.Stage, cmd.RemapConstantBufferInheritance.Slot, cmd.RemapConstantBufferInheritance.InheritStage, cmd.RemapConstantBufferInheritance.InheritSlot);
            break;
        case DrawBundlesCommandType::RemapShaderResourceInheritance:
            RemapShaderResourceInheritance(cmd.RemapShaderResourceInheritance.Stage, cmd.RemapShaderResourceInheritance.Slot, cmd.RemapShaderResourceInheritance.InheritStage, cmd.RemapShaderResourceInheritance.InheritSlot);
            break;
        case DrawBundlesCommandType::PSSetFastShaderResource:
            PSSetFastShaderResource(cmd.PSSetFastShaderResource.Slot, cmd.PSSetFastShaderResource.pShaderResourceView);
            break;
        case DrawBundlesCommandType::VSSetFastShaderResource:
            VSSetFastShaderResource(cmd.VSSetFastShaderResource.Slot, cmd.VSSetFastShaderResource.pShaderResourceView);
            break;
        case DrawBundlesCommandType::PSSetFastConstantBuffer:
            PSSetFastConstantBuffer(cmd.PSSetFastConstantBuffer.Slot, cmd.PSSetFastConstantBuffer.pConstantBuffer);
            break;
        case DrawBundlesCommandType::VSSetFastConstantBuffer:
            VSSetFastConstantBuffer(cmd.VSSetFastConstantBuffer.Slot, cmd.VSSetFastConstantBuffer.pConstantBuffer);
            break;
        case DrawBundlesCommandType::PSSetFastSampler:
            PSSetFastSampler(cmd.PSSetFastSampler.Slot, cmd.PSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::VSSetFastSampler:
            VSSetFastSampler(cmd.VSSetFastSampler.Slot, cmd.VSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::HSSetFastSampler:
            HSSetFastSampler(cmd.HSSetFastSampler.Slot, cmd.HSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::GSSetFastSampler:
            GSSetFastSampler(cmd.GSSetFastSampler.Slot, cmd.GSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::CSSetFastSampler:
            CSSetFastSampler(cmd.CSSetFastSampler.Slot, cmd.CSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::DSSetFastSampler:
            DSSetFastSampler(cmd.DSSetFastSampler.Slot, cmd.DSSetFastSampler.pSampler);
            break;
        case DrawBundlesCommandType::IASetInputLayout:
            IASetInputLayout(cmd.IASetInputLayout.pInputLayout);
            break;
        case DrawBundlesCommandType::IASetPrimitiveTopology:
            IASetPrimitiveTopology(cmd.IASetPrimitiveTopology.PrimitiveTopology);
            break;
        case DrawBundlesCommandType::DrawIndexedPC:
            DrawIndexed(cmd.DrawIndexedPC.IndexCount, cmd.DrawIndexedPC.StartIndexLocation, cmd.DrawIndexedPC.BaseVertexLocation);
            break;
        case DrawBundlesCommandType::DrawIndexedInstancedPC:
            DrawIndexedInstanced(cmd.DrawIndexedInstancedPC.IndexCountPerInstance, cmd.DrawIndexedInstancedPC.InstanceCount,
            cmd.DrawIndexedInstancedPC.StartIndexLocation, cmd.DrawIndexedInstancedPC.BaseVertexLocation,
            cmd.DrawIndexedInstancedPC.StartInstanceLocation);
            break;
        case DrawBundlesCommandType::Draw:
            Draw(cmd.Draw.VertexCount, cmd.Draw.StartVertexLocation);
            break;
        default:
            MessageBoxA(NULL, "Unknown Bundle Context command!", "Error!", MB_OK);
            break;
        }
    }
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DeviceContextX<ABI>
D3D11_DECLARE_ABI_TEMPLATES();