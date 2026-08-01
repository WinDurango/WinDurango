#include "EraNetworking.h"

HRESULT NetworkInformationEra::__abi_GetConnectionProfiles(__FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile **ConnectionProfiles)
{
    return m_realNetworkInformation->GetConnectionProfiles(ConnectionProfiles);
}

HRESULT NetworkInformationEra::__abi_GetInternetConnectionProfile(ABI::Windows::Networking::Connectivity::IConnectionProfile **ConnectionProfile)
{
    return m_realNetworkInformation->GetInternetConnectionProfile(ConnectionProfile);
}

HRESULT NetworkInformationEra::__abi_GetLanIdentifiers(__FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier **LanIdentifiers)
{
    return m_realNetworkInformation->GetLanIdentifiers(LanIdentifiers);
}

HRESULT NetworkInformationEra::__abi_GetHostNames(__FIVectorView_1_Windows__CNetworking__CHostName **HostNames)
{
    return m_realNetworkInformation->GetHostNames(HostNames);
}

HRESULT NetworkInformationEra::__abi_GetProxyConfigurationAsync(ABI::Windows::Foundation::IUriRuntimeClass *URI, __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration **ProxyConfiguration)
{
    return m_realNetworkInformation->GetProxyConfigurationAsync(URI, ProxyConfiguration);
}

HRESULT NetworkInformationEra::__abi_GetSortedEndpointPairs(__FIIterable_1_Windows__CNetworking__CEndpointPair *DestinationList, ABI::Windows::Networking::HostNameSortOptions SortOptions, __FIVectorView_1_Windows__CNetworking__CEndpointPair **EndpointPairs)
{
    return m_realNetworkInformation->GetSortedEndpointPairs(DestinationList, SortOptions, EndpointPairs);
}

HRESULT NetworkInformationEra::__abi_add_NetworkStatusChanged(ABI::Windows::Networking::Connectivity::INetworkStatusChangedEventHandler *Handler, EventRegistrationToken *Token)
{
    return m_realNetworkInformation->add_NetworkStatusChanged(Handler, Token);
}

HRESULT NetworkInformationEra::__abi_remove_NetworkStatusChanged(EventRegistrationToken Token)
{
    return m_realNetworkInformation->remove_NetworkStatusChanged(Token);
}

HRESULT NetworkInformationEra::QueryInterface(const IID &riid, void **ppvObject)
{
    if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
    {
        *ppvObject = static_cast<IActivationFactory *>(this);
        AddRef();
        return S_OK;
    }

    if (riid == __uuidof(INetworkInformationEra) || riid == __uuidof(ABI::Windows::Networking::Connectivity::INetworkInformationStatics))
    {
        *ppvObject = static_cast<INetworkInformationEra*>(this);
        AddRef();
        return S_OK;
    }

    char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
    OLECHAR iidwstr[sizeof(iidstr)];
    StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
    WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
    MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);

    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG NetworkInformationEra::AddRef()
{
    return InterlockedIncrement(&m_RefCount);
}

ULONG NetworkInformationEra::Release()
{
    ULONG RefCount = InterlockedDecrement(&m_RefCount);
    if (!RefCount) delete this;
    return RefCount;
}

HRESULT NetworkInformationEra::GetIids(ULONG *iidCount, IID **iids)
{
    return m_realFactory->GetIids(iidCount, iids);
}

HRESULT NetworkInformationEra::GetRuntimeClassName(HSTRING *className)
{
    return m_realFactory->GetRuntimeClassName(className);
}

HRESULT NetworkInformationEra::GetTrustLevel(TrustLevel *trustLevel)
{
    return m_realFactory->GetTrustLevel(trustLevel);
}
