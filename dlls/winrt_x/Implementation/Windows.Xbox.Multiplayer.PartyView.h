#pragma once
#include "Windows.Xbox.Multiplayer.PartyView.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyView : PartyViewT<PartyView>
    {
        PartyView() = default;

        winrt::Windows::Foundation::Collections::IVectorView<hstring> ReservedMembers();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyMember> Members();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyMemberDeviceGroup> MembersGroupedByDevice();
        winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference MatchSession();
        winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GameSession();
        bool IsPartyInAnotherTitle();
        winrt::Windows::Xbox::Multiplayer::SessionJoinability Joinability();
    };
}
