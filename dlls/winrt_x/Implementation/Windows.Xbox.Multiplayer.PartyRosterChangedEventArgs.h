#pragma once
#include "Windows.Xbox.Multiplayer.PartyRosterChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyRosterChangedEventArgs : PartyRosterChangedEventArgsT<PartyRosterChangedEventArgs>
    {
        PartyRosterChangedEventArgs() = default;

        winrt::Windows::Foundation::Collections::IVectorView<hstring> AddedMembers();
        winrt::Windows::Foundation::Collections::IVectorView<hstring> AddedReservedMembers();
        winrt::Windows::Foundation::Collections::IVectorView<hstring> RemovedMembers();
        winrt::Windows::Foundation::Collections::IVectorView<hstring> RemovedReservedMembers();
        winrt::Windows::Xbox::Multiplayer::PartyView PartyView();
    };
}
