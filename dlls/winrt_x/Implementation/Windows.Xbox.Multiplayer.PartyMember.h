#pragma once
#include "Windows.Xbox.Multiplayer.PartyMember.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyMember : PartyMemberT<PartyMember>
    {
        PartyMember() = default;

        hstring XboxUserId();
        bool IsLocal();
        winrt::Windows::Foundation::DateTime JoinTime();
    };
}
