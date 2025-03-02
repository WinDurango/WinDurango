#pragma once
#include "Windows.Xbox.Multiplayer.GamePlayer.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct GamePlayer : GamePlayerT<GamePlayer>
    {
        GamePlayer() = default;

        hstring XboxUserId();
        winrt::Windows::Foundation::DateTime LastInvitedTime();
        winrt::Windows::Foundation::DateTime PartyJoinTime();
    };
}
