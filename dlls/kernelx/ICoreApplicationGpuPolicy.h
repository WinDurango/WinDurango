#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <windows.ui.core.h>

using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::System;



MIDL_INTERFACE("42A6A529-3CC6-4867-B5B7-6D1FAF5325F9")
ICoreApplicationGpuPolicy : public IInspectable
{
public:
	STDMETHOD(get_DisableKinectGpuReservation)(bool*) PURE;
	STDMETHOD(set_DisableKinectGpuReservation)(bool) PURE;
};




