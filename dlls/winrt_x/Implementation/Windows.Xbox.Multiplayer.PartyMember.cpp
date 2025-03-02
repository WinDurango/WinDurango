#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyMember.h"
#include "Windows.Xbox.Multiplayer.PartyMember.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    hstring PartyMember::XboxUserId()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    bool PartyMember::IsLocal()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime PartyMember::JoinTime()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
