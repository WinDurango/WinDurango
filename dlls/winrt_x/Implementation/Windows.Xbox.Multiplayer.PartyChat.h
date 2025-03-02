#pragma once
#include "Windows.Xbox.Multiplayer.PartyChat.g.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    struct PartyChat
    {
        PartyChat() = default;

        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyChatView> GetPartyChatViewAsync();
        static winrt::event_token PartyChatViewChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);
        static void PartyChatViewChanged(winrt::event_token const& token) noexcept;
        static bool IsPartyChatActive();
        static bool IsPartyChatSuppressed();
        static void IsPartyChatSuppressed(bool value);
        static winrt::event_token IsPartyChatActiveChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler);
        static void IsPartyChatActiveChanged(winrt::event_token const& token) noexcept;
        static winrt::event_token IsPartyChatSuppressedChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler);
        static void IsPartyChatSuppressedChanged(winrt::event_token const& token) noexcept;
    };
}
namespace winrt::Windows::Xbox::Multiplayer::factory_implementation
{
    struct PartyChat : PartyChatT<PartyChat, implementation::PartyChat>
    {
    };
}
