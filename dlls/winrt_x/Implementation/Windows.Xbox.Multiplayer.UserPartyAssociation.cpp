#include "pch.h"
#include "Windows.Xbox.Multiplayer.UserPartyAssociation.h"
#include "Windows.Xbox.Multiplayer.UserPartyAssociation.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Foundation::Collections::IVectorView<hstring> UserPartyAssociation::QueriedXboxUserIds()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    hstring UserPartyAssociation::PartyId()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
