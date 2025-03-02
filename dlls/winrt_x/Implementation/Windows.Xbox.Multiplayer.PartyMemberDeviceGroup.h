#pragma once
#include "Windows.Xbox.Multiplayer.PartyMemberDeviceGroup.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyMemberDeviceGroup : PartyMemberDeviceGroupT<PartyMemberDeviceGroup>
    {
        PartyMemberDeviceGroup() = default;

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyMember> Members();
    };
}
