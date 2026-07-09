#include "Windows.Xbox.Chat.UserMuteStateChangedEventArgs.h"

namespace winrt::Windows::Xbox::Chat::implementation
{
    winrt::Windows::Xbox::System::User UserMuteStateChangedEventArgs::User()
    {
        throw hresult_not_implemented();
    }
    hstring UserMuteStateChangedEventArgs::XboxUserId()
    {
        throw hresult_not_implemented();
    }
    bool UserMuteStateChangedEventArgs::Muted()
    {
        throw hresult_not_implemented();
    }
}
