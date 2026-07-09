#pragma once
#include "Windows.Xbox.Chat.UserMuteStateChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Chat::implementation
{
    struct UserMuteStateChangedEventArgs : UserMuteStateChangedEventArgsT<UserMuteStateChangedEventArgs>
    {
        UserMuteStateChangedEventArgs() = default;

        winrt::Windows::Xbox::System::User User();
        hstring XboxUserId();
        bool Muted();
    };
}
