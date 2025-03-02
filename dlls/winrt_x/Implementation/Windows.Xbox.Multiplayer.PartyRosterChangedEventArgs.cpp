#include "pch.h"
#include "Windows.Xbox.Multiplayer.PartyRosterChangedEventArgs.h"
#include "Windows.Xbox.Multiplayer.PartyRosterChangedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Multiplayer::implementation
{
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::AddedMembers()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::AddedReservedMembers()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::RemovedMembers()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<hstring> PartyRosterChangedEventArgs::RemovedReservedMembers()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Multiplayer::PartyView PartyRosterChangedEventArgs::PartyView()
    {
        printf("%s called\n", __FUNCTION__); throw hresult_not_implemented();
    }
}
