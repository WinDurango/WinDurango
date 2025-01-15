#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Storage.h>

// forward declare
namespace winrt::Windows::Xbox::Storage
{
	struct ContainerInfo2;
	struct BlobInfo;
}

namespace WinDurango::impl
{
	class ConnectedStorage
	{
	public:
		winrt::Windows::Foundation::IAsyncAction InitializeStorage( const wchar_t* name );
		winrt::Windows::Foundation::IAsyncAction CreateContainer(winrt::hstring name) const;
		winrt::Windows::Foundation::IAsyncAction Read(winrt::hstring containerName, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer> data) const;
		winrt::Windows::Foundation::IAsyncAction Upload(winrt::hstring containerName, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<winrt::hstring> blobsToDelete, winrt::hstring displayName = {}) const;
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> GetBlobInfoAsync(winrt::hstring parentContainerName, winrt::hstring blobNamePrefix);
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> GetContainerInfo2Async( );

		static winrt::Windows::Foundation::IAsyncAction CreateDirectories(const wchar_t* storageType, winrt::hstring &storagePath);
		static winrt::Windows::Foundation::IAsyncOperation<bool> DoesFolderExist(winrt::hstring path);
		static winrt::Windows::Foundation::IAsyncOperation<bool> DoesFileExist(winrt::Windows::Storage::StorageFolder folder, winrt::hstring path);

	private:
		static winrt::hstring ObtainPackageName( );

		winrt::hstring m_storagePath;
	};

	inline ConnectedStorage* s_userStorage;
	inline ConnectedStorage* s_machineStorage;
}
