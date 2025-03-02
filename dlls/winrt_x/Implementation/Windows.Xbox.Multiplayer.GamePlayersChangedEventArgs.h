#pragma once
#include "Windows.Xbox.Multiplayer.GamePlayersChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct GamePlayersChangedEventArgs : GamePlayersChangedEventArgsT<GamePlayersChangedEventArgs>
    {
        GamePlayersChangedEventArgs() = default;

        winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GameSession();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer> AvailablePlayers();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayerDeviceGroup> AvailablePlayersGroupedByDevice();
    };
}
