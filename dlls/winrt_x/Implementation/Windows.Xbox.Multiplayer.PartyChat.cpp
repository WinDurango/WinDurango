#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyChat.h"
#include "Windows.Xbox.Multiplayer.PartyChat.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyChatView> PartyChat::GetPartyChatViewAsync()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::event_token PartyChat::PartyChatViewChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyChat::PartyChatViewChanged(winrt::event_token const& token) noexcept
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    bool PartyChat::IsPartyChatActive()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    bool PartyChat::IsPartyChatSuppressed()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyChat::IsPartyChatSuppressed(bool value)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::event_token PartyChat::IsPartyChatActiveChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyChat::IsPartyChatActiveChanged(winrt::event_token const& token) noexcept
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::event_token PartyChat::IsPartyChatSuppressedChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyChat::IsPartyChatSuppressedChanged(winrt::event_token const& token) noexcept
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
