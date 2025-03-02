#pragma once
#include "Windows.Xbox.Multiplayer.PartyChatMember.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyChatMember : PartyChatMemberT<PartyChatMember>
    {
        PartyChatMember() = default;

        hstring XboxUserId();
        bool IsLocal();
    };
}
