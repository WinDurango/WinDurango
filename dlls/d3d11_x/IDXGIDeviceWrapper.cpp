#include "pch.h"
#include "IDXGIWrappers.h"
#include "../kernelx/utils.h"

namespace d3d11x
{

    HRESULT IDXGIDeviceWrapper::QueryInterface(REFIID riid, void** ppvObject)
    {
        if (riid == __uuidof(IDXGIDevice))
        {
            *ppvObject = this;
            AddRef( );
            return S_OK;
        }

        // DEBUG
        char iidstr[ sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}") ];
        OLECHAR iidwstr[ sizeof(iidstr) ];
        StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
        WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
        printf("[IDXGIDeviceWrapper] QueryInterface: %s\n", iidstr);

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }




    ULONG IDXGIDeviceWrapper::AddRef( )
    {
        printf("[IDXGIDeviceWrapper] --> AddRef\n");
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG IDXGIDeviceWrapper::Release( )
    {
        printf("[IDXGIDeviceWrapper] --> Release\n");
        ULONG refCount = InterlockedDecrement(&m_RefCount);
        if (refCount == 0)
            delete this;
        return refCount;
    }

    HRESULT __stdcall IDXGIDeviceWrapper::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData)
    {
        return m_realDevice->SetPrivateData(Name, DataSize, pData);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown)
    {
        return m_realDevice->SetPrivateDataInterface(Name, pUnknown);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData)
    {
        return m_realDevice->GetPrivateData(Name, pDataSize, pData);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::GetParent(REFIID riid, void** ppParent)
    {
        // this should probably check if fails -AleBlbl
        HRESULT hr = m_realDevice->GetParent(riid, ppParent);
        this->AddRef( );

        if (IsXboxCallee( ))
        {
            if (riid == __uuidof(IDXGIAdapter))
            {
                *ppParent = new IDXGIAdapterWrapper(reinterpret_cast<IDXGIAdapter*>(*ppParent));
            }
        }
        return hr;
    }

    HRESULT __stdcall IDXGIDeviceWrapper::GetAdapter(IDXGIAdapter_X** pAdapter)
    {
        IDXGIAdapter* adapter;
        HRESULT hr = m_realDevice->GetAdapter(&adapter);

        *pAdapter = new IDXGIAdapterWrapper(adapter);
        return hr;
    }

    HRESULT __stdcall IDXGIDeviceWrapper::CreateSurface(const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface)
    {
        return m_realDevice->CreateSurface(pDesc, NumSurfaces, Usage, pSharedResource, ppSurface);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::QueryResourceResidency(IGraphicsUnknown** ppResources, DXGI_RESIDENCY* pResidencyStatus, UINT NumResources)
    {
        return m_realDevice->QueryResourceResidency(reinterpret_cast<IUnknown**>(ppResources), pResidencyStatus, NumResources);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::SetGPUThreadPriority(INT Priority)
    {
        return m_realDevice->SetGPUThreadPriority(Priority);
    }

    HRESULT __stdcall IDXGIDeviceWrapper::GetGPUThreadPriority(INT* pPriority)
    {
        return m_realDevice->GetGPUThreadPriority(pPriority);
    }

}