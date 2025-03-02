#include "pch.h"
#include "Windows.Xbox.Multiplayer.GamePlayersChangedEventArgs.h"
#include "Windows.Xbox.Multiplayer.GamePlayersChangedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GamePlayersChangedEventArgs::GameSession()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer> GamePlayersChangedEventArgs::AvailablePlayers()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayerDeviceGroup> GamePlayersChangedEventArgs::AvailablePlayersGroupedByDevice()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
