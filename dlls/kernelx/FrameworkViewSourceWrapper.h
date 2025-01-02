#pragma once
#include "ICoreApplicationX.h"

class FrameworkViewSourceWrapper : public IFrameworkViewSource
{
public:

	FrameworkViewSourceWrapper(IFrameworkViewSource* windowViewSource)
		: m_realViewSource(windowViewSource)
	{

	}

	HRESULT STDMETHODCALLTYPE CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView** viewProvider) override;

	// IActivationFactory (IInspectable + IUnknown)
	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;

private:
	long m_refCount = 1;
	IFrameworkViewSource* m_realViewSource;
};