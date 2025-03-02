#pragma once
#include "Windows.Xbox.Multiplayer.MultiplayerSessionReference.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct MultiplayerSessionReference : MultiplayerSessionReferenceT<MultiplayerSessionReference>
    {
        MultiplayerSessionReference() = default;

        MultiplayerSessionReference(hstring const& sessionName, hstring const& serviceConfigurationId, hstring const& sessionTemplateName);
        hstring SessionName();
        hstring ServiceConfigurationId();
        hstring SessionTemplateName();
    };
}
namespace winrt::Windows::Xbox::Multiplayer::factory_implementation
{
    struct MultiplayerSessionReference : MultiplayerSessionReferenceT<MultiplayerSessionReference, implementation::MultiplayerSessionReference>
    {
    };
}
