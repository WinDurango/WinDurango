#include "Windows.Xbox.Storage.ConnectedStorageContainer.h"
#include "WinDurangoWinRT.h"
#include "Windows.Xbox.Storage.ConnectedStorageSpace.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> BlobInfoQueryResult::GetBlobInfoAsync(uint32_t startIndex, uint32_t maxNumberOfItems)
    {
        co_return co_await m_connectedStorage->GetBlobInfoAsync(parentName, prefix);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> BlobInfoQueryResult::GetBlobInfoAsync()
    {
        co_return co_await m_connectedStorage->GetBlobInfoAsync(parentName, prefix);
    }
    winrt::Windows::Foundation::IAsyncOperation<uint32_t> BlobInfoQueryResult::GetItemCountAsync()
    {
        auto blobs = co_await m_connectedStorage->GetBlobInfoAsync(parentName, prefix);
        co_return blobs.Size();
    }
    ConnectedStorageContainer::ConnectedStorageContainer(hstring name, wd::WinRT::ConnectedStorage *connectedStorage)
    {
        containerName = name;
        m_connectedStorage = connectedStorage;
    }
    hstring ConnectedStorageContainer::Name()
    {
        return containerName;
    }
    winrt::Windows::Xbox::Storage::ConnectedStorageSpace ConnectedStorageContainer::OwningSpace()
    {
        return winrt::make<winrt::Windows::Xbox::Storage::implementation::ConnectedStorageSpace>();
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitUpdatesAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete)
    {
        co_await m_connectedStorage->Upload(Name(), blobsToWrite, blobsToDelete);
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::ReadAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToRead)
    {
        co_await m_connectedStorage->Read(Name(), blobsToRead);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer>> ConnectedStorageContainer::GetAsync(winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToRead)
    {
        auto result = co_await m_connectedStorage->Get(Name(), blobsToRead);
        co_return result;
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitPropertySetUpdatesAsync(winrt::Windows::Foundation::Collections::IPropertySet blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Storage", "Unimplemented: SubmitPropertySetUpdatesAsync(IPropertySet, IIterable<hstring>)");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitUpdatesAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete, hstring displayName)
    {
        co_await m_connectedStorage->Upload(Name(), blobsToWrite, blobsToDelete, displayName);
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitPropertySetUpdatesAsync(winrt::Windows::Foundation::Collections::IPropertySet blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete, hstring displayName)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Storage", "Unimplemented: SubmitPropertySetUpdatesAsync(IPropertySet, IIterable<hstring>, hstring)");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Storage::BlobInfoQueryResult ConnectedStorageContainer::CreateBlobInfoQuery(hstring const &blobNamePrefix)
    {
        return winrt::make<winrt::Windows::Xbox::Storage::implementation::BlobInfoQueryResult>(Name(), blobNamePrefix, m_connectedStorage);
    }
}
