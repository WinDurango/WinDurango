#pragma once
#include <windows.applicationmodel.store.h>

MIDL_INTERFACE("d52dc065-da3f-4685-995e-9b482eb5e603")
	ICurrentAppX : IInspectable
{
public:
	virtual HRESULT STDMETHODCALLTYPE get_LicenseInformation(
		ABI::Windows::ApplicationModel::Store::ILicenseInformation* * value
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE get_LinkUri(
		ABI::Windows::Foundation::IUriRuntimeClass** value
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE get_AppId(
		GUID* value
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE RequestAppPurchaseAsync(
		boolean includeReceipt,
		__FIAsyncOperation_1_HSTRING** requestAppPurchaseOperation
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE RequestProductPurchaseAsync(
		HSTRING productId,
		boolean includeReceipt,
		__FIAsyncOperation_1_HSTRING** requestProductPurchaseOperation
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE LoadListingInformationAsync(
		__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation** loadListingOperation
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetAppReceiptAsync(
		__FIAsyncOperation_1_HSTRING** appReceiptOperation
	) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetProductReceiptAsync(
		HSTRING productId,
		__FIAsyncOperation_1_HSTRING** getProductReceiptOperation
	) = 0;
};

MIDL_INTERFACE("8eb7dc30-f170-4ed5-8e21-1516da3fd367")
ILicenseInformationX : IInspectable
{
public:
	virtual HRESULT STDMETHODCALLTYPE get_ProductLicenses(
		__FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense * *value
		) = 0;
	virtual HRESULT STDMETHODCALLTYPE get_IsActive(
		boolean* value
		) = 0;
	virtual HRESULT STDMETHODCALLTYPE get_IsTrial(
		boolean* value
		) = 0;
	virtual HRESULT STDMETHODCALLTYPE get_ExpirationDate(
		ABI::Windows::Foundation::DateTime* value
		) = 0;
	virtual HRESULT STDMETHODCALLTYPE add_LicenseChanged(
		ABI::Windows::ApplicationModel::Store::ILicenseChangedEventHandler* handler,
		EventRegistrationToken* cookie
		) = 0;
	virtual HRESULT STDMETHODCALLTYPE remove_LicenseChanged(
		EventRegistrationToken cookie
		) = 0;
};

MIDL_INTERFACE("AA98C583-A3C8-4F51-A5BC-463AE0C23EAA")
IXboxUserLicenseInformation : public IInspectable
{
public:
	virtual HRESULT STDMETHODCALLTYPE get_CurrentLicenseUserXuid(winrt::hstring* value) = 0;
};

class XboxUserLicenseInformationWrapperX : public IXboxUserLicenseInformation
{
	HRESULT QueryInterface(REFIID riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;
	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;
	HRESULT STDMETHODCALLTYPE get_CurrentLicenseUserXuid(winrt::hstring* value) override;
private:
	long m_RefCount = 1;
};

class LicenseInformationWrapperX : public ILicenseInformationX
{
public:
	LicenseInformationWrapperX(ABI::Windows::ApplicationModel::Store::ILicenseInformation* realLicenseInformation)
		: m_realLicenseInformation(realLicenseInformation)
	{
		m_RefCount++;
	}

	HRESULT QueryInterface(REFIID riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;

	HRESULT STDMETHODCALLTYPE get_ProductLicenses(
		__FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense** value
	) override;

	HRESULT STDMETHODCALLTYPE get_IsActive(
		boolean* value
	) override;

	HRESULT STDMETHODCALLTYPE get_IsTrial(
		boolean* value
	) override;

	HRESULT STDMETHODCALLTYPE get_ExpirationDate(
		ABI::Windows::Foundation::DateTime* value
	) override;

	HRESULT STDMETHODCALLTYPE add_LicenseChanged(
		ABI::Windows::ApplicationModel::Store::ILicenseChangedEventHandler* handler,
		EventRegistrationToken* cookie
	) override;

	HRESULT STDMETHODCALLTYPE remove_LicenseChanged(
		EventRegistrationToken cookie
	) override;

private:
	long m_RefCount = 1;
	ABI::Windows::ApplicationModel::Store::ILicenseInformation* m_realLicenseInformation;
};

class CurrentAppWrapperX : ICurrentAppX
{
public:
	CurrentAppWrapperX(ABI::Windows::ApplicationModel::Store::ICurrentApp* realApp)
		: m_realCurrentApp(realApp)
	{
		m_RefCount++;
	}
	
	HRESULT QueryInterface(REFIID riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;

	HRESULT STDMETHODCALLTYPE get_LicenseInformation(
		ABI::Windows::ApplicationModel::Store::ILicenseInformation** value
	) override;

	HRESULT STDMETHODCALLTYPE get_LinkUri(
		ABI::Windows::Foundation::IUriRuntimeClass** value
	) override;

	HRESULT STDMETHODCALLTYPE get_AppId(
		GUID* value
	) override;

	HRESULT STDMETHODCALLTYPE RequestAppPurchaseAsync(
		boolean includeReceipt,
		__FIAsyncOperation_1_HSTRING** requestAppPurchaseOperation
	) override;

	HRESULT STDMETHODCALLTYPE RequestProductPurchaseAsync(
		HSTRING productId,
		boolean includeReceipt,
		__FIAsyncOperation_1_HSTRING** requestProductPurchaseOperation
	) override;

	HRESULT STDMETHODCALLTYPE LoadListingInformationAsync(
		__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation** loadListingOperation
	) override;

	HRESULT STDMETHODCALLTYPE GetAppReceiptAsync(
		__FIAsyncOperation_1_HSTRING** appReceiptOperation
	) override;

	HRESULT STDMETHODCALLTYPE GetProductReceiptAsync(
		HSTRING productId,
		__FIAsyncOperation_1_HSTRING** getProductReceiptOperation
	) override;

private:
	long m_RefCount = 1;
	ABI::Windows::ApplicationModel::Store::ICurrentApp* m_realCurrentApp;
};