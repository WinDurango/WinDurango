#include "Windows.Xbox.Networking.SecureDeviceAssociationTemplate.h"
#include "Windows.Xbox.Networking.Development.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Networking::implementation
{
    winrt::Windows::Xbox::Networking::SecureDeviceAssociation SecureDeviceAssociationIncomingEventArgs::Association()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: Association");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAssociationState SecureDeviceAssociationStateChangedEventArgs::OldState()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: OldState");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAssociationState SecureDeviceAssociationStateChangedEventArgs::NewState()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: NewState");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAssociationTemplate SecureDeviceAssociationTemplate::GetTemplateByName(hstring const& name)
    {
        return winrt::make<SecureDeviceAssociationTemplate>();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Networking::SecureDeviceAssociationTemplate> SecureDeviceAssociationTemplate::Templates()
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Networking::SecureDeviceAssociationTemplate>().GetView();
    }
    winrt::event_token SecureDeviceAssociationTemplate::AssociationIncoming(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Networking::SecureDeviceAssociationTemplate, winrt::Windows::Xbox::Networking::SecureDeviceAssociationIncomingEventArgs> const& handler)
    {
        return e_AssociationIncoming.add(handler);
    }
    void SecureDeviceAssociationTemplate::AssociationIncoming(winrt::event_token const& token) noexcept
    {
        e_AssociationIncoming.remove(token);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Networking::SecureDeviceAssociation> SecureDeviceAssociationTemplate::CreateAssociationAsync(winrt::Windows::Xbox::Networking::SecureDeviceAddress secureDeviceAddress, winrt::Windows::Xbox::Networking::CreateSecureDeviceAssociationBehavior behavior)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateAssociationAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Networking::SecureDeviceAssociation> SecureDeviceAssociationTemplate::CreateAssociationForPortsAsync(winrt::Windows::Xbox::Networking::SecureDeviceAddress secureDeviceAddress, winrt::Windows::Xbox::Networking::CreateSecureDeviceAssociationBehavior behavior, hstring initiatorPort, hstring acceptorPort)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateAssociationForPortsAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer> SecureDeviceAssociationTemplate::CreateCertificateRequestAsync(hstring subjectName)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: CreateCertificateRequestAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SecureDeviceAssociationTemplate::InstallCertificateAsync(winrt::Windows::Storage::Streams::IBuffer certificateBuffer)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: InstallCertificateAsync");
        throw hresult_not_implemented();
    }
    hstring SecureDeviceAssociationTemplate::Name()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: Name");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceSocketDescription SecureDeviceAssociationTemplate::InitiatorSocketDescription()
    {
        return winrt::make<winrt::Windows::Xbox::Networking::implementation::SecureDeviceSocketDescription>();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceSocketDescription SecureDeviceAssociationTemplate::AcceptorSocketDescription()
    {
        return winrt::make<winrt::Windows::Xbox::Networking::implementation::SecureDeviceSocketDescription>();
    }
    winrt::Windows::Xbox::Networking::SecureDeviceAssociationUsage SecureDeviceAssociationTemplate::AllowedUsages()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: AllowedUsages");
        throw hresult_not_implemented();
    }
    hstring SecureDeviceAssociationTemplate::RelyingParty()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: RelyingParty");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Networking::ProtocolParserDescription> SecureDeviceAssociationTemplate::ProtocolParserDescriptions()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: ProtocolParserDescriptions");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Networking::QualityOfServiceMetric> SecureDeviceAssociationTemplate::QualityOfServiceMetricPathPriorities()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: QualityOfServiceMetricPathPriorities");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Networking::MultiplayerSessionRequirement SecureDeviceAssociationTemplate::MultiplayerSessionRequirement()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: MultiplayerSessionRequirement");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Networking::SecureDeviceAssociation> SecureDeviceAssociationTemplate::Associations()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Networking", "Unimplemented: Associations");
        throw hresult_not_implemented();
    }
}
