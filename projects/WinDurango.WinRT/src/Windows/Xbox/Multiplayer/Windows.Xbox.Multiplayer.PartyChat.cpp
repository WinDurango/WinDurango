#include "Windows.Xbox.Multiplayer.PartyChat.h"
#include "WinDurangoWinRT.h"

static bool g_isChatSuppresed = false;
namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Multiplayer::PartyChatView> PartyChat::GetPartyChatViewAsync()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: GetPartyChatViewAsync");
        throw hresult_not_implemented();
    }
    winrt::event_token PartyChat::PartyChatViewChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        return {};
    }
    void PartyChat::PartyChatViewChanged(winrt::event_token const& token) noexcept
    {

    }
    bool PartyChat::IsPartyChatActive()
    {
        throw false;
    }
    bool PartyChat::IsPartyChatSuppressed()
    {
        return g_isChatSuppresed;
    }
    void PartyChat::IsPartyChatSuppressed(bool value)
    {
        g_isChatSuppresed = value;
    }
    winrt::event_token PartyChat::IsPartyChatActiveChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler)
    {
        return {};
    }
    void PartyChat::IsPartyChatActiveChanged(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token PartyChat::IsPartyChatSuppressedChanged(winrt::Windows::Foundation::EventHandler<bool> const& handler)
    {
        return {};
    }
    void PartyChat::IsPartyChatSuppressedChanged(winrt::event_token const& token) noexcept
    {

    }
}
