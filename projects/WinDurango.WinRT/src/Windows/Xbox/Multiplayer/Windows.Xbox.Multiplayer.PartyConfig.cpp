#include "Windows.Xbox.Multiplayer.PartyConfig.h"
#include "WinDurangoWinRT.h"
#include "Windows.Xbox.System.User.h"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    bool g_suppressGameSessionReadyToast = true;
    SuppressGameSessionReadyToastMode g_suppressGameSessionReadyToastMode = SuppressGameSessionReadyToastMode::Always;

    hstring PartyChatMember::XboxUserId()
    {
        return L"1";
    }
    uint8_t PartyChatMember::IsLocal()
    {
        return true;
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Multiplayer::PartyChatMember> PartyChatView::Members()
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Multiplayer::PartyChatMember>().GetView();
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
        return g_suppressGameSessionReadyToastMode;
    }
    void PartyConfig::SuppressGameSessionReadyToastMode(winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode const& value)
    {
        g_suppressGameSessionReadyToastMode = value;
    }
}
