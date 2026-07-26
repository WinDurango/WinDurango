#pragma once
#include "CoreWindow.h"
#include <windows.ui.core.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <wrl.h>
#include "EraCoreWindow.h"

using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::System;
using namespace Microsoft::WRL;

MIDL_INTERFACE("0aacf7a4-5e1d-49df-8034-fb6a68bc5ed1")
ICoreApplicationEra : public IInspectable
{
  public:
    virtual HRESULT QueryInterface(const IID &riid, void **ppvObject) override = 0;
    virtual ULONG AddRef() override = 0;
    virtual ULONG Release() override = 0;

    virtual INT32 _abi_get_Id(HSTRING * value) = 0;
    virtual INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs * handler,
                                      EventRegistrationToken * token) = 0;
    virtual INT32 _abi_remove_Suspending(EventRegistrationToken token) = 0;
    virtual INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable * handler, EventRegistrationToken * token) = 0;
    virtual INT32 _abi_remove_Resuming(EventRegistrationToken token) = 0;
    virtual INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet * *value) = 0;
    virtual INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView * *value) = 0;
    virtual INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource * viewSource) = 0;
    virtual INT32 _abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory *
                                                  activationFactoryCallback) = 0;
};

MIDL_INTERFACE("42A6A529-3CC6-4867-B5B7-6D1FAF5325F9")
ICoreApplicationGpuPolicyEra : public IInspectable
{
  public:
    virtual HRESULT get_DisableKinectGpuReservation(bool *) = 0;
    virtual HRESULT set_DisableKinectGpuReservation(bool) = 0;
};

enum ResourceAvailability
{
    ResourceAvailability_Full,
    ResourceAvailability_Constrained,
    ResourceAvailability_FullWithExtendedSystemReserve,
};

MIDL_INTERFACE("9FF3799E-6E83-468C-A5B0-501CE6BB0FA1")
ICoreApplicationResourceAvailabilityEra : public IInspectable
{
  public:
    STDMETHOD(_abi_get_ResourceAvailability)(ResourceAvailability *) PURE;
    STDMETHOD(_abi_add_ResourceAvailabilityChanged)(winrt::Windows::Foundation::EventHandler<IInspectable> * handler,
                                                    EventRegistrationToken * token) PURE;
    STDMETHOD(_abi_remove_ResourceAvailabilityChanged)(EventRegistrationToken) PURE;
};

MIDL_INTERFACE("1ADA0E3E-E4A2-4123-B451-DC96BF800419")
ICoreImmersiveApplicationEra : public IInspectable
{
public:
	virtual HRESULT STDMETHODCALLTYPE get_MainView(__RPC__deref_out_opt ABI::Windows::ApplicationModel::Core::ICoreApplicationView * *value) = 0;
};

MIDL_INTERFACE("CF86461D-261E-4B72-9ACD-44ED2ACE6A29")
ICoreApplicationExitEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE Exit(void) = 0;
    virtual HRESULT STDMETHODCALLTYPE add_Exiting(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT STDMETHODCALLTYPE remove_Exiting(EventRegistrationToken token) = 0;
};

// Main Wrapper
class CoreApplicationEra : public RuntimeClass<IActivationFactory, ICoreApplicationResourceAvailabilityEra,
                                               ICoreApplicationGpuPolicyEra, ICoreApplicationEra, ICoreImmersiveApplicationEra, ICoreApplicationExitEra>
{
  public:
    CoreApplicationEra(ComPtr<IActivationFactory> realFactory)
    {
        m_realFactory = realFactory;
        HRESULT hr = m_realFactory.As(&m_realCoreApplication);
        if (FAILED(hr))
            throw E_FAIL;
        AddRef();
    }

    // for IActivationFactory
    HRESULT STDMETHODCALLTYPE ActivateInstance(__RPC__deref_out_opt IInspectable **instance) override
    {
        return m_realFactory->ActivateInstance(instance);
    }

    // ICoreApplication
    INT32 _abi_get_Id(HSTRING *value) override;
    INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs *handler,
                              EventRegistrationToken *token) override;
    INT32 _abi_remove_Suspending(EventRegistrationToken token) override;
    INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable *handler, EventRegistrationToken *token) override;
    INT32 _abi_remove_Resuming(EventRegistrationToken token) override;
    INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet **value) override;
    INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView **value) override;
    INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource *viewSource) override;
    INT32 _abi_RunWithActivationFactories(
        ABI::Windows::Foundation::IGetActivationFactory *activationFactoryCallback) override;

    // ICoreApplicationResourceAvailability
    HRESULT _abi_get_ResourceAvailability(ResourceAvailability *resourceAvailability) override;
    HRESULT _abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable> *handler,
                                                 EventRegistrationToken *token) override;
    HRESULT _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) override;

    // ICoreApplicationGpuPolicy
    HRESULT get_DisableKinectGpuReservation(bool *) override;
    HRESULT set_DisableKinectGpuReservation(bool) override;

    // ICoreImmersiveApplication   
    HRESULT get_MainView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value) override;

    // ICoreApplicationExit
    HRESULT Exit() override;
    HRESULT add_Exiting(__FIEventHandler_1_IInspectable *handler, EventRegistrationToken *token) override;
    HRESULT remove_Exiting(EventRegistrationToken token) override;

    // IActivationFactory (IInspectable + IUnknown)
    HRESULT QueryInterface(const IID &riid, void **ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

    HRESULT GetIids(ULONG *iidCount, IID **iids) override;
    HRESULT GetRuntimeClassName(HSTRING *className) override;
    HRESULT GetTrustLevel(TrustLevel *trustLevel) override;

  private:
    ULONG m_RefCount = 0;
    ComPtr<ICoreApplication> m_realCoreApplication;
    ComPtr<IActivationFactory> m_realFactory;
    bool m_KinectGpuReservation = false;
};

class FrameworkViewEra : public IFrameworkView
{
  public:
    FrameworkViewEra(IFrameworkView *windowView)
    {
        m_realView = windowView;
        AddRef();
    }

    HRESULT Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView *applicationView) override
    {
        return m_realView->Initialize(applicationView);
    }

    HRESULT SetWindow(ABI::Windows::UI::Core::ICoreWindow *window) override
    {
        window = reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow *>(
            new CoreWindowEra((ABI::Windows::UI::Core::CoreWindow *)window));
        m_realView->SetWindow(window);

        //Resizes game window to 1280x720 so it's not a square by default.
        
        auto view = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
        winrt::Windows::Foundation::Size desiredSize{1280.0f, 720.0f};
        view.TryResizeView(desiredSize);

        return S_OK;
    }

    HRESULT Load(HSTRING entryPoint) override
    {
        return m_realView->Load(entryPoint);
    }

    HRESULT Run() override
    {
        return m_realView->Run();
    }

    HRESULT Uninitialize() override
    {
        return m_realView->Uninitialize();
    }

    // IActivationFactory (IInspectable + IUnknown)
    HRESULT QueryInterface(const IID &riid, void **ppvObject) override
    {
        if (riid == __uuidof(IFrameworkView) || riid == __uuidof(IUnknown) || riid == __uuidof(IInspectable))
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG AddRef() override
    {
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        ULONG refCount = InterlockedDecrement(&m_RefCount);
        if (refCount == 0)
            delete this;
        return refCount;
    }

    HRESULT GetIids(ULONG *iidCount, IID **iids) override
    {
        return m_realView->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING *className) override
    {
        return m_realView->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel *trustLevel) override
    {
        return m_realView->GetTrustLevel(trustLevel);
    }

  private:
    ULONG m_RefCount = 0;
    IFrameworkView *m_realView;
};

class FrameworkViewSourceEra : public IFrameworkViewSource
{
  public:
    FrameworkViewSourceEra(IFrameworkViewSource *windowViewSource)
    {
        m_realViewSource = windowViewSource;
        AddRef();
    }

    HRESULT STDMETHODCALLTYPE CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView **viewProvider) override
    {
        auto hr = m_realViewSource->CreateView(viewProvider);

        if (SUCCEEDED(hr))
            *viewProvider = new FrameworkViewEra(*viewProvider);

        return hr;
    }

    // IActivationFactory (IInspectable + IUnknown)
    HRESULT QueryInterface(const IID &riid, void **ppvObject) override
    {
        if (riid == __uuidof(IFrameworkViewSource))
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
        OLECHAR iidwstr[sizeof(iidstr)];
        StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
        WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
        MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG AddRef() override
    {
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        ULONG refCount = InterlockedDecrement(&m_RefCount);
        if (refCount == 0)
            delete this;
        return refCount;
    }

    HRESULT GetIids(ULONG *iidCount, IID **iids) override
    {
        return m_realViewSource->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING *className) override
    {
        return m_realViewSource->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel *trustLevel) override
    {
        return m_realViewSource->GetTrustLevel(trustLevel);
    }

  private:
    ULONG m_RefCount = 0;
    IFrameworkViewSource *m_realViewSource;
};

MIDL_INTERFACE("4207a996-ca2f-42f7-bde8-8b10457a7f30")
IStorageItemEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE get_Name(HSTRING* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Path(HSTRING* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Attributes(ABI::Windows::Storage::FileAttributes* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_DateCreated(ABI::Windows::Foundation::DateTime* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE IsOfType(ABI::Windows::Storage::StorageItemTypes type,boolean* value) = 0;
};

MIDL_INTERFACE("72d1cb78-b3ef-4f75-a80b-6fd9dae2944b")
IStorageFolderEra : public IStorageItemEra
{
public:
};

class StorageFolderEra : public IStorageFolderEra
{
public:
    StorageFolderEra(ComPtr<ABI::Windows::Storage::IStorageFolder> realFolder)
    {
        m_realFolder = realFolder;
        m_realFolder.As(&m_realItem);
        InterlockedIncrement(&m_RefCount);
    }

    HRESULT STDMETHODCALLTYPE get_Name(HSTRING* value) override
    {
        return m_realItem->get_Name(value);
    }

    HRESULT STDMETHODCALLTYPE get_Path(HSTRING* value) override
    {
        return m_realItem->get_Path(value);
    }

    HRESULT STDMETHODCALLTYPE get_Attributes(ABI::Windows::Storage::FileAttributes* value) override
    {
        return m_realItem->get_Attributes(value);
    }

    HRESULT STDMETHODCALLTYPE get_DateCreated(ABI::Windows::Foundation::DateTime* value) override
    {
        return m_realItem->get_DateCreated(value);
    }

    HRESULT STDMETHODCALLTYPE IsOfType(ABI::Windows::Storage::StorageItemTypes type, boolean* value) override
    {
        return m_realItem->IsOfType(type, value);
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override
    {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IInspectable) || riid == __uuidof(IStorageFolderEra) ||
            riid == __uuidof(IStorageItemEra))
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
        OLECHAR iidwstr[sizeof(iidstr)];
        StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
        WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
        MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG AddRef() override
    {
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        ULONG RefCount = InterlockedDecrement(&m_RefCount);
        if (!RefCount) delete this;
        return RefCount;
    }

    HRESULT GetIids(ULONG* iidCount, IID** iids) override
    {
        return m_realFolder->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING* className) override
    {
        return m_realFolder->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel* trustLevel) override
    {
        return m_realFolder->GetTrustLevel(trustLevel);
    }

private:
    ComPtr<ABI::Windows::Storage::IStorageFolder> m_realFolder;
    ComPtr<ABI::Windows::Storage::IStorageItem> m_realItem;
    ULONG m_RefCount = 0;
};

MIDL_INTERFACE("c3da6fb7-b744-4b45-b0b8-223a0938d0dc")
IApplicationDataEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE get_LocalFolder(IStorageFolderEra** value) = 0;
};

MIDL_INTERFACE("5612147b-e843-45e3-94d8-06169e3c8e17")
IApplicationDataStaticsEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE get_Current(IApplicationDataEra** value) = 0;
};

class ApplicationDataEra : public RuntimeClass<IActivationFactory, IApplicationDataEra, IApplicationDataStaticsEra>
{
public:
    ApplicationDataEra(ComPtr<IActivationFactory> realFactory)
    {
        m_realFactory = realFactory;
        HRESULT hr = m_realFactory.As(&m_realApplicationDataStatics);
        m_realApplicationDataStatics->get_Current(&m_realApplicationData);
        InterlockedIncrement(&m_RefCount);
    }

    HRESULT get_LocalFolder(IStorageFolderEra** value) override
    {
        ComPtr<ABI::Windows::Storage::IStorageFolder> Folder;
        HRESULT hr = m_realApplicationData->get_LocalFolder(Folder.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            *value = new StorageFolderEra(Folder);
        }
        
        return hr;
    }

    HRESULT STDMETHODCALLTYPE get_Current(IApplicationDataEra** value) override
    {
        *value = static_cast<IApplicationDataEra*>(this);
        AddRef();
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE ActivateInstance(__RPC__deref_out_opt IInspectable **instance) override
    {
        return m_realFactory->ActivateInstance(instance);
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override
    {
        if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IActivationFactory *>(this);
            AddRef();
            return S_OK;
        }
        if (riid == __uuidof(IApplicationDataEra))
        {
            *ppvObject = static_cast<IApplicationDataEra *>(this);
            AddRef();
            return S_OK;
        }
        if (riid == __uuidof(IApplicationDataStaticsEra))
        {
            *ppvObject = static_cast<IApplicationDataStaticsEra *>(this);
            AddRef();
            return S_OK;
        }

        char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
        OLECHAR iidwstr[sizeof(iidstr)];
        StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
        WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
        MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG AddRef() override
    {
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        ULONG RefCount = InterlockedDecrement(&m_RefCount);
        if (!RefCount) delete this;
        return RefCount;
    }

    HRESULT GetIids(ULONG* iidCount, IID** iids) override
    {
        return m_realFactory->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING* className) override
    {
        return m_realFactory->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel* trustLevel) override
    {
        return m_realFactory->GetTrustLevel(trustLevel);
    }

private:
    ComPtr<ABI::Windows::Storage::IApplicationDataStatics> m_realApplicationDataStatics;
    ComPtr<ABI::Windows::Storage::IApplicationData> m_realApplicationData;
    ComPtr<IActivationFactory> m_realFactory;
    ULONG m_RefCount = 0;
};

MIDL_INTERFACE("163C792F-BD75-413C-BF23-B1FE7B95D825")
IPackageEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE get_Id(ABI::Windows::ApplicationModel::IPackageId **value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_InstalledLocation(IStorageFolderEra **value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_IsFramework(boolean *value) = 0;
};

MIDL_INTERFACE("4E534BDF-2960-4878-97A4-9624DEB72F2D")
IPackageStaticsEra : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE get_Current(IPackageEra **value) = 0;
};

class PackageEra : public RuntimeClass<IActivationFactory, IPackageEra, IPackageStaticsEra>
{
public:
    PackageEra(ComPtr<IActivationFactory> realFactory)
    {
        m_realFactory = realFactory;
        HRESULT hr = m_realFactory.As(&m_realPackageStatics);
        m_realPackageStatics->get_Current(&m_realPackage);
        InterlockedIncrement(&m_RefCount);
    }

    HRESULT STDMETHODCALLTYPE get_Id(ABI::Windows::ApplicationModel::IPackageId **value) override
    {
        return m_realPackage->get_Id(value);
    }

    HRESULT STDMETHODCALLTYPE get_InstalledLocation(IStorageFolderEra **value) override
    {
        ComPtr<ABI::Windows::Storage::IStorageFolder> Folder;
        HRESULT hr = m_realPackage->get_InstalledLocation(Folder.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            *value = new StorageFolderEra(Folder);
        }

        return hr;
    }

    HRESULT STDMETHODCALLTYPE get_IsFramework(boolean *value) override
    {
        return m_realPackage->get_IsFramework(value);
    }

    HRESULT STDMETHODCALLTYPE get_Current(IPackageEra **value) override
    {
        *value = static_cast<IPackageEra*>(this);
        AddRef();
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE ActivateInstance(__RPC__deref_out_opt IInspectable **instance) override
    {
        return m_realFactory->ActivateInstance(instance);
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override
    {
        if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IActivationFactory *>(this);
            AddRef();
            return S_OK;
        }
        if (riid == __uuidof(IPackageEra))
        {
            *ppvObject = static_cast<IPackageEra *>(this);
            AddRef();
            return S_OK;
        }
        if (riid == __uuidof(IPackageStaticsEra))
        {
            *ppvObject = static_cast<IPackageStaticsEra *>(this);
            AddRef();
            return S_OK;
        }

        char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
        OLECHAR iidwstr[sizeof(iidstr)];
        StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
        WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
        MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG AddRef() override
    {
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        ULONG RefCount = InterlockedDecrement(&m_RefCount);
        if (!RefCount) delete this;
        return RefCount;
    }

    HRESULT GetIids(ULONG* iidCount, IID** iids) override
    {
        return m_realFactory->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING* className) override
    {
        return m_realFactory->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel* trustLevel) override
    {
        return m_realFactory->GetTrustLevel(trustLevel);
    }

private:
    ComPtr<ABI::Windows::ApplicationModel::IPackageStatics> m_realPackageStatics;
    ComPtr<ABI::Windows::ApplicationModel::IPackage> m_realPackage;
    ComPtr<IActivationFactory> m_realFactory;
    ULONG m_RefCount = 0;
};