#include "pch.h"
#include "Windows.Xbox.Multiplayer.MultiplayerSessionReference.h"
#include "Windows.Xbox.Multiplayer.MultiplayerSessionReference.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    MultiplayerSessionReference::MultiplayerSessionReference(hstring const& sessionName, hstring const& serviceConfigurationId, hstring const& sessionTemplateName)
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    hstring MultiplayerSessionReference::SessionName()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    hstring MultiplayerSessionReference::ServiceConfigurationId()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    hstring MultiplayerSessionReference::SessionTemplateName()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
