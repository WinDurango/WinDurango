#include "Windows.Xbox.Networking.SecureDeviceAddress.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Networking::implementation
{
    winrt::Windows::Xbox::Networking::SecureDeviceAddress SecureDeviceAddressFactory::CreateAddressFromBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateAddressFromBuffer");
        throw hresult_not_implemented();
    }
    uint32_t SecureDeviceAddress::CompareBuffers(winrt::Windows::Storage::Streams::IBuffer const& buffer1, winrt::Windows::Storage::Streams::IBuffer const& buffer2)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CompareBuffers");
        throw hresult_not_implemented();
    }
    uint32_t SecureDeviceAddress::CompareBytes(array_view<uint8_t const> bytes1, array_view<uint8_t const> bytes2)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CompareBytes");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAddress SecureDeviceAddress::FromBytes(array_view<uint8_t const> bytes)
    {
        return winrt::make<implementation::SecureDeviceAddress>();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAddress SecureDeviceAddress::GetLocal()
    {
        return winrt::make<implementation::SecureDeviceAddress>();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAddress SecureDeviceAddress::CreateDedicatedServerAddress(hstring const& hostnameOrAddress)
    {
        return winrt::make<implementation::SecureDeviceAddress>();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAddress SecureDeviceAddress::FromBase64String(hstring const& base64String)
    {
        return winrt::make<implementation::SecureDeviceAddress>();
    }
    winrt::event_token SecureDeviceAddress::BufferChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Networking::SecureDeviceAddress, winrt::Windows::Foundation::IInspectable> const& handler)
    {
        return e_BufferChanged.add(handler);
    }
    void SecureDeviceAddress::BufferChanged(winrt::event_token const& token) noexcept
    {
        e_BufferChanged.remove(token);
    }
    winrt::Windows::Storage::Streams::IBuffer SecureDeviceAddress::GetBuffer()
    {
        winrt::Windows::Storage::Streams::IBuffer Buffer(winrt::Windows::Storage::Streams::Buffer(64));
        return Buffer;
    }
    int32_t SecureDeviceAddress::Compare(winrt::Windows::Xbox::Networking::SecureDeviceAddress const& secureDeviceAddress)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: Compare");
        throw hresult_not_implemented();
    }
    hstring SecureDeviceAddress::GetBase64String()
    {
        return L"0";
    }
    bool SecureDeviceAddress::IsLocal()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: IsLocal");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::NetworkAccessType SecureDeviceAddress::NetworkAccessType()
    {
        return NetworkAccessType::Open;
    }
}
