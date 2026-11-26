#include "Windows.Xbox.ApplicationModel.Core.CoreApplicationContext.h"
#include "WinDurangoWinRT.h"
#include "Windows.Xbox.System.User.h"

namespace winrt::Windows::Xbox::ApplicationModel::Core::implementation
{
    winrt::Windows::Xbox::System::User CoreApplicationContext::CurrentUser()
    {
        return System::implementation::User::Users().GetAt(1);
    }
    winrt::event_token CoreApplicationContext::CurrentUserChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        return {};
    }
    void CoreApplicationContext::CurrentUserChanged(winrt::event_token const& token) noexcept
    {

    }
    void CoreApplicationContext::SetCurrentUser(winrt::Windows::Xbox::System::User const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::ApplicationModel::Core", "Unimplemented: SetCurrentUser");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::System::User CoreApplicationContext::CurrentSystemUser()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::ApplicationModel::Core", "Unimplemented: CurrentSystemUser");
        throw hresult_not_implemented();
    }
    winrt::event_token CoreApplicationContext::CurrentSystemUserChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::ApplicationModel::Core", "Unimplemented: CurrentSystemUserChanged");
        throw hresult_not_implemented();
    }
    void CoreApplicationContext::CurrentSystemUserChanged(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::ApplicationModel::Core", "Unimplemented: CurrentSystemUserChanged");
        throw hresult_not_implemented();
    }
}
