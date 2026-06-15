#include "ID3D11Resource.h"
#include "d3d11.x.h"

//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11Resource<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG D3D11Resource<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11Resource<ABI>::Release()
{
    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        void* AllocationBase = nullptr;
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(this->m_pAllocationStart, &mbi, sizeof(mbi));
        if (mbi.AllocationBase && Result == sizeof(mbi))
        {
            AllocationBase = mbi.AllocationBase;
            auto range = g_ResourceMap.equal_range(AllocationBase);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second == this)
                {
                    g_ResourceMap.erase(it);
                    break;
                }
            }
        }

        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11Resource<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11Resource<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Resource<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Resource<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Resource<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Resource
//
template <abi_t ABI> void D3D11Resource<ABI>::GetType(D3D11_RESOURCE_DIMENSION *pDimension)
{
    m_pFunction->GetType(pDimension);
}

template <abi_t ABI> void D3D11Resource<ABI>::SetEvictionPriority(uint32_t EvictionPriority)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> uint32_t D3D11Resource<ABI>::GetEvictionPriority()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11Resource<ABI>::GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc)
{
    IMPLEMENT_STUB();
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Resource<ABI>
D3D11_DECLARE_ABI_TEMPLATES();


//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11Texture1D<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11Texture1D>() || riid == xcom::guid_of<gfx::ID3D11Resource>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11Texture1D<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11Texture1D<ABI>::Release()
{
    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        void* AllocationBase = nullptr;
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(this->m_pAllocationStart, &mbi, sizeof(mbi));
        if (mbi.AllocationBase && Result == sizeof(mbi))
        {
            AllocationBase = mbi.AllocationBase;
            auto range = g_ResourceMap.equal_range(AllocationBase);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second == this)
                {
                    g_ResourceMap.erase(it);
                    break;
                }
            }
        }

        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11Texture1D<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11Texture1D<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture1D<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Texture1D<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture1D<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                             xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Resource
//
template <abi_t ABI> void D3D11Texture1D<ABI>::GetType(D3D11_RESOURCE_DIMENSION *pDimension)
{
    m_pFunction->GetType(pDimension);
}

template <abi_t ABI> void D3D11Texture1D<ABI>::SetEvictionPriority(uint32_t EvictionPriority)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> uint32_t D3D11Texture1D<ABI>::GetEvictionPriority()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11Texture1D<ABI>::GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc)
{
    IMPLEMENT_STUB();
}

//
// ID3D11Texture1D
//
template <abi_t ABI> void D3D11Texture1D<ABI>::GetDesc(D3D11_TEXTURE1D_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture1D<ABI>
D3D11_DECLARE_ABI_TEMPLATES();


//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11Texture2D<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11Texture2D>() || riid == xcom::guid_of<gfx::ID3D11Resource>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11Texture2D<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11Texture2D<ABI>::Release()
{
    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        void* AllocationBase = nullptr;
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(this->m_pAllocationStart, &mbi, sizeof(mbi));
        if (mbi.AllocationBase && Result == sizeof(mbi))
        {
            AllocationBase = mbi.AllocationBase;
            auto range = g_ResourceMap.equal_range(AllocationBase);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second == this)
                {
                    g_ResourceMap.erase(it);
                    break;
                }
            }
        }

        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11Texture2D<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11Texture2D<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture2D<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Texture2D<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture2D<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                             xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Resource
//
template <abi_t ABI> void D3D11Texture2D<ABI>::GetType(D3D11_RESOURCE_DIMENSION *pDimension)
{
    m_pFunction->GetType(pDimension);
}

template <abi_t ABI> void D3D11Texture2D<ABI>::SetEvictionPriority(uint32_t EvictionPriority)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> uint32_t D3D11Texture2D<ABI>::GetEvictionPriority()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11Texture2D<ABI>::GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc)
{
    IMPLEMENT_STUB();
}

//
// ID3D11Texture2D
//
template <abi_t ABI> void D3D11Texture2D<ABI>::GetDesc(D3D11_TEXTURE2D_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture2D<ABI>
D3D11_DECLARE_ABI_TEMPLATES();


//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11Texture3D<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == xcom::guid_of<gfx::ID3D11Texture3D>() || riid == xcom::guid_of<gfx::ID3D11Resource>())
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    IMPLEMENT_STUB();
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

template <abi_t ABI> ULONG D3D11Texture3D<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11Texture3D<ABI>::Release()
{
    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        void* AllocationBase = nullptr;
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(this->m_pAllocationStart, &mbi, sizeof(mbi));
        if (mbi.AllocationBase && Result == sizeof(mbi))
        {
            AllocationBase = mbi.AllocationBase;
            auto range = g_ResourceMap.equal_range(AllocationBase);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second == this)
                {
                    g_ResourceMap.erase(it);
                    break;
                }
            }
        }

        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11Texture3D<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11Texture3D<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture3D<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Texture3D<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Texture3D<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid,
                                                             xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Resource
//
template <abi_t ABI> void D3D11Texture3D<ABI>::GetType(D3D11_RESOURCE_DIMENSION *pDimension)
{
    m_pFunction->GetType(pDimension);
}

template <abi_t ABI> void D3D11Texture3D<ABI>::SetEvictionPriority(uint32_t EvictionPriority)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> uint32_t D3D11Texture3D<ABI>::GetEvictionPriority()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11Texture3D<ABI>::GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc)
{
    IMPLEMENT_STUB();
}

//
// ID3D11Texture3D
//
template <abi_t ABI> void D3D11Texture3D<ABI>::GetDesc(D3D11_TEXTURE3D_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Texture3D<ABI>
D3D11_DECLARE_ABI_TEMPLATES();


//
// IUnknown
//
template <abi_t ABI> HRESULT D3D11Buffer<ABI>::QueryInterface(REFIID riid, void **ppvObject)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> ULONG D3D11Buffer<ABI>::AddRef()
{
    m_pFunction->AddRef();
    return InterlockedIncrement(&this->m_RefCount);
}

template <abi_t ABI> ULONG D3D11Buffer<ABI>::Release()
{
    std::lock_guard PlacementUpdateLock(g_ResourceMapMutex);
    m_pFunction->Release();
    ULONG RefCount = InterlockedDecrement(&this->m_RefCount);
    if (!RefCount)
    {
        void* AllocationBase = nullptr;
        MEMORY_BASIC_INFORMATION mbi{};
        SIZE_T Result = VirtualQuery(this->m_pAllocationStart, &mbi, sizeof(mbi));
        if (mbi.AllocationBase && Result == sizeof(mbi))
        {
            AllocationBase = mbi.AllocationBase;
            auto range = g_ResourceMap.equal_range(AllocationBase);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second == this)
                {
                    g_ResourceMap.erase(it);
                    break;
                }
            }
        }

        delete this;
    }
    return RefCount;
}

//
// ID3D11DeviceChild
//
template <abi_t ABI> void D3D11Buffer<ABI>::GetDevice(gfx::ID3D11Device<ABI> **ppDevice)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> HRESULT D3D11Buffer<ABI>::GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Buffer<ABI>::SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI> HRESULT D3D11Buffer<ABI>::SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

template <abi_t ABI>
HRESULT D3D11Buffer<ABI>::SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData)
{
    IMPLEMENT_STUB();
    return E_NOTIMPL;
}

//
// ID3D11Resource
//
template <abi_t ABI> void D3D11Buffer<ABI>::GetType(D3D11_RESOURCE_DIMENSION *pDimension)
{
    m_pFunction->GetType(pDimension);
}

template <abi_t ABI> void D3D11Buffer<ABI>::SetEvictionPriority(uint32_t EvictionPriority)
{
    IMPLEMENT_STUB();
}

template <abi_t ABI> uint32_t D3D11Buffer<ABI>::GetEvictionPriority()
{
    IMPLEMENT_STUB();
    return {};
}

template <abi_t ABI> void D3D11Buffer<ABI>::GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc)
{
    IMPLEMENT_STUB();
}

//
// ID3D11Buffer
//
template <abi_t ABI> void D3D11Buffer<ABI>::GetDesc(D3D11_BUFFER_DESC *pDesc)
{
    m_pFunction->GetDesc(pDesc);
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11Buffer<ABI>
D3D11_DECLARE_ABI_TEMPLATES();