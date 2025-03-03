#include "pch.h"
#include "Windows.Xbox.System.User.h"
#include "Windows.Xbox.System.User.g.cpp"
#include "Windows.Xbox.System.UserDisplayInfo.h"

namespace winrt::Windows::Xbox::System::implementation
{
    //winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs>> m_userAddedEvent;
    UserOnlineState User::OnlineState()
    {
        return UserOnlineState::Offline;
    }
    winrt::event_token User::OnlineStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::OnlineStateChangedEventArgs> const& handler)
    {
        return m_onlineStateChangedEvent.add(handler);
    }
    void User::OnlineStateChanged(winrt::event_token const& token) noexcept
    {
        m_onlineStateChangedEvent.remove(token);
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> User::Users()
    {
		wprintf(L"User || Users Queried!\n");
        if (staticUsers == Foundation::Collections::IVector<winrt::Windows::Xbox::System::User>(nullptr) || staticUsers.Size( ) == 0) {
            staticUsers = winrt::single_threaded_vector<System::User>( );

            for (int i = 0; i < 4; i++)
            {
                wprintf(L"User || User %d Created!\n", i);
                staticUser = winrt::make<User>(i);
                staticUsers.Append(staticUser);
                continue;
            }
        }

        return staticUsers.GetView();
    }
    winrt::event_token User::UserAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs> const& handler)
    {
        return m_userAddedEvent.add(handler);
    }
    void User::UserAdded(winrt::event_token const& token) noexcept
    {
        m_userAddedEvent.remove(token);
    }
    winrt::event_token User::UserRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserRemovedEventArgs> const& handler)
    {
        return m_userRemovedEvent.add(handler);
    }
    void User::UserRemoved(winrt::event_token const& token) noexcept
    {
        m_userRemovedEvent.remove(token);
    }
    winrt::Windows::Xbox::System::User User::GetUserById(uint32_t id)
    {
        printf("!!!! Windows.Xbox.System.User GetUserById | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureForAllUsersAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers, array_view<uint8_t const> body)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureForAllUsersAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers, hstring body)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureForAllUsersAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token User::AudioDeviceAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceAddedEventArgs> const& handler)
    {
        return {};
    }
    void User::AudioDeviceAdded(winrt::event_token const& token) noexcept
    {
        return;
    }
    winrt::event_token User::AudioDeviceRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceRemovedEventArgs> const& handler)
    {
        printf("!!!! Windows.Xbox.System.User AudioDeviceRemoved | NOT IMPLEMENTED !!!!\n");
        return {};
    }
    void User::AudioDeviceRemoved(winrt::event_token const& token) noexcept
    {
        printf("!!!! Windows.Xbox.System.User AudioDeviceRemoved | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token User::AudioDeviceChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceChangedEventArgs> const& handler)
    {
        printf("!!!! Windows.Xbox.System.User AudioDeviceChanged | NOT IMPLEMENTED !!!!\n");
        return {};
    }
    void User::AudioDeviceChanged(winrt::event_token const& token) noexcept
    {
        printf("!!!! Windows.Xbox.System.User AudioDeviceChanged | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token User::SignInCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignInCompletedEventArgs> const& handler)
    {
        return {};
    }
    void User::SignInCompleted(winrt::event_token const& token) noexcept
    {
        printf("!!!! Windows.Xbox.System.User SignInCompleted | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token User::SignOutStarted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutStartedEventArgs> const& handler)
    {
        return m_signOutStartedEvent.add(handler);
    }
    void User::SignOutStarted(winrt::event_token const& token) noexcept
    {
        m_signOutStartedEvent.remove(token);
    }
    winrt::event_token User::SignOutCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutCompletedEventArgs> const& handler)
    {
        return {};
    }
    void User::SignOutCompleted(winrt::event_token const& token) noexcept
    {
        return;
    }
    winrt::event_token User::UserDisplayInfoChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserDisplayInfoChangedEventArgs> const& handler)
    {
        printf("!!!! Windows.Xbox.System.User UserDisplayInfoChanged | NOT IMPLEMENTED !!!!\n");
        return {};
    }
    void User::UserDisplayInfoChanged(winrt::event_token const& token) noexcept
    {
        printf("!!!! Windows.Xbox.System.User UserDisplayInfoChanged | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::guid User::GetNetworkCacheIdForUsers(winrt::Windows::Foundation::Collections::IVectorView<uint32_t> const& users)
    {
        printf("!!!! Windows.Xbox.System.User GetNetworkCacheIdForUsers | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    uint32_t User::Id()
    {
        return m_id;
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::IAudioDeviceInfo> User::AudioDevices()
    {
        printf("!!!! Windows.Xbox.System.User AudioDevices | NOT IMPLEMENTED !!!!\n");
        return winrt::single_threaded_vector<System::IAudioDeviceInfo>( ).GetView( );
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IController> User::Controllers()
    {
        printf("!!!! Windows.Xbox.System.User Controllers | NOT IMPLEMENTED !!!!\n");
        return winrt::single_threaded_vector<Input::IController>( ).GetView( );
    }
    winrt::Windows::Xbox::System::UserDisplayInfo User::DisplayInfo()
    {
        hstring gamertag = to_hstring(m_id);
        return winrt::make<implementation::UserDisplayInfo>(gamertag);
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
        printf("!!!! Windows.Xbox.System.User Location | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::System::User User::Sponsor()
    {
        printf("!!!! Windows.Xbox.System.User Sponsor | NOT IMPLEMENTED !!!!\n");
        return nullptr;
    }
    hstring User::XboxUserHash()
    {
        printf("!!!! Windows.Xbox.System.User XboxUserHash | NOT IMPLEMENTED-- !!!!\n");
        return winrt::to_hstring(m_id);
    }
    hstring User::XboxUserId()
    {
        printf("!!!! Windows.Xbox.System.User XboxUserId | NOT IMPLEMENTED !!!!\n");
        return winrt::to_hstring(m_id);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers, array_view<uint8_t const> body)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> User::GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers, hstring body)
    {
        printf("!!!! Windows.Xbox.System.User GetTokenAndSignatureAsync | NOT IMPLEMENTED !!!!\n");
        throw hresult_not_implemented();
    }
}
