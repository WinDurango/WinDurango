#include "Windows.Xbox.ApplicationModel.Store.Configuration.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::ApplicationModel::Store::implementation
{
    hstring Configuration::MarketplaceId()
    {
        return L"0";
    }
}
