#pragma once
#include "Windows.Xbox.Multiplayer.PartyConfig.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyConfig
    {
        PartyConfig() = default;

        static bool SuppressGameSessionReadyToast();
        static void SuppressGameSessionReadyToast(bool value);
        static winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode SuppressGameSessionReadyToastMode();
        static void SuppressGameSessionReadyToastMode(winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode const& value);
    };
}
namespace winrt::Windows::Xbox::Multiplayer::factory_implementation
{
    struct PartyConfig : PartyConfigT<PartyConfig, implementation::PartyConfig>
    {
    };
}
