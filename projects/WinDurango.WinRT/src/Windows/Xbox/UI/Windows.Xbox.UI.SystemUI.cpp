#include "Windows.Xbox.UI.SystemUI.h"
#include "Windows.Xbox.UI.AccountPickerResult.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::UI::implementation
{
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowEpgAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::IInspectable>> propertySet)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowEpgAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowMiniguideAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowMiniguideAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowProfileCardAsync(winrt::Windows::Xbox::System::User requestingUser, hstring targetXuid)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowProfileCardAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowSendInvitesAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowSendInvitesAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::AccountPickerResult> SystemUI::ShowAccountPickerAsync(winrt::Windows::Xbox::Input::Controller controller, winrt::Windows::Xbox::UI::AccountPickerOptions options)
    {
        co_return winrt::make<winrt::Windows::Xbox::UI::implementation::AccountPickerResult>();
    }
    winrt::Windows::Foundation::IAsyncOperation<hstring> SystemUI::ShowVirtualKeyboardAsync(hstring defaultText, hstring titleText, hstring descriptionText, winrt::Windows::Xbox::UI::VirtualKeyboardInputScope inputScope)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowVirtualKeyboardAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchPartyAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: LaunchPartyAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchAchievementsAsync(winrt::Windows::Xbox::System::User requestingUser, uint32_t titleId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: LaunchAchievementsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowPartyAndSendPartyInvitesAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> recipientUserIdList)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowPartyAndSendPartyInvitesAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowCreateLookingForGroupAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> preselectedTags, hstring preselectedDescription, uint32_t defaultNeedCount)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowCreateLookingForGroupAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowUserLookingForGroupsAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowUserLookingForGroupsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowLookingForGroupResultsAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> tags)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowLookingForGroupResultsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowSendMultiplayerActivityGameInvites(winrt::Windows::Xbox::System::User requestingUser, uint32_t titleId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowSendMultiplayerActivityGameInvites");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowStateShareAsync(winrt::Windows::Xbox::System::User requestingUser, uint32_t xblTitleId, hstring linkToken)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowStateShareAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchKinectSetupAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: LaunchKinectSetupAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchRecentPlayersAsync(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: LaunchRecentPlayersAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::SnapDefaultBroadcastApp(winrt::Windows::Xbox::System::User requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: SnapDefaultBroadcastApp");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowComposeMessageAsync(winrt::Windows::Xbox::System::User requestingUser, hstring defaultMessageText, winrt::Windows::Foundation::Collections::IVector<hstring> recipientUserIdList)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowComposeMessageAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::AddRemoveFriendResult> SystemUI::ShowAddRemoveFriendAsync(winrt::Windows::Xbox::System::User requestingUser, hstring targetUserId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowAddRemoveFriendAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<hstring>> SystemUI::ShowPeoplePickerAsync(winrt::Windows::Xbox::System::User requestingUser, hstring promptText, winrt::Windows::Foundation::Collections::IVectorView<hstring> selectFromUserIdList, winrt::Windows::Foundation::Collections::IVectorView<hstring> preselectedUserIdList, uint32_t minimumSelectionCount, uint32_t maximumSelectionCount)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowPeoplePickerAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> SystemUI::TrySnapSelf()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: TrySnapSelf");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> SystemUI::TrySnapOther(winrt::Windows::Foundation::Uri snapTargetUri, winrt::Windows::Xbox::System::User user)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: TrySnapOther");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowMiniguideWithCommandAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Xbox::UI::MiniguideCommand initialCommand)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowMiniguideWithCommandAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<hstring> SystemUI::ShowVirtualKeyboardWithOptionsAsync(winrt::Windows::Xbox::UI::KeyboardOptions options)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowVirtualKeyboardWithOptionsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowSendGameInvitesAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceToInviteTo, hstring customActivationContext)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowSendGameInvitesAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowSendGameInvitesWithDisplayTextAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceToInviteTo, hstring inviteDisplayTextId, hstring customActivationContext)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ShowSendGameInvitesWithDisplayTextAsync");
        throw hresult_not_implemented();
    }
    void SystemUI::SetNotificationPositionHint(winrt::Windows::Xbox::UI::NotificationPositionHint const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: SetNotificationPositionHint");
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::WebAuthenticationResult> SystemUI::AuthenticateWithCallbackUriAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Xbox::UI::WebAuthenticationOptions options, winrt::Windows::Foundation::Uri requestUri, winrt::Windows::Foundation::Uri callbackUri)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: AuthenticateWithCallbackUriAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::WebAuthenticationResult> SystemUI::AuthenticateWithoutCallbackUriAsync(winrt::Windows::Xbox::System::User requestingUser, winrt::Windows::Xbox::UI::WebAuthenticationOptions options, winrt::Windows::Foundation::Uri requestUri)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: AuthenticateWithoutCallbackUriAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Uri SystemUI::GetCurrentApplicationCallbackUri(winrt::Windows::Xbox::System::User const& requestingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: GetCurrentApplicationCallbackUri");
        throw hresult_not_implemented();
    }
    hstring WebAuthenticationResult::ResponseData()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ResponseData");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::UI::WebAuthenticationStatus WebAuthenticationResult::ResponseStatus()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ResponseStatus");
        throw hresult_not_implemented();
    }
    uint32_t WebAuthenticationResult::ResponseErrorDetail()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::UI", "Unimplemented: ResponseErrorDetail");
        throw hresult_not_implemented();
    }
}
