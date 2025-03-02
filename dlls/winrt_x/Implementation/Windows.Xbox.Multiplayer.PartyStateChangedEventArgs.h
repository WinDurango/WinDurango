#pragma once
#include "Windows.Xbox.Multiplayer.PartyStateChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyStateChangedEventArgs : PartyStateChangedEventArgsT<PartyStateChangedEventArgs>
    {
        PartyStateChangedEventArgs() = default;

        winrt::Windows::Xbox::Multiplayer::PartyView PartyView();
    };
}
