#include "Windows.Xbox.Storage.ConnectedStorage.h"
#include <winrt/Windows.Storage.FileProperties.h>

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::CreateContainer(winrt::hstring name) const
{
    if (!co_await DoesFolderExist(m_storagePath + L"\\" + name))
    {
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(m_storagePath);
        co_await folder.CreateFolderAsync(name);
    }
}

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::Read(winrt::hstring containerName, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer> data) const
{
    if (!DoesFolderExist(m_storagePath + L"\\" + containerName))
    {
        co_await CreateContainer(containerName);
    }

    auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(m_storagePath + L"\\" + containerName);

    for (auto const &pair : data)
    {
        auto fileName = pair.Key();
        auto file = co_await folder.GetFileAsync(fileName);
        auto fileBuffer = co_await winrt::Windows::Storage::FileIO::ReadBufferAsync(file);
        auto bufferByteAccess = fileBuffer.as<Windows::Storage::Streams::IBufferByteAccess>();
        uint8_t *fileData = nullptr;
        bufferByteAccess->Buffer(&fileData);
        auto dataBuffer = pair.Value();
        auto dataBufferByteAccess = dataBuffer.as<Windows::Storage::Streams::IBufferByteAccess>();
        uint8_t *dataBufferData = nullptr;
        dataBufferByteAccess->Buffer(&dataBufferData);
        memcpy(dataBufferData, fileData, fileBuffer.Length());
    }

    co_return;
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer>> wd::WinRT::ConnectedStorage::Get(winrt::hstring containerName, winrt::Windows::Foundation::Collections::IIterable<winrt::hstring> blobsToRead) const
{
    if (!co_await DoesFolderExist(m_storagePath + L"\\" + containerName))
    {
        co_await CreateContainer(containerName);
    }

    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer> data = winrt::single_threaded_map<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer>();
    auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(m_storagePath + L"\\" + containerName);

    for (auto const &blobs : blobsToRead)
    {
        try {
            winrt::Windows::Storage::IStorageFile file = co_await folder.GetFileAsync(blobs);
            auto fileBuffer = co_await winrt::Windows::Storage::FileIO::ReadBufferAsync(file);
            data.Insert(blobs, fileBuffer);
        } catch (...) {
            p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::ConnectedStorage", "File doesnt exist: {}", winrt::to_string(blobs));
        }
    }
    co_await Read(containerName, data.GetView());

    co_return data.GetView();
}

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::Upload(winrt::hstring containerName, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<winrt::hstring> blobsToDelete, winrt::hstring displayName) const
{
    if (!co_await DoesFolderExist(m_storagePath + L"\\" + containerName))
    {
        co_await CreateContainer(containerName);
    }

    if (!displayName.empty())
    {
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(m_storagePath + L"\\" + containerName);
        auto file = co_await folder.CreateFileAsync(L"DisplayName.txt", winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting);
        co_await winrt::Windows::Storage::FileIO::WriteTextAsync(file, displayName);
    }

    auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(m_storagePath + L"\\" + containerName);

    if (blobsToWrite != nullptr)
        for (auto const &pair : blobsToWrite)
        {
            auto fileName = pair.Key();
            auto dataBuffer = pair.Value();
            auto file = co_await folder.CreateFileAsync(
                fileName, winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting);
            co_await winrt::Windows::Storage::FileIO::WriteBufferAsync(file, dataBuffer);
        }

    if (blobsToDelete != nullptr)
        for (auto const &blobName : blobsToDelete)
        {
            auto file = co_await folder.GetFileAsync(blobName);
            co_await file.DeleteAsync();
        }

    co_return;
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> wd::WinRT::ConnectedStorage::GetBlobInfoAsync(winrt::hstring parentContainerName, winrt::hstring blobNamePrefix)
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Storage::BlobInfo> blobInfoVector = winrt::single_threaded_vector<winrt::Windows::Xbox::Storage::BlobInfo>();
    winrt::hstring s_prefix = blobNamePrefix;

    winrt::hstring storagePath = m_storagePath + L"\\" + parentContainerName;
    if (!co_await DoesFolderExist(storagePath))
        co_return blobInfoVector.GetView();

    auto storageFolder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(storagePath);
    auto files = co_await storageFolder.GetFilesAsync();

    for (auto file : files)
    {
        std::wstring_view str_view{file.Name()};
        if (!str_view._Starts_with(s_prefix))
            continue;

        winrt::Windows::Storage::FileProperties::BasicProperties folderProperties = co_await file.GetBasicPropertiesAsync();

        uint32_t size = folderProperties.Size();

        blobInfoVector.Append({file.Name(), size});
    }
    co_return blobInfoVector.GetView();
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> wd::WinRT::ConnectedStorage::GetContainerInfo2Async()
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Storage::ContainerInfo2> containerInfoVector = winrt::single_threaded_vector<winrt::Windows::Xbox::Storage::ContainerInfo2>();

    winrt::hstring storagePath = m_storagePath;
    auto storageFolder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(storagePath);
    auto folders = co_await storageFolder.GetFoldersAsync();

    for (auto folder : folders)
    {
        auto folderProperties = co_await folder.GetBasicPropertiesAsync();

        uint64_t size = folderProperties.Size();
        winrt::Windows::Foundation::DateTime date = folderProperties.DateModified();

        winrt::hstring displayName = {};
        if (co_await DoesFileExist(folder, L"DisplayName.txt"))
        {
            auto file = co_await folder.GetFileAsync(L"DisplayName.txt");
            displayName = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);
        }

        if (displayName.empty())
            displayName = folder.DisplayName();

        containerInfoVector.Append({folder.Name(), size, displayName, date, false});
    }
    co_return containerInfoVector.GetView();
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo>> wd::WinRT::ConnectedStorage::GetContainerInfoAsync()
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Storage::ContainerInfo> containerInfoVector = winrt::single_threaded_vector<winrt::Windows::Xbox::Storage::ContainerInfo>();

    winrt::hstring storagePath = m_storagePath;
    auto storageFolder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(storagePath);
    auto folders = co_await storageFolder.GetFoldersAsync();

    for (auto folder : folders)
    {
        auto folderProperties = co_await folder.GetBasicPropertiesAsync();

        uint64_t size = folderProperties.Size();
        winrt::Windows::Foundation::DateTime date = folderProperties.DateModified();

        winrt::hstring displayName = {};
        if (co_await DoesFileExist(folder, L"DisplayName.txt"))
        {
            auto file = co_await folder.GetFileAsync(L"DisplayName.txt");
            displayName = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);
        }

        if (displayName.empty())
            displayName = folder.DisplayName();

        containerInfoVector.Append({folder.Name()});
    }
    co_return containerInfoVector.GetView();
}

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::DeleteContainer(winrt::hstring containerName)
{
    winrt::hstring containerPath = m_storagePath + L"\\" + containerName;
    if (co_await DoesFolderExist(containerPath))
    {
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(containerPath);
        co_await folder.DeleteAsync();
    }
}

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::CreateDirectories(const wchar_t *storageType,
                                                                                        winrt::hstring &storagePath)
{
    co_await winrt::resume_background();

    winrt::hstring packageName = ObtainPackageName();
    if (packageName.empty())
    {
        co_return;
    }

    winrt::hstring folderPath = winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path() + L"\\WinDurango";

    if (!co_await DoesFolderExist(folderPath))
    {
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path());
        co_await folder.CreateFolderAsync(L"WinDurango");
    }

    folderPath = folderPath + L"\\" + storageType;

    if (!co_await DoesFolderExist(folderPath))
    {
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path() + L"\\WinDurango");
        co_await folder.CreateFolderAsync(storageType);
    }

    storagePath = folderPath;
}

winrt::Windows::Foundation::IAsyncOperation<bool> wd::WinRT::ConnectedStorage::DoesFolderExist(winrt::hstring path)
{
    try
    {
        co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path);
    }
    catch (...)
    {
        co_return false;
    }

    co_return true;
}

winrt::Windows::Foundation::IAsyncOperation<bool> wd::WinRT::ConnectedStorage::DoesFileExist(winrt::Windows::Storage::StorageFolder folder, winrt::hstring path)
{
    try
    {
        co_await folder.GetFileAsync(path);
    }
    catch (...)
    {
        co_return false;
    }

    co_return true;
}

winrt::hstring wd::WinRT::ConnectedStorage::ObtainPackageName()
{
    return winrt::Windows::ApplicationModel::Package::Current().Id().FamilyName();
}

winrt::Windows::Foundation::IAsyncAction wd::WinRT::ConnectedStorage::InitializeStorage(const wchar_t *name)
{
    co_await CreateDirectories(name, m_storagePath);
}