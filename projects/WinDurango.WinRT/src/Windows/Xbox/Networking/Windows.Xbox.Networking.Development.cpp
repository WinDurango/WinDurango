#include "Windows.Xbox.Networking.Development.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Networking::implementation
{
    hstring SecureDeviceSocketDescription::Name()
    {
        return L"";
    }
    winrt::Windows::Xbox::Networking::SecureIpProtocol SecureDeviceSocketDescription::IpProtocol()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: IpProtocol");
        throw hresult_not_implemented();
    }
    uint16_t SecureDeviceSocketDescription::BoundPortRangeLower()
    {
        return 0;
    }
    uint16_t SecureDeviceSocketDescription::BoundPortRangeUpper()
    {
        return 0;
    }
    winrt::Windows::Xbox::Networking::SecureDeviceSocketUsage SecureDeviceSocketDescription::AllowedUsages()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: AllowedUsages");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAddress Development::CreateSecureDeviceAddressFromHostNames(winrt::Windows::Xbox::Networking::SecureDeviceId const& secureDeviceId, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Networking::HostName> const& hostNames)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateSecureDeviceAddressFromHostNames");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceSocketDescription Development::CreateSecureDeviceSocketDescription(hstring const& name, winrt::Windows::Xbox::Networking::SecureIpProtocol const& secureIpProtocol, uint16_t boundPortRangeLower, uint16_t boundPortRangeUpper, winrt::Windows::Xbox::Networking::SecureDeviceSocketUsage const& allowedUsages)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateSecureDeviceSocketDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAssociationTemplate Development::CreateSecureDeviceAssociationTemplate(hstring const& name, winrt::Windows::Xbox::Networking::SecureDeviceSocketDescription const& initiatorSecureDeviceSocketDescription, winrt::Windows::Xbox::Networking::SecureDeviceSocketDescription const& acceptorSecureDeviceSocketDescription, winrt::Windows::Xbox::Networking::SecureDeviceAssociationUsage const& allowedUsages, hstring const& relyingParty, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Xbox::Networking::ProtocolParserDescription> const& protocolParserDescriptions, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Xbox::Networking::QualityOfServiceMetric> const& qualityOfServiceMetricPathPriorities, winrt::Windows::Xbox::Networking::MultiplayerSessionRequirement const& multiplayerSessionRequirement)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateSecureDeviceAssociationTemplate");
        throw hresult_not_implemented();
    }
}
