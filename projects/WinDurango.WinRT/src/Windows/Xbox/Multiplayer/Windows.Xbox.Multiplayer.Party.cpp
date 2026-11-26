#include "Windows.Xbox.Multiplayer.Party.h"
#include "Windows.Xbox.Multiplayer.PartyView.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    hstring GamePlayer::XboxUserId()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: XboxUserId");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime GamePlayer::LastInvitedTime()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: LastInvitedTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime GamePlayer::PartyJoinTime()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: PartyJoinTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer> GamePlayerDeviceGroup::Players()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: Players");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GameSessionReadyEventArgs::GameSession()
    {
        return gameSession;
    }
    winrt::Windows::Xbox::Multiplayer::PartyView PartyStateChangedEventArgs::PartyView()
    {
        return partyView;
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::AddedMembers()
    {
        return addedMembers;
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::AddedReservedMembers()
    {
        return addedReservedMembers;
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::RemovedMembers()
    {
        return removedMembers;
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::RemovedReservedMembers()
    {
        return removedReservedMembers;
    }
    winrt::Windows::Xbox::Multiplayer::PartyView PartyRosterChangedEventArgs::PartyView()
    {
        return partyView;
    }
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference MatchStatusChangedEventArgs::MatchSession()
    {
        return matchSession;
    }
    winrt::Windows::Xbox::Multiplayer::MatchStatus MatchStatusChangedEventArgs::MatchStatus()
    {
        return matchStatus;
    }
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GamePlayersChangedEventArgs::GameSession()
    {
        return gameSession;
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer> GamePlayersChangedEventArgs::AvailablePlayers()
    {
        return availablePlayers;
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayerDeviceGroup> GamePlayersChangedEventArgs::AvailablePlayersGroupedByDevice()
    {
        return availablePlayersGroupedByDevice;
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> UserPartyAssociation::QueriedXboxUserIds()
    {
        return queriedXboxUserIds;
    }
    hstring UserPartyAssociation::PartyId()
    {
        return partyId;
    }
    winrt::Windows::Foundation::IAsyncAction Party::RegisterGameSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: RegisterGameSessionAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::RegisterMatchSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "RegisterMatchSessionAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::InviteToPartyAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> usersToInvite)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: InviteToPartyAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> Party::GetPartyViewAsync()
    {
        co_return winrt::make<implementation::PartyView>();
    }
    winrt::Windows::Foundation::IAsyncAction Party::AddLocalUsersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> localUsersToAdd)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Party::PullInactivePlayersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Party::PullReservedPlayersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer>> Party::GetAvailableGamePlayersAsync(winrt::Windows::Xbox::System::User actingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: GetAvailableGamePlayersAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayerDeviceGroup>> Party::GetAvailableGamePlayersGroupedByDeviceAsync(winrt::Windows::Xbox::System::User actingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: GetAvailableGamePlayersGroupedByDeviceAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::SwitchPartyTitleAsync(winrt::Windows::Xbox::System::User actingUser)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: SwitchPartyTitleAsync");
        throw hresult_not_implemented();
    }
    winrt::event_token Party::GameSessionReady(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GameSessionReadyEventArgs> const& handler)
    {
        return {};
    }
    void Party::GameSessionReady(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token Party::PartyStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyStateChangedEventArgs> const& handler)
    {
        return {};
    }
    void Party::PartyStateChanged(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token Party::PartyRosterChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyRosterChangedEventArgs> const& handler)
    {
        return {};
    }
    void Party::PartyRosterChanged(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token Party::MatchStatusChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::MatchStatusChangedEventArgs> const& handler)
    {
        return {};
    }
    void Party::MatchStatusChanged(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token Party::GamePlayersChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GamePlayersChangedEventArgs> const& handler)
    {
        return {};
    }
    void Party::GamePlayersChanged(winrt::event_token const& token) noexcept
    {

    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> Party::GetPartyViewAsyncEx(winrt::Windows::Xbox::Multiplayer::PartyFlags flags)
    {
        co_return winrt::make<implementation::PartyView>();
    }
    winrt::Windows::Foundation::IAsyncAction Party::RemoveLocalUsersAsync(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> localUsersToRemove)
    {
        co_return;
    }
    hstring Party::PartyId()
    {
        return L"0";
    }
    winrt::Windows::Foundation::IAsyncAction Party::DisassociateGameSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceToDisassociate)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: DisassociateGameSessionAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::RegisterGameSessionCompareAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceComparand)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: RegisterGameSessionCompareAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::RegisterMatchSessionCompareAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceComparand)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: RegisterMatchSessionCompareAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::UserPartyAssociation>> Party::GetUserPartyAssociationsAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> targetXboxUserIds)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: GetUserPartyAssociationsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> Party::GetPartyViewByPartyIdAsync(winrt::Windows::Xbox::System::User actingUser, hstring partyId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: GetPartyViewByPartyIdAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Party::JoinPartyByIdAsync(winrt::Windows::Xbox::System::User actingUser, hstring partyId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: JoinPartyByIdAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Multiplayer::SessionJoinability Party::Joinability()
    {
        return sessionJoinability;
    }
    void Party::Joinability(winrt::Windows::Xbox::Multiplayer::SessionJoinability const& value)
    {
        sessionJoinability = value;
    }
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GameSessionReadyEventArgs>> Party::e_GameSessionReady{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyStateChangedEventArgs>> Party::e_PartyStateChanged{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyRosterChangedEventArgs>> Party::e_PartyRosterChanged{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::MatchStatusChangedEventArgs>> Party::e_MatchStatusChanged{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GamePlayersChangedEventArgs>> Party::e_GamePlayersChanged{};
    winrt::Windows::Xbox::Multiplayer::SessionJoinability Party::sessionJoinability{};
}
