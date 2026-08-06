#include "Windows.Xbox.System.User.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::System::implementation
{
    winrt::Windows::Xbox::System::User UserAddedEventArgs::User()
    {
        return m_user;
    }

    winrt::Windows::Xbox::System::User UserRemovedEventArgs::User()
    {
        return m_user;
    }

    winrt::Windows::Xbox::System::UserOnlineState User::OnlineState()
    {
        return winrt::Windows::Xbox::System::UserOnlineState::Offline;
    }

    winrt::event_token User::OnlineStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::OnlineStateChangedEventArgs> const& handler)
    {
        return m_OnlineStateChanged.add(handler);
    }

    void User::OnlineStateChanged(winrt::event_token const& token) noexcept
    {
        m_OnlineStateChanged.remove(token);
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> User::Users()
    {
        if (a_users == winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::System::User>(nullptr) || a_users.Size() == 0)
        {
            a_users = winrt::single_threaded_vector<winrt::Windows::Xbox::System::User>();

            for (size_t i = 0; i < 4; i++)
            {
                p_wd->log.Log("WinDurango::WinRT::Windows::Xbox::System", "Creating user");
                winrt::Windows::Xbox::System::User user = winrt::make<User>(i);
                a_users.Append(user);
            }
        }

        return a_users.GetView();
    }

    winrt::event_token User::UserAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs> const& handler)
    {
        return m_UserAdded.add(handler);
    }

    void User::UserAdded(winrt::event_token const& token) noexcept
    {
        m_UserAdded.remove(token);
    }

    winrt::event_token User::UserRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserRemovedEventArgs> const& handler)
    {
        return m_UserRemoved.add(handler);
    }

    void User::UserRemoved(winrt::event_token const& token) noexcept
    {
        m_UserRemoved.remove(token);
    }

    winrt::Windows::Xbox::System::User User::GetUserById(uint32_t Id)
    {
        return Users().GetAt(Id);
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring method, hstring url, hstring headers)
    {
        co_return winrt::make<winrt::Windows::Xbox::System::implementation::GetTokenAndSignatureResult>();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring method, hstring url, hstring headers, winrt::Windows::Foundation::Collections::IVector<uint8_t> body)
    {
        co_return winrt::make<winrt::Windows::Xbox::System::implementation::GetTokenAndSignatureResult>();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring method, hstring url, hstring headers, hstring body)
    {
        co_return winrt::make<winrt::Windows::Xbox::System::implementation::GetTokenAndSignatureResult>();
    }

    winrt::event_token User::AudioDeviceAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceAddedEventArgs> const& handler)
    {
        return {};
    }

    void User::AudioDeviceAdded(winrt::event_token const& token) noexcept
    {

    }

    winrt::event_token User::AudioDeviceRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceRemovedEventArgs> const& handler)
    {
        return {};
    }

    void User::AudioDeviceRemoved(winrt::event_token const& token) noexcept
    {

    }

    winrt::event_token User::AudioDeviceChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceChangedEventArgs> const& handler)
    {
        return {};
    }

    void User::AudioDeviceChanged(winrt::event_token const& token) noexcept
    {

    }

    winrt::event_token User::SignInCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignInCompletedEventArgs> const& handler)
    {
        return {};
    }

    void User::SignInCompleted(winrt::event_token const& token) noexcept
    {
        
    }

    winrt::event_token User::SignOutStarted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutStartedEventArgs> const& handler)
    {
        return {};
    }

    void User::SignOutStarted(winrt::event_token const& token) noexcept
    {

    }

    winrt::event_token User::SignOutCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutCompletedEventArgs> const& handler)
    {
        return {};
    }

    void User::SignOutCompleted(winrt::event_token const& token) noexcept
    {

    }

    winrt::event_token User::UserDisplayInfoChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserDisplayInfoChangedEventArgs> const& handler)
    {
        return {};
    }

    void User::UserDisplayInfoChanged(winrt::event_token const& token) noexcept
    {

    }

    winrt::guid User::GetNetworkCacheIdForUsers(winrt::Windows::Foundation::Collections::IVectorView<uint32_t> const& unk)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::System", "Unimplemented: GetNetworkCacheIdForUsers");
        throw hresult_not_implemented();
    }

    uint32_t User::Id()
    {
        return id;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::AudioDeviceInfo> User::AudioDevices()
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::System::AudioDeviceInfo>().GetView();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IController> User::Controllers()
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Input::IController>().GetView();
    }

    winrt::Windows::Xbox::System::UserDisplayInfo User::DisplayInfo()
    {
        hstring ID = to_hstring(id);
        return winrt::make<winrt::Windows::Xbox::System::implementation::UserDisplayInfo>(ID);
    }

    bool User::IsGuest()
    {
        return false;
    }

    bool User::IsSignedIn()
    {
        return true;
    }

    winrt::Windows::Xbox::System::UserLocation User::Location()
    {
        return winrt::Windows::Xbox::System::UserLocation::Local;
    }

    winrt::Windows::Xbox::System::User User::Sponsor()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::System", "Unimplemented: Sponsor");
        throw hresult_not_implemented();
    }

    hstring User::XboxUserHash()
    {
        return winrt::to_hstring(id);
    }

    hstring User::XboxUserId()
    {
        return winrt::to_hstring(id);
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring method, hstring url, hstring headers)
    {
        co_return winrt::make<GetTokenAndSignatureResult>();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring method, hstring url, hstring headers, uint32_t __bodySize, uint8_t body)
    {
        co_return winrt::make<GetTokenAndSignatureResult>();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring method, hstring url, hstring headers, hstring body)
    {
        co_return winrt::make<GetTokenAndSignatureResult>();
    }
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::OnlineStateChangedEventArgs>> User::m_OnlineStateChanged{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs>> User::m_UserAdded{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserRemovedEventArgs>> User::m_UserRemoved{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceAddedEventArgs>> User::m_AudioDeviceAdded{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceRemovedEventArgs>> User::m_AudioDeviceRemoved{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceChangedEventArgs>> User::m_AudioDeviceChanged{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignInCompletedEventArgs>> User::m_SignInCompleted{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutStartedEventArgs>> User::m_SignOutStarted{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutCompletedEventArgs>> User::m_SignOutCompleted{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserDisplayInfoChangedEventArgs>> User::m_UserDisplayInfoChanged{};
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::System::User> User::a_users{};
}
