#pragma once
#include "ICoreApplicationX.h"

class FrameworkViewWrapper : public IFrameworkView
{
public:

	FrameworkViewWrapper(IFrameworkView* windowView)
		: m_realView(windowView)
	{

	}


	HRESULT STDMETHODCALLTYPE Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* applicationView) override;
	HRESULT STDMETHODCALLTYPE SetWindow(ABI::Windows::UI::Core::ICoreWindow* window) override;
	HRESULT STDMETHODCALLTYPE Load(HSTRING entryPoint) override;
	HRESULT STDMETHODCALLTYPE Run(void) override;
	HRESULT STDMETHODCALLTYPE Uninitialize(void) override;

	// IActivationFactory (IInspectable + IUnknown)
	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;

private:
	long m_refCount = 1;
	IFrameworkView* m_realView;
};