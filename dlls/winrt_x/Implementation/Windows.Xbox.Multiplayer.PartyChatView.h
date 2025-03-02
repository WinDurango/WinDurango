#pragma once
#include "Windows.Xbox.Multiplayer.PartyChatView.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyChatView : PartyChatViewT<PartyChatView>
    {
        PartyChatView() = default;

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyChatMember> Members();
    };
}
