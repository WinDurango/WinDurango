#include "pch.h"
#include "FrameworkViewWrapper.h"




HRESULT __stdcall FrameworkViewWrapper::Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* applicationView)
{
	return m_realView->Initialize(applicationView);
}

HRESULT __stdcall FrameworkViewWrapper::SetWindow(ABI::Windows::UI::Core::ICoreWindow* window)
{
	// Finally Wraps the coreWindow with xbox CoreWindow
	window = reinterpret_cast<ICoreWindow*>(new CoreWindowWrapperX((CoreWindow*)window));
	return m_realView->SetWindow(window);
}

HRESULT __stdcall FrameworkViewWrapper::Load(HSTRING entryPoint)
{
	return m_realView->Load(entryPoint);
}

HRESULT __stdcall FrameworkViewWrapper::Run(void)
{
	return m_realView->Run();
}

HRESULT __stdcall FrameworkViewWrapper::Uninitialize(void)
{
	return m_realView->Uninitialize();
}

HRESULT FrameworkViewWrapper::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == __uuidof(IFrameworkView) ||
		riid == __uuidof(IUnknown) ||
		riid == __uuidof(IInspectable))
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else
	{
		/*/ DEBUG
		char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
		OLECHAR iidwstr[sizeof(iidstr)];
		StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
		WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
		MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);*/
	}

	return m_realView->QueryInterface(riid, ppvObject);
}

ULONG FrameworkViewWrapper::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

ULONG FrameworkViewWrapper::Release()
{
	ULONG refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0)
		delete this;
	return refCount;
}

HRESULT FrameworkViewWrapper::GetIids(ULONG* iidCount, IID** iids)
{
	return m_realView->GetIids(iidCount, iids);
}

HRESULT FrameworkViewWrapper::GetRuntimeClassName(HSTRING* className)
{
	return m_realView->GetRuntimeClassName(className);
}

HRESULT FrameworkViewWrapper::GetTrustLevel(TrustLevel* trustLevel)
{
	return m_realView->GetTrustLevel(trustLevel);
}