#include "ID3D11CommandList.h"

//
// IUnknown
//
template<abi_t ABI>
HRESULT D3D11CommandList<ABI>::QueryInterface(REFIID riid, void** ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
ULONG D3D11CommandList<ABI>::AddRef()
{
    if (m_pFunction) m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template<abi_t ABI>
ULONG D3D11CommandList<ABI>::Release()
{
    if (m_pFunction) m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (RefCount <= 1)
    {
        for (auto& command : m_Commands)
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
            else if (command.m_CommandType == DrawBundlesCommandType::OMSetRenderTargets)
            {
                if (command.OMSetRenderTargets.ppRenderTargetViews)
                {
                    delete[] command.OMSetRenderTargets.ppRenderTargetViews;
                    command.OMSetRenderTargets.ppRenderTargetViews = nullptr;
                }
            }
            else if (command.m_CommandType == DrawBundlesCommandType::RSSetViewports)
            {
                if (command.RSSetViewports.pViewports)
                {
                    delete[] command.RSSetViewports.pViewports;
                    command.RSSetViewports.pViewports = nullptr;
                }
            }
            else if (command.m_CommandType == DrawBundlesCommandType::RSSetScissorRects)
            {
                if (command.RSSetScissorRects.pRects)
                {
                    delete[] command.RSSetScissorRects.pRects;
                    command.RSSetScissorRects.pRects = nullptr;
                }
            }
        }

        m_Commands.clear();
    }

    if (!RefCount) delete this;
    return RefCount;
}

//
// ID3D11DeviceChild
//
template<abi_t ABI>
void D3D11CommandList<ABI>::GetDevice(gfx::ID3D11Device<ABI>** ppDevice)
{
    IMPLEMENT_STUB();
}

template<abi_t ABI>
HRESULT D3D11CommandList<ABI>::GetPrivateData(_GUID const& guid, uint32_t* pDataSize, void* pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
HRESULT D3D11CommandList<ABI>::SetPrivateData(_GUID const& guid, uint32_t DataSize, void const* pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
HRESULT D3D11CommandList<ABI>::SetPrivateDataInterface(_GUID const& guid, IUnknown const* pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template<abi_t ABI>
HRESULT D3D11CommandList<ABI>::SetPrivateDataInterfaceGraphics(_GUID const& guid, xbox::IGraphicsUnknown<ABI> const* pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11CommandList
//
template<abi_t ABI>
uint32_t D3D11CommandList<ABI>::GetContextFlags()
{
    IMPLEMENT_STUB();
    return 0;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11CommandList<ABI>
D3D11_DECLARE_ABI_TEMPLATES();