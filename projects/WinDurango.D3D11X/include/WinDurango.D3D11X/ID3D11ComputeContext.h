#pragma once
#include "d3d11_x.g.h"
#include "ID3D11DeviceContext.h"

template<abi_t ABI>
class D3D11ComputeContextX : public gfx::ID3D11ComputeContextX<ABI>, ID3D11BackgroundContext
{
public:
    D3D11DeviceContextX<ABI> *m_pImmediateContext;

    D3D11ComputeContextX()
    {
        if (this->m_RefCount != 0)
            this->m_RefCount = 0;
        AddRef();
        m_pImmediateContext = new D3D11DeviceContextX<ABI>();
        std::memcpy(&this->m_Function, *(void***)this, sizeof(this->m_Function));
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
        return S_OK;
    }

    //
    // ID3D11ComputeContextX
    //
    gfx::D3D11_COMPUTE_CONTEXT_TYPE GetType();
    void Dispatch(uint32_t a1, uint32_t a2, uint32_t a3);
    void DispatchIndirect(gfx::ID3D11Buffer<ABI>* a1, uint32_t a2);
    void CSSetShaderResources(uint32_t a1, uint32_t a2, gfx::ID3D11ShaderResourceView<ABI>** a3);
    void CSSetUnorderedAccessViews(uint32_t a1, uint32_t a2, gfx::ID3D11UnorderedAccessView<ABI>** a3, const uint32_t* a4);
    void CSSetShader(gfx::ID3D11ComputeShader<ABI>* a1, ID3D11ClassInstance** a2, uint32_t a3);
    void CSSetSamplers(uint32_t a1, uint32_t a2, gfx::ID3D11SamplerState<ABI>** a3);
    void CSSetConstantBuffers(uint32_t a1, uint32_t a2, gfx::ID3D11Buffer<ABI>** a3);
    void CSSetConstantBuffers1(uint32_t a1, uint32_t a2, gfx::ID3D11Buffer<ABI>** a3, const uint32_t* a4, const uint32_t* a5);
    void CSSetPlacementConstantBuffer(uint32_t a1, gfx::ID3D11Buffer<ABI>* a2, void* a3);
    void CSSetPlacementShaderResource(uint32_t a1, gfx::ID3D11ShaderResourceView<ABI>* a2, void* a3);
    void CSSetPlacementUnorderedAccessView(uint32_t a1, gfx::ID3D11UnorderedAccessView<ABI>* a2, uint32_t a3, void* a4);
    void CopyResource(gfx::ID3D11Resource<ABI>* a1, gfx::ID3D11Resource<ABI>* a2, uint32_t a3);
    void CopySubresourceRegion(gfx::ID3D11Resource<ABI>* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, gfx::ID3D11Resource<ABI>* a6, uint32_t a7, const D3D11_BOX* a8, uint32_t a9);
    void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI>* pUAV, const uint32_t* a2);
    void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI>* pUAV, const float* a2);
    uint64_t InsertFence(uint32_t a1);
    void InsertWaitOnFence(uint32_t a1, uint64_t a2);
    HRESULT Flush();
    void ClearState();
    void CopyMemoryToMemory(void* a1, void* a2, uint64_t a3);
    void FillMemoryWithValue(void* a1, uint64_t a2, uint32_t a3);
    void FillResourceWithValue(gfx::ID3D11Resource<ABI>* a1, uint32_t a2);
    void WriteTimestampToMemory(void* a1);
    HRESULT PIXBeginEvent(const wchar_t* a1);
    HRESULT PIXBeginEventEx(const void* a1, uint32_t a2);
    HRESULT PIXEndEvent();
    void PIXSetMarker(const wchar_t* a1);
    void PIXSetMarkerEx(const void* a1, uint32_t a2);
    void GpuSendPipelinedEvent(gfx::D3D11X_GPU_PIPELINED_EVENT a1);
    void SetComputeShaderLimits(const gfx::D3D11X_COMPUTE_SHADER_LIMITS* a1);
    void FlushGpuCachesTopOfPipe(uint32_t a1);
    void FlushGpuCachesBottomOfPipe(uint32_t a1);
    void SetDispatchFlags(uint32_t a1);
    uint32_t GetDispatchFlags();
    HRESULT SetPriority(gfx::D3D11X_COMPUTE_CONTEXT_PRIORITY a1);
    void WriteValueBottomOfPipe(void*, uint32_t a1);
    void InsertThreadTraceMarker(uint32_t a1);
    void BeginResourceBatch(void*, uint32_t a1);
    uint32_t EndResourceBatch(uint32_t* a1);
    void SetFastResourcesFromBatch(void* a1, uint32_t a2);
    void SetGDSRange(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3);
    void WriteGDS(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3, const uint32_t* a4, uint32_t a5);
    void ReadGDS(gfx::_D3D11X_GDS_REGION_TYPE a1, uint32_t a2, uint32_t a3, uint32_t* a4, uint32_t a5);
    void InsertWaitOnMemory(const void* a1, uint32_t a2, D3D11_COMPARISON_FUNC a3, uint32_t a4, uint32_t a5);
    void CSSetShaderUserData(uint32_t a1, uint32_t a2, const uint32_t* a3);
    void WriteValueEndOfPipe64(void* a1, uint64_t a2, uint32_t a3);
    void InsertWaitOnMemory64(const void* a1, uint32_t a2, D3D11_COMPARISON_FUNC a3, uint64_t a4);
    void InsertWaitOnPresent(uint32_t a1, gfx::ID3D11Resource<ABI>* a2);

    BOOL ExecuteContext() override;
    UINT m_CommandIndex = 0;
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11ComputeContextX<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);
