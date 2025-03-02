#pragma once
#include "Windows.Xbox.Multiplayer.GamePlayerDeviceGroup.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct GamePlayerDeviceGroup : GamePlayerDeviceGroupT<GamePlayerDeviceGroup>
    {
        GamePlayerDeviceGroup() = default;

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::GamePlayer> Players();
    };
}
