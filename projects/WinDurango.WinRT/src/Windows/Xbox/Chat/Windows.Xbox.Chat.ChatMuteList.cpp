#include "Windows.Xbox.Chat.ChatMuteList.h"

namespace winrt::Windows::Xbox::Chat::implementation
{
    winrt::event_token ChatMuteList::UserMuteStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Chat::UserMuteStateChangedEventArgs> const& handler)
    {
        return {};
    }
    void ChatMuteList::UserMuteStateChanged(winrt::event_token const& token) noexcept
    {
        
    }
}
