#pragma once
#include "Windows.Xbox.Multiplayer.UserPartyAssociation.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct UserPartyAssociation : UserPartyAssociationT<UserPartyAssociation>
    {
        UserPartyAssociation() = default;

        winrt::Windows::Foundation::Collections::IVectorView<hstring> QueriedXboxUserIds();
        hstring PartyId();
    };
}
