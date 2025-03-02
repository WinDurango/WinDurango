#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyStateChangedEventArgs.h"
#include "Windows.Xbox.Multiplayer.PartyStateChangedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Xbox::Multiplayer::PartyView PartyStateChangedEventArgs::PartyView()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
