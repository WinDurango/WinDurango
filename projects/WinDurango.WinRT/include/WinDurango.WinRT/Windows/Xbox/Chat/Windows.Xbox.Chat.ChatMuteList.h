#pragma once
#include "Windows.Xbox.Chat.ChatMuteList.g.h"

namespace winrt::Windows::Xbox::Chat::implementation
{
    struct ChatMuteList
    {
        ChatMuteList() = default;

        static winrt::event_token UserMuteStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Chat::UserMuteStateChangedEventArgs> const& handler);
        static void UserMuteStateChanged(winrt::event_token const& token) noexcept;
    };
}
namespace winrt::Windows::Xbox::Chat::factory_implementation
{
    struct ChatMuteList : ChatMuteListT<ChatMuteList, implementation::ChatMuteList>
    {
    };
}
