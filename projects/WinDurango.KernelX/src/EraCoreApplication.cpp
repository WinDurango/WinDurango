#include "EraCoreApplication.h"

INT32 CoreApplicationEra::_abi_get_Id(HSTRING *value)
{
    return m_realCoreApplication->get_Id(value);
}

INT32 CoreApplicationEra::_abi_add_Suspending(
    __FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs *handler, EventRegistrationToken *token)
{
    return S_OK;
}

INT32 CoreApplicationEra::_abi_remove_Suspending(EventRegistrationToken token)
{
    return m_realCoreApplication->remove_Suspending(token);
}

INT32 CoreApplicationEra::_abi_add_Resuming(__FIEventHandler_1_IInspectable *handler, EventRegistrationToken *token)
{
    return S_OK;
}

INT32 CoreApplicationEra::_abi_remove_Resuming(EventRegistrationToken token)
{
    return m_realCoreApplication->remove_Resuming(token);
}

INT32 CoreApplicationEra::_abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet **value)
{
    return m_realCoreApplication->get_Properties(value);
}

INT32 CoreApplicationEra::_abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView **value)
{
    return m_realCoreApplication->GetCurrentView(value);
}

INT32 CoreApplicationEra::_abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource *viewSource)
{
    FrameworkViewSourceEra *ViewSource = new FrameworkViewSourceEra(viewSource);
    return m_realCoreApplication->Run(ViewSource);
}

INT32 CoreApplicationEra::_abi_RunWithActivationFactories(
    ABI::Windows::Foundation::IGetActivationFactory *activationFactoryCallback)
{
    throw winrt::hresult_not_implemented();
}

HRESULT CoreApplicationEra::_abi_get_ResourceAvailability(ResourceAvailability *resourceAvailability)
{
    *resourceAvailability = ResourceAvailability_Full;
    return S_OK;
}

HRESULT CoreApplicationEra::_abi_add_ResourceAvailabilityChanged(
    winrt::Windows::Foundation::EventHandler<IInspectable> *handler, EventRegistrationToken *token)
{
    return S_OK;
}

HRESULT CoreApplicationEra::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
    return S_OK;
}

HRESULT CoreApplicationEra::get_DisableKinectGpuReservation(bool *Value)
{
    *Value = this->m_KinectGpuReservation;
    return S_OK;
}

HRESULT CoreApplicationEra::set_DisableKinectGpuReservation(bool Value)
{
    this->m_KinectGpuReservation = Value;
    return S_OK;
}

HRESULT CoreApplicationEra::get_MainView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView **value)
{
    *value = nullptr;
    return S_OK;
}

HRESULT CoreApplicationEra::Exit()
{
    return S_OK;
}

HRESULT CoreApplicationEra::add_Exiting(__FIEventHandler_1_IInspectable *handler, EventRegistrationToken *token)
{
    return S_OK;
}

HRESULT CoreApplicationEra::remove_Exiting(EventRegistrationToken token)
{
    return S_OK;
}

HRESULT CoreApplicationEra::QueryInterface(const IID &riid, void **ppvObject)
{
    if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
    {
        *ppvObject = static_cast<IActivationFactory *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationEra))
    {
        *ppvObject = static_cast<ICoreApplicationEra *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationResourceAvailabilityEra))
    {
        *ppvObject = static_cast<ICoreApplicationResourceAvailabilityEra *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationGpuPolicyEra))
    {
        *ppvObject = static_cast<ICoreApplicationGpuPolicyEra *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(ICoreImmersiveApplicationEra))
    {
        *ppvObject = static_cast<ICoreImmersiveApplicationEra *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationExitEra))
    {
        *ppvObject = static_cast<ICoreApplicationExitEra *>(this);
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

ULONG CoreApplicationEra::AddRef()
{
    return InterlockedIncrement(&m_RefCount);
}

ULONG CoreApplicationEra::Release()
{
    ULONG RefCount = InterlockedDecrement(&m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

HRESULT CoreApplicationEra::GetIids(ULONG *iidCount, IID **iids)
{
    return m_realFactory->GetIids(iidCount, iids);
}

HRESULT CoreApplicationEra::GetRuntimeClassName(HSTRING *className)
{
    return m_realFactory->GetRuntimeClassName(className);
}

HRESULT CoreApplicationEra::GetTrustLevel(TrustLevel *trustLevel)
{
    return m_realFactory->GetTrustLevel(trustLevel);
}