#pragma once
#include "ID3D11DeviceContext.h"
#include "d3d11_x.g.h"
#include <vector>
#include <zlib.h>

BOOL DMAFences[1024]{};
UINT DMAFenceIndex = 0;

template <abi_t ABI> struct CopyResourceCommand;

template <abi_t ABI> struct CopySubresourceRegionCommand;

template <abi_t ABI> struct DMAInsertFenceCommand;

template <abi_t ABI> struct DMAInsertWaitOnFenceCommand;

template <abi_t ABI> struct LZDecompressMemoryCommand;

template <abi_t ABI> struct FillMemoryWithValueCommand;

template <abi_t ABI> struct CopyLastErrorCodeToMemoryCommand;

template <abi_t ABI> struct DMACommands
{
  public:
    enum class DMACommandType
    {
        CopyResource,
        CopySubresourceRegion,
        DMAInsertFence,
        DMAInsertWaitOnFence,
        LZDecompressMemory,
        FillMemoryWithValue,
        CopyLastErrorCodeToMemory,
    };

    union {
        CopyResourceCommand<ABI> CopyResource;
        CopySubresourceRegionCommand<ABI> CopySubresourceRegion;
        DMAInsertFenceCommand<ABI> DMAInsertFence;
        DMAInsertWaitOnFenceCommand<ABI> DMAInsertWaitOnFence;
        LZDecompressMemoryCommand<ABI> LZDecompressMemory;
        FillMemoryWithValueCommand<ABI> FillMemoryWithValue;
        CopyLastErrorCodeToMemoryCommand<ABI> CopyLastErrorCodeToMemory;
    };

    DMACommandType m_DMACommandType;
};

template <abi_t ABI> class D3D11DMAEngineContextX : public gfx::ID3D11DMAEngineContextX<ABI>, ID3D11BackgroundContext
{
  public:
    std::vector<DMACommands<ABI>> m_DMACommandQueue;
    D3D11DeviceContextX<ABI> *m_pImmediateContext;

    D3D11DMAEngineContextX()
    {
        if (this->m_RefCount != 0)
            this->m_RefCount = 0;
        AddRef();
        m_pImmediateContext = new D3D11DeviceContextX<ABI>();
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
    // ID3D11DMAEngineContextX
    //
    D3D11_DEVICE_CONTEXT_TYPE GetType();
    void CopyResource(gfx::ID3D11Resource<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3);
    void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5,
                               gfx::ID3D11Resource<ABI> *v6, uint32_t v7, D3D11_BOX const *v8, uint32_t v9);
    HRESULT LZDecompressBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4,
                               uint32_t v5, uint32_t v6);
    HRESULT LZDecompressTexture(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5,
                                gfx::ID3D11Buffer<ABI> *v6, uint32_t v7);
    HRESULT LZCompressBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4,
                             uint32_t v5, uint32_t v6);
    HRESULT LZCompressTexture(gfx::ID3D11Buffer<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3,
                              D3D11_BOX const *v4, uint32_t v5);
    HRESULT JPEGDecode(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5,
                       gfx::ID3D11Buffer<ABI> *v6, uint32_t v7);
    uint64_t InsertFence(uint32_t v1);
    void InsertWaitOnFence(uint32_t v1, uint64_t v2);
    HRESULT Submit();
    void CopyLastErrorCodeToMemory(void *v1);
    void CopyLastErrorCodeToBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2);
    void CopyMemoryToMemory(void *v1, void *v2, uint64_t v3);
    void FillMemoryWithValue(void *v1, uint64_t v2, uint32_t v3);
    void FillResourceWithValue(gfx::ID3D11Resource<ABI> *v1, uint32_t v2);
    HRESULT LZDecompressMemory(void *v1, void *v2, uint32_t v3, uint32_t v4);
    HRESULT LZCompressMemory(void *v1, void *v2, uint32_t v3, uint32_t v4);
    void WriteTimestampToMemory(void *v1);
    void WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2);
    void WriteValueBottomOfPipe(void *v1, uint32_t v2);
    void InsertWaitOnMemory(void const *v1, uint32_t v2, D3D11_COMPARISON_FUNC v3, uint32_t v4, uint32_t v5);

    BOOL ExecuteContext() override;
    UINT m_CommandIndex = 0;
};

template <abi_t ABI> struct CopyResourceCommand
{
    gfx::ID3D11Resource<ABI> *pDstResource;
    gfx::ID3D11Resource<ABI> *pSrcResource;
    UINT Flags;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        pDmaContext->m_pImmediateContext->CopyResource(pDstResource, pSrcResource);
        return FALSE;
    }
};

template <abi_t ABI> struct CopySubresourceRegionCommand
{
    gfx::ID3D11Resource<ABI> *pDstResource;
    UINT DstSubresource;
    UINT DstX;
    UINT DstY;
    UINT DstZ;
    gfx::ID3D11Resource<ABI> *pSrcResource;
    UINT SrcSubresource;
    const D3D11_BOX *pSrcBox;
    UINT Flags;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        pDmaContext->m_pImmediateContext->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ,
                                                                pSrcResource, SrcSubresource, pSrcBox);
        return FALSE;
    }
};

template <abi_t ABI> struct DMAInsertFenceCommand
{
    UINT Flags;
    UINT64 Fence;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        return !*reinterpret_cast<BOOL volatile *>(Fence);
    }
};

template <abi_t ABI> struct DMAInsertWaitOnFenceCommand
{
    UINT Flags;
    UINT64 Fence;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        return !*reinterpret_cast<BOOL volatile *>(Fence);
    }
};

template <abi_t ABI> struct LZDecompressMemoryCommand
{
    void *NextIn;
    void *NextOut;
    UINT AvailIn;
    UINT Flags;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        z_stream Stream{};
        Stream.next_in = reinterpret_cast<Bytef*>(NextIn);
        Stream.avail_in = AvailIn;
        Stream.next_out = reinterpret_cast<Bytef*>(NextOut);
        Stream.avail_out = UINT32_MAX;

        inflate(&Stream, Z_FINISH);
        inflateEnd(&Stream);

        return FALSE;
    }
};

template <abi_t ABI> struct FillMemoryWithValueCommand
{
    void *pDstAddress;
    UINT64 SizeBytes;
    UINT FillValue;

    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        pDmaContext->m_pImmediateContext->FillMemoryWithValue(pDstAddress, SizeBytes, FillValue);
        return FALSE;
    }
};

template <abi_t ABI> struct CopyLastErrorCodeToMemoryCommand
{
    void *pDstAddress;
    BOOL Execute(D3D11DMAEngineContextX<ABI> *pDmaContext)
    {
        return FALSE;
    }
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11DMAEngineContextX<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);