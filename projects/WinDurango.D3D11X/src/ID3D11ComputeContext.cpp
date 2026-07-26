#include "ID3D11ComputeContext.h"

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::QueryInterface(REFIID riid, void ** ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
ULONG D3D11ComputeContextX<ABI>::AddRef()
{
    return InterlockedIncrement(&this->m_RefCount);
}

template<abi_t ABI>
ULONG D3D11ComputeContextX<ABI>::Release()
{
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

template <abi_t ABI> 
void D3D11ComputeContextX<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
gfx::D3D11_COMPUTE_CONTEXT_TYPE D3D11ComputeContextX<ABI>::GetType()
{
    IMPLEMENT_STUB();
    return gfx::D3D11_COMPUTE_CONTEXT_TYPE::D3D11_COMPUTE_CONTEXT_DEFERRED;
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::Dispatch(uint32_t a1, uint32_t a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::DispatchIndirect(gfx::ID3D11Buffer<ABI>* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetShaderResources(uint32_t a1, uint32_t a2, gfx::ID3D11ShaderResourceView<ABI>** a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetUnorderedAccessViews(uint32_t a1, uint32_t a2, gfx::ID3D11UnorderedAccessView<ABI>** a3, const uint32_t* a4)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetShader(gfx::ID3D11ComputeShader<ABI>* a1, ID3D11ClassInstance** a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetSamplers(uint32_t a1, uint32_t a2, gfx::ID3D11SamplerState<ABI>** a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetConstantBuffers(uint32_t a1, uint32_t a2, gfx::ID3D11Buffer<ABI>** a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetConstantBuffers1(uint32_t a1, uint32_t a2, gfx::ID3D11Buffer<ABI>** a3, const uint32_t* a4, const uint32_t* a5)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetPlacementConstantBuffer(uint32_t a1, gfx::ID3D11Buffer<ABI>* a2, void* a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetPlacementShaderResource(uint32_t a1, gfx::ID3D11ShaderResourceView<ABI>* a2, void* a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetPlacementUnorderedAccessView(uint32_t a1, gfx::ID3D11UnorderedAccessView<ABI>* a2, uint32_t a3, void* a4)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CopyResource(gfx::ID3D11Resource<ABI>* a1, gfx::ID3D11Resource<ABI>* a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CopySubresourceRegion(gfx::ID3D11Resource<ABI>* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, gfx::ID3D11Resource<ABI>* a6, uint32_t a7, const D3D11_BOX* a8, uint32_t a9)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI>* pUAV, const uint32_t* a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI>* pUAV, const float* a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
uint64_t D3D11ComputeContextX<ABI>::InsertFence(uint32_t a1)
{
    ComputeCommands<ABI> Command{};
    Command.m_ComputeCommandType = ComputeCommands<ABI>::ComputeCommandType::ComputeInsertFence;
    Command.ComputeInsertFence.Flags = a1;
    m_ComputeCommandQueue.push_back(Command);

    if (ComputeFenceIndex >= 1024)
    {
        ComputeFenceIndex = 0;
    }

    UINT FenceIndex = ComputeFenceIndex;
    ComputeFences[FenceIndex] = TRUE;
    ComputeFenceIndex++;
    Command.ComputeInsertFence.Fence = (UINT64)&ComputeFences[FenceIndex];
    m_ComputeCommandQueue.push_back(Command);

    return (UINT64)&ComputeFences[FenceIndex];
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::InsertWaitOnFence(uint32_t a1, uint64_t a2)
{
    ComputeCommands<ABI> Command{};
    Command.m_ComputeCommandType = ComputeCommands<ABI>::ComputeCommandType::ComputeInsertWaitOnFence;
    Command.ComputeInsertWaitOnFence.Flags = a1;
    Command.ComputeInsertWaitOnFence.Fence = a2;
    m_ComputeCommandQueue.push_back(Command);
}

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::Flush()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::ClearState()
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CopyMemoryToMemory(void* a1, void* a2, uint64_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::FillMemoryWithValue(void* a1, uint64_t a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::FillResourceWithValue(gfx::ID3D11Resource<ABI>* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::WriteTimestampToMemory(void* a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::PIXBeginEvent(const wchar_t* a1)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::PIXBeginEventEx(const void* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::PIXEndEvent()
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::PIXSetMarker(const wchar_t* a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::PIXSetMarkerEx(const void* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::GpuSendPipelinedEvent(gfx::D3D11X_GPU_PIPELINED_EVENT a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::SetComputeShaderLimits(const gfx::D3D11X_COMPUTE_SHADER_LIMITS* a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::FlushGpuCachesTopOfPipe(uint32_t a1)
{

}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::FlushGpuCachesBottomOfPipe(uint32_t a1)
{

}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::SetDispatchFlags(uint32_t a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
uint32_t D3D11ComputeContextX<ABI>::GetDispatchFlags()
{
    return 0;
}

template<abi_t ABI>
HRESULT D3D11ComputeContextX<ABI>::SetPriority(gfx::D3D11X_COMPUTE_CONTEXT_PRIORITY a1)
{
    return S_OK;
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::WriteValueBottomOfPipe(void* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::InsertThreadTraceMarker(uint32_t a1)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::BeginResourceBatch(void* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
uint32_t D3D11ComputeContextX<ABI>::EndResourceBatch(uint32_t* a1)
{
    return 0;
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::SetFastResourcesFromBatch(void* a1, uint32_t a2)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::SetGDSRange(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::WriteGDS(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3, const uint32_t* a4, uint32_t a5)
{

}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::ReadGDS(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3, uint32_t* a4, uint32_t a5)
{

}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::InsertWaitOnMemory(const void* a1, uint32_t a2, D3D11_COMPARISON_FUNC a3, uint32_t a4, uint32_t a5)
{

}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::CSSetShaderUserData(uint32_t a1, uint32_t a2, const uint32_t* a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::WriteValueEndOfPipe64(void* a1, uint64_t a2, uint32_t a3)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::InsertWaitOnMemory64(const void* a1, uint32_t a2, D3D11_COMPARISON_FUNC a3, uint64_t a4)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
void D3D11ComputeContextX<ABI>::InsertWaitOnPresent(uint32_t a1, gfx::ID3D11Resource<ABI>* a2)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI>
BOOL D3D11ComputeContextX<ABI>::ExecuteContext()
{
    IMPLEMENT_STUB();
    return FALSE;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ComputeContextX<ABI>
D3D11_DECLARE_ABI_TEMPLATES();