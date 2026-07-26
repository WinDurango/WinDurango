#include "Windows.Xbox.Multiplayer.PartyConfig.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    bool g_suppressGameSessionReadyToast = false;

    hstring PartyChatMember::XboxUserId()
    {
        return userId;
    }
    uint8_t PartyChatMember::IsLocal()
    {
        return isLocal;
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyChatMember> PartyChatView::Members()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: Members");
        throw hresult_not_implemented();
    }
    bool PartyConfig::SuppressGameSessionReadyToast()
    {
        return g_suppressGameSessionReadyToast;
    }
    void PartyConfig::SuppressGameSessionReadyToast(bool value)
    {
        g_suppressGameSessionReadyToast = value;
    }
    winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode PartyConfig::SuppressGameSessionReadyToastMode()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: SuppressGameSessionReadyToastMode");
        throw hresult_not_implemented();
    }
    void PartyConfig::SuppressGameSessionReadyToastMode(winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Unimplemented: SuppressGameSessionReadyToastMode(SuppressGameSessionReadyToastMode)");
        if (value == winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode::Always) {
            p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Setting Game Session Ready Toast Mode = Always");
        } else {
            p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Multiplayer", "Setting Game Session Ready Toast Mode = WhenTitleIsInFocus");
        }
    }
}
