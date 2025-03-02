#include "pch.h"
#include "Windows.Xbox.Multiplayer.GamePlayer.h"
#include "Windows.Xbox.Multiplayer.GamePlayer.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    hstring GamePlayer::XboxUserId()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime GamePlayer::LastInvitedTime()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime GamePlayer::PartyJoinTime()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
