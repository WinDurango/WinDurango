#pragma once
#include "Windows.Xbox.Multiplayer.Party.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct Party
    {
        Party() = default;

        static winrt::Windows::Foundation::IAsyncAction RegisterGameSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference);
        static winrt::Windows::Foundation::IAsyncAction RegisterMatchSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference);
        static winrt::Windows::Foundation::IAsyncAction InviteToPartyAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> usersToInvite);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> GetPartyViewAsync();
        static winrt::Windows::Foundation::IAsyncAction AddLocalUsersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> localUsersToAdd);
        static winrt::Windows::Foundation::IAsyncAction PullInactivePlayersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference);
        static winrt::Windows::Foundation::IAsyncAction PullReservedPlayersAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer>> GetAvailableGamePlayersAsync(winrt::Windows::Xbox::System::User actingUser);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayerDeviceGroup>> GetAvailableGamePlayersGroupedByDeviceAsync(winrt::Windows::Xbox::System::User actingUser);
        static winrt::Windows::Foundation::IAsyncAction SwitchPartyTitleAsync(winrt::Windows::Xbox::System::User actingUser);
        static winrt::event_token GameSessionReady(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GameSessionReadyEventArgs> const& handler);
        static void GameSessionReady(winrt::event_token const& token) noexcept;
        static winrt::event_token PartyStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyStateChangedEventArgs> const& handler);
        static void PartyStateChanged(winrt::event_token const& token) noexcept;
        static winrt::event_token PartyRosterChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::PartyRosterChangedEventArgs> const& handler);
        static void PartyRosterChanged(winrt::event_token const& token) noexcept;
        static winrt::event_token MatchStatusChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::MatchStatusChangedEventArgs> const& handler);
        static void MatchStatusChanged(winrt::event_token const& token) noexcept;
        static winrt::event_token GamePlayersChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Multiplayer::GamePlayersChangedEventArgs> const& handler);
        static void GamePlayersChanged(winrt::event_token const& token) noexcept;
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> GetPartyViewAsyncEx(winrt::Windows::Xbox::Multiplayer::PartyFlags flags);
        static winrt::Windows::Foundation::IAsyncAction RemoveLocalUsersAsync(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> localUsersToRemove);
        static hstring PartyId();
        static winrt::Windows::Foundation::IAsyncAction DisassociateGameSessionAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceToDisassociate);
        static winrt::Windows::Foundation::IAsyncAction RegisterGameSessionCompareAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceComparand);
        static winrt::Windows::Foundation::IAsyncAction RegisterMatchSessionCompareAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference sessionReferenceComparand);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::UserPartyAssociation>> GetUserPartyAssociationsAsync(winrt::Windows::Xbox::System::User actingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> targetXboxUserIds);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyView> GetPartyViewByPartyIdAsync(winrt::Windows::Xbox::System::User actingUser, hstring partyId);
        static winrt::Windows::Foundation::IAsyncAction JoinPartyByIdAsync(winrt::Windows::Xbox::System::User actingUser, hstring partyId);
        static winrt::Windows::Xbox::Multiplayer::SessionJoinability Joinability();
        static void Joinability(winrt::Windows::Xbox::Multiplayer::SessionJoinability const& value);
    };
}
namespace winrt::Windows::Xbox::Multiplayer::factory_implementation
{
    struct Party : PartyT<Party, implementation::Party>
    {
    };
}
