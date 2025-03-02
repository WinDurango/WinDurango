#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyConfig.h"
#include "Windows.Xbox.Multiplayer.PartyConfig.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    bool PartyConfig::SuppressGameSessionReadyToast()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyConfig::SuppressGameSessionReadyToast(bool value)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode PartyConfig::SuppressGameSessionReadyToastMode()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    void PartyConfig::SuppressGameSessionReadyToastMode(winrt::Windows::Xbox::Multiplayer::SuppressGameSessionReadyToastMode const& value)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
