#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Networking.Connectivity.h>
#include <wrl.h>
#include <windows.foundation.collections.h>
#include <windows.networking.connectivity.h>

using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL;

MIDL_INTERFACE("06B35320-5BBA-4381-B8C4-A72F467E704F")
INetworkInformationEra : public IInspectable
{
public:
    virtual HRESULT __abi_GetConnectionProfiles(__FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile** ConnectionProfiles) = 0;
    virtual HRESULT __abi_GetInternetConnectionProfile(ABI::Windows::Networking::Connectivity::IConnectionProfile** ConnectionProfile) = 0;
    virtual HRESULT __abi_GetLanIdentifiers(__FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier** LanIdentifiers) = 0;
    virtual HRESULT __abi_GetHostNames(__FIVectorView_1_Windows__CNetworking__CHostName** HostNames) = 0;
    virtual HRESULT __abi_GetProxyConfigurationAsync(ABI::Windows::Foundation::IUriRuntimeClass* URI, __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration** ProxyConfiguration) = 0;
    virtual HRESULT __abi_GetSortedEndpointPairs(__FIIterable_1_Windows__CNetworking__CEndpointPair* DestinationList, ABI::Windows::Networking::HostNameSortOptions SortOptions, __FIVectorView_1_Windows__CNetworking__CEndpointPair** EndpointPairs) = 0;
    virtual HRESULT __abi_add_NetworkStatusChanged(ABI::Windows::Networking::Connectivity::INetworkStatusChangedEventHandler* Handler, EventRegistrationToken* Token) = 0;
    virtual HRESULT __abi_remove_NetworkStatusChanged(EventRegistrationToken Token) = 0;
};

// Main Wrapper
class NetworkInformationEra : public RuntimeClass<IActivationFactory, INetworkInformationEra>
{
public:
    NetworkInformationEra(ComPtr<IActivationFactory> realFactory)
    {
        m_realFactory = realFactory;
        HRESULT hr = m_realFactory.As(&m_realNetworkInformation);
        if (FAILED(hr))
            throw E_FAIL;
        AddRef();
    }

    // IActivationFactory
    HRESULT STDMETHODCALLTYPE ActivateInstance(__RPC__deref_out_opt IInspectable **instance) override
    {
        return m_realFactory->ActivateInstance(instance);
    }

    // INetworkInformation
    HRESULT __abi_GetConnectionProfiles(__FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile **ConnectionProfiles) override;
    HRESULT __abi_GetInternetConnectionProfile(ABI::Windows::Networking::Connectivity::IConnectionProfile** ConnectionProfile) override;
    HRESULT __abi_GetLanIdentifiers(__FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier** LanIdentifiers) override;
    HRESULT __abi_GetHostNames(__FIVectorView_1_Windows__CNetworking__CHostName** HostNames) override;
    HRESULT __abi_GetProxyConfigurationAsync(ABI::Windows::Foundation::IUriRuntimeClass* URI, __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration** ProxyConfiguration) override;
    HRESULT __abi_GetSortedEndpointPairs(__FIIterable_1_Windows__CNetworking__CEndpointPair* DestinationList, ABI::Windows::Networking::HostNameSortOptions SortOptions, __FIVectorView_1_Windows__CNetworking__CEndpointPair** EndpointPairs) override;
    HRESULT __abi_add_NetworkStatusChanged(ABI::Windows::Networking::Connectivity::INetworkStatusChangedEventHandler* Handler, EventRegistrationToken* Token) override;
    HRESULT __abi_remove_NetworkStatusChanged(EventRegistrationToken Token) override;


    // IActivationFactory (IInspectable + IUnknown)
    HRESULT QueryInterface(const IID &riid, void **ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

    HRESULT GetIids(ULONG *iidCount, IID **iids) override;
    HRESULT GetRuntimeClassName(HSTRING *className) override;
    HRESULT GetTrustLevel(TrustLevel *trustLevel) override;

private:
    ULONG m_RefCount = 0;
    ComPtr<ABI::Windows::Networking::Connectivity::INetworkInformationStatics> m_realNetworkInformation;
    ComPtr<IActivationFactory> m_realFactory;
};