#include "pch.h"
#include "Windows.Xbox.Multiplayer.MatchStatusChangedEventArgs.h"
#include "Windows.Xbox.Multiplayer.MatchStatusChangedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference MatchStatusChangedEventArgs::MatchSession()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Multiplayer::MatchStatus MatchStatusChangedEventArgs::MatchStatus()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
