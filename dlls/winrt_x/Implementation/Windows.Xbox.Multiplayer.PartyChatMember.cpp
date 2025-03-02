#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyChatMember.h"
#include "Windows.Xbox.Multiplayer.PartyChatMember.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    hstring PartyChatMember::XboxUserId()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    bool PartyChatMember::IsLocal()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
