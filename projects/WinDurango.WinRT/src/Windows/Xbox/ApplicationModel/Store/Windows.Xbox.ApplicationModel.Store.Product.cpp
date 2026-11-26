#include "Windows.Xbox.ApplicationModel.Store.Product.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::ApplicationModel::Store::implementation
{
    hstring ProductPurchasedEventArgs::Receipt()
    {
        return L"0";
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowPurchaseAsync(winrt::Windows::Xbox::System::User unk, hstring unka)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowDetailsAsync(winrt::Windows::Xbox::System::User unk, hstring unka)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowMarketplaceAsync(winrt::Windows::Xbox::System::User unk, winrt::Windows::Xbox::ApplicationModel::Store::ProductItemTypes unka, hstring unkaa, winrt::Windows::Xbox::ApplicationModel::Store::ProductItemTypes unkaaa)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowRedeemCodeAsync(winrt::Windows::Xbox::System::User unk, hstring unka)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowSubscriptionAsync(winrt::Windows::Xbox::System::User unk, hstring unka, uint32_t unkaa)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::ApplicationModel::Store::PrivilegeCheckResult> Product::CheckPrivilegeAsync(winrt::Windows::Xbox::System::User unk, uint32_t unka, bool unkaa, hstring unkaaa)
    {
        co_return PrivilegeCheckResult::NoIssue;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::ApplicationModel::Store::PrivilegeCheckResult> Product::CheckPrivilegesAsync(winrt::Windows::Xbox::System::User unk, winrt::Windows::Foundation::Collections::IVectorView<uint32_t> unka, bool unkaa, hstring unkaaa)
    {
        co_return PrivilegeCheckResult::NoIssue;
    }
    winrt::event_token Product::ProductPurchased(winrt::Windows::Xbox::ApplicationModel::Store::ProductPurchasedEventHandler const& handler)
    {
        return {};
    }
    void Product::ProductPurchased(winrt::event_token const& token) noexcept
    {

    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowPurchaseForStoreIdAsync(winrt::Windows::Xbox::System::User unk, hstring unka)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowDetailsForStoreIdAsync(winrt::Windows::Xbox::System::User unk, hstring unka)
    {
        co_return;
    }

    winrt::event<winrt::Windows::Xbox::ApplicationModel::Store::ProductPurchasedEventHandler> Product::e_ProductPurchased{};
}
