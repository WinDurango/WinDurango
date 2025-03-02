#include "pch.h"
#include "Windows.Xbox.Multiplayer.GameSessionReadyEventArgs.h"
#include "Windows.Xbox.Multiplayer.GameSessionReadyEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Xbox::Multiplayer::MultiplayerSessionReference GameSessionReadyEventArgs::GameSession()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
