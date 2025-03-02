#pragma once
#include "Windows.Xbox.Multiplayer.MatchStatusChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct MatchStatusChangedEventArgs : MatchStatusChangedEventArgsT<MatchStatusChangedEventArgs>
    {
        MatchStatusChangedEventArgs() = default;

        winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference MatchSession();
        winrt::Windows::Xbox::Multiplayer::MatchStatus MatchStatus();
    };
}
