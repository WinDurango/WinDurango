#include "pch.h"
#include "CurrentAppWrapper.hpp"

HRESULT XboxUserLicenseInformationWrapperX::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == __uuidof(IXboxUserLicenseInformation))
	{
		*ppvObject = reinterpret_cast<ICurrentAppX*>(this);
		AddRef();
		return S_OK;
	}

	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG XboxUserLicenseInformationWrapperX::AddRef()
{
	return InterlockedIncrement(&m_RefCount);
}

ULONG XboxUserLicenseInformationWrapperX::Release()
{
	ULONG refCount = InterlockedDecrement(&m_RefCount);
	if (refCount == 0)
	{
		delete this;
	}
	return refCount;
}

HRESULT XboxUserLicenseInformationWrapperX::GetIids(ULONG* iidCount, IID** iids)
{
	return E_NOTIMPL;
}

HRESULT XboxUserLicenseInformationWrapperX::GetRuntimeClassName(HSTRING* className)
{
	return E_NOTIMPL;
}

HRESULT XboxUserLicenseInformationWrapperX::GetTrustLevel(TrustLevel* trustLevel)
{
	return E_NOTIMPL;
}

HRESULT XboxUserLicenseInformationWrapperX::get_CurrentLicenseUserXuid(winrt::hstring* value)
{
	printf("[XboxUserLicenseInformationWrapperX] get_CurrentLicenseUserXuid\n");
	*value = winrt::to_hstring(123);
	return S_OK;
}

HRESULT LicenseInformationWrapperX::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == __uuidof(ILicenseInformationX))
	{
		*ppvObject = reinterpret_cast<ICurrentAppX*>(this);
		AddRef();
		return S_OK;
	}

	if (riid == __uuidof(IXboxUserLicenseInformation))
	{
		*ppvObject = reinterpret_cast<IXboxUserLicenseInformation*>(new XboxUserLicenseInformationWrapperX());
		AddRef();
		return S_OK;
	}

	HRESULT hr = m_realLicenseInformation->QueryInterface(riid, ppvObject);
	if (FAILED(hr))
	{
		char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
		OLECHAR iidwstr[sizeof(iidstr)];
		StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
		WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
		printf("[LicenseInformationWrapperX] Interface Not Implemented: %s\n", iidstr);
	}

	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG LicenseInformationWrapperX::AddRef()
{
	return InterlockedIncrement(&m_RefCount);
}

ULONG LicenseInformationWrapperX::Release()
{
	ULONG refCount = InterlockedDecrement(&m_RefCount);
	if (refCount == 0)
	{
		m_realLicenseInformation->Release();
		delete this;
	}
	return refCount;
}

HRESULT LicenseInformationWrapperX::GetIids(ULONG* iidCount, IID** iids)
{
	return m_realLicenseInformation->GetIids(iidCount, iids);
}

HRESULT LicenseInformationWrapperX::GetRuntimeClassName(HSTRING* className)
{
	return m_realLicenseInformation->GetRuntimeClassName(className);
}

HRESULT LicenseInformationWrapperX::GetTrustLevel(TrustLevel* trustLevel)
{
	return m_realLicenseInformation->GetTrustLevel(trustLevel);
}

HRESULT LicenseInformationWrapperX::get_ProductLicenses(
	ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_t**
	value)
{
	printf("[LicenseInformationWrapperX] get_ProductLicenses\n");
	return E_NOTIMPL;
}

HRESULT LicenseInformationWrapperX::get_IsActive(boolean* value)
{
	printf("[LicenseInformationWrapperX] get_IsActive\n");
	*value = true;
	return S_OK;
}

HRESULT LicenseInformationWrapperX::get_IsTrial(boolean* value)
{
	printf("[LicenseInformationWrapperX] get_IsTrial\n");
	*value = false;
	return S_OK;
}

HRESULT LicenseInformationWrapperX::get_ExpirationDate(ABI::Windows::Foundation::DateTime* value)
{
	printf("[LicenseInformationWrapperX] get_ExpirationDate\n");
	DateTime time;
	time.UniversalTime = UINT64_MAX;

	*value = time;
	return S_OK;
}

HRESULT LicenseInformationWrapperX::add_LicenseChanged(
	ABI::Windows::ApplicationModel::Store::ILicenseChangedEventHandler* handler, EventRegistrationToken* cookie)
{
	HRESULT hr = m_realLicenseInformation->add_LicenseChanged(handler, cookie);
	printf("[LicenseInformationWrapperX] add_LicenseChanged\n");

	if (SUCCEEDED(hr))
		handler->Invoke();

	return hr;
}

HRESULT LicenseInformationWrapperX::remove_LicenseChanged(EventRegistrationToken cookie)
{
	printf("[LicenseInformationWrapperX] remove_LicenseChanged\n");
	return E_NOTIMPL;
}

HRESULT __stdcall CurrentAppWrapperX::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == __uuidof(ICurrentAppX))
	{
		*ppvObject = reinterpret_cast<ICurrentAppX*>(this);
		AddRef();
		return S_OK;
	}

	HRESULT hr = m_realCurrentApp->QueryInterface(riid, ppvObject);
	if (FAILED(hr))
	{
		char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
		OLECHAR iidwstr[sizeof(iidstr)];
		StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
		WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
		printf("[CurrentAppWrapperX] Interface Not Implemented: %s\n", iidstr);
	}

	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG __stdcall CurrentAppWrapperX::AddRef()
{
	return InterlockedIncrement(&m_RefCount);
}

ULONG __stdcall CurrentAppWrapperX::Release()
{
	ULONG refCount = InterlockedDecrement(&m_RefCount);
	if (refCount == 0)
	{
		m_realCurrentApp->Release();
		delete this;
	}
	return refCount;
}

HRESULT CurrentAppWrapperX::GetIids(ULONG* iidCount, IID** iids)
{
	printf("[CurrentAppWrapperX] GetIids\n");
	return m_realCurrentApp->GetIids(iidCount, iids);
}

HRESULT CurrentAppWrapperX::GetRuntimeClassName(HSTRING* className)
{
	printf("[CurrentAppWrapperX] GetRuntimeClassName\n");
	return m_realCurrentApp->GetRuntimeClassName(className);
}

HRESULT CurrentAppWrapperX::GetTrustLevel(TrustLevel* trustLevel)
{
	printf("[CurrentAppWrapperX] GetTrustLevel\n");
	return m_realCurrentApp->GetTrustLevel(trustLevel);
}

HRESULT CurrentAppWrapperX::get_LicenseInformation(ABI::Windows::ApplicationModel::Store::ILicenseInformation** value)
{
	printf("[CurrentAppWrapperX] get_LicenseInformation\n");
	return E_NOTIMPL;
}

HRESULT CurrentAppWrapperX::get_LinkUri(ABI::Windows::Foundation::IUriRuntimeClass** value)
{
	return m_realCurrentApp->get_LinkUri(value);
}

HRESULT CurrentAppWrapperX::get_AppId(GUID* value)
{
	return m_realCurrentApp->get_AppId(value);
}

HRESULT CurrentAppWrapperX::RequestAppPurchaseAsync(boolean includeReceipt,
	ABI::Windows::Foundation::__FIAsyncOperation_1_HSTRING_t** requestAppPurchaseOperation)
{
	return m_realCurrentApp->RequestAppPurchaseAsync(includeReceipt, requestAppPurchaseOperation);
}

HRESULT CurrentAppWrapperX::RequestProductPurchaseAsync(HSTRING productId, boolean includeReceipt,
	ABI::Windows::Foundation::__FIAsyncOperation_1_HSTRING_t** requestProductPurchaseOperation)
{
	return S_OK;
}

HRESULT CurrentAppWrapperX::LoadListingInformationAsync(
	ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation_t**
	loadListingOperation)
{
	return m_realCurrentApp->LoadListingInformationAsync(loadListingOperation);
}

HRESULT CurrentAppWrapperX::GetAppReceiptAsync(
	ABI::Windows::Foundation::__FIAsyncOperation_1_HSTRING_t** appReceiptOperation)
{
	return m_realCurrentApp->GetAppReceiptAsync(appReceiptOperation);
}

HRESULT CurrentAppWrapperX::GetProductReceiptAsync(HSTRING productId,
	ABI::Windows::Foundation::__FIAsyncOperation_1_HSTRING_t** getProductReceiptOperation)
{
	return m_realCurrentApp->GetProductReceiptAsync(productId, getProductReceiptOperation);
}
