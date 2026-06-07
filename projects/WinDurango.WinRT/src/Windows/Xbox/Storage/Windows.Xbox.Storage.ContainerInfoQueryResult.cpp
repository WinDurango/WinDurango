#include "Windows.Xbox.Storage.ContainerInfoQueryResult.h"
#include "WinDurangoWinRT.h"
#include "Windows.Xbox.Storage.ConnectedStorage.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo>> ContainerInfoQueryResult::GetContainerInfoAsync(uint32_t unk, uint32_t unka)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Storage", "Unimplemented: GetContainerInfoAsync(uint32_t, uint32_t)");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo>> ContainerInfoQueryResult::GetContainerInfoAsync()
    {
        co_return co_await m_connectedStorage->GetContainerInfoAsync();
    }
    winrt::Windows::Foundation::IAsyncOperation<uint32_t> ContainerInfoQueryResult::GetItemCountAsync()
    {
        auto items = co_await m_connectedStorage->GetContainerInfoAsync();
        co_return items.Size();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> ContainerInfoQueryResult::GetContainerInfo2Async(uint32_t unk, uint32_t unka)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Storage", "Unimplemented: GetContainerInfo2Async(uint32_t, uint32_t)");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> ContainerInfoQueryResult::GetContainerInfo2Async()
    {
        co_return co_await m_connectedStorage->GetContainerInfo2Async();
    }
}
