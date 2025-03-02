#pragma once
#include "Windows.Xbox.Multiplayer.GameSessionReadyEventArgs.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct GameSessionReadyEventArgs : GameSessionReadyEventArgsT<GameSessionReadyEventArgs>
    {
        GameSessionReadyEventArgs() = default;

        winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GameSession();
    };
}
