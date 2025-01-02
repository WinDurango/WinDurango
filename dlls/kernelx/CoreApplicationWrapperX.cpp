#include "pch.h"
#include "CoreApplicationWrapperX.h"
#include "FrameworkViewSourceWrapper.h"

HRESULT CoreApplicationWrapperX::GetIids(ULONG* iidCount, IID** iids)
{
	printf("GetIids\n");
	return m_realFactory->GetIids(iidCount, iids);
}

HRESULT CoreApplicationWrapperX::GetRuntimeClassName(HSTRING* className)
{
	printf("GetRuntimeClassName\n");
	return m_realFactory->GetRuntimeClassName(className);
}

HRESULT CoreApplicationWrapperX::GetTrustLevel(TrustLevel* trustLevel)
{
	printf("GetTrustLevel\n");
	return m_realFactory->GetTrustLevel(trustLevel);
}

INT32 CoreApplicationWrapperX::_abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
	printf("_abi_add_Resuming\n");
	//return m_realCoreApplication->add_Resuming(handler, token);
	return S_OK;
}

INT32 CoreApplicationWrapperX::_abi_remove_Resuming(EventRegistrationToken token)
{
	printf("_abi_remove_Resuming\n");
	return m_realCoreApplication->remove_Resuming(token);
}

INT32 CoreApplicationWrapperX::_abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token)
{
	printf("_abi_add_Suspending\n");
	//return m_realCoreApplication->add_Suspending(handler, token);
	return S_OK;
}

INT32 CoreApplicationWrapperX::_abi_remove_Suspending(EventRegistrationToken token)
{
	printf("_abi_remove_Suspending\n");
	return m_realCoreApplication->remove_Suspending(token);
}

HRESULT CoreApplicationWrapperX::_abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability)
{
	// TODO: Stubbed for now.
	*resourceAvailability = ResourceAvailability_Full;
	printf("_abi_get_ResourceAvailability\n");
	return S_OK;
}

HRESULT CoreApplicationWrapperX::_abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token)
{
	printf("_abi_add_ResourceAvailabilityChanged\n");
	//Stubbed at this moment.
	return 0;
}

HRESULT CoreApplicationWrapperX::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
	printf("_abi_remove_ResourceAvailabilityChanged\n");
	//Stubbed at this moment.
	return 0;
}

INT32 CoreApplicationWrapperX::_abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value)
{
	printf("[CoreApplicationWrapperX] ---> _abi_GetCurrentView\n");
	return m_realCoreApplication->GetCurrentView(value);
}

INT32 CoreApplicationWrapperX::_abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource)
{
	printf("_abi_Run\n");

	// Wrap the ViewSource and pass it to the original function
	FrameworkViewSourceWrapper* wrappedViewSource = new FrameworkViewSourceWrapper(viewSource);
	return m_realCoreApplication->Run(wrappedViewSource);
}

INT32 CoreApplicationWrapperX::_abi_get_Id(HSTRING* value)
{
	printf("_abi_get_Id\n");
	return m_realCoreApplication->get_Id(value);
}

INT32 CoreApplicationWrapperX::_abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value)
{
	printf("_abi_get_Properties\n");
	return m_realCoreApplication->get_Properties(value);
}


HRESULT CoreApplicationWrapperX::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
	{
		*ppvObject = static_cast<IActivationFactory*>(this);
		AddRef();
		return S_OK;
	}
	else if (riid == __uuidof(ICoreApplicationX))
	{
		*ppvObject = static_cast<ICoreApplicationX*>(this);
		AddRef();
		return S_OK;
	}
	else if (riid == __uuidof(ICoreApplicationResourceAvailabilityX)) // allow ICoreApplicationResourceAvailabilityX interface
	{
		*ppvObject = static_cast<ICoreApplicationResourceAvailabilityX*>(this);
		AddRef();
		return S_OK;
	} 
	
	// DEBUG
	HRESULT hr = m_realFactory->QueryInterface(riid, ppvObject);
	if(FAILED(hr))
	{
		char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
		OLECHAR iidwstr[sizeof(iidstr)];
		StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
		WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
		MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);
	}

	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG CoreApplicationWrapperX::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

ULONG CoreApplicationWrapperX::Release()
{
	ULONG refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0)
		delete this;
	return refCount;
}

