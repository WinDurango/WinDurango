#include "Windows.Xbox.Storage.ConnectedStorageSpace.h"
#include "Windows.Xbox.Storage.ConnectedStorageContainer.h"
#include "Windows.Xbox.System.User.h"
#include "Windows.Xbox.Storage.ContainerInfoQueryResult.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForUserAsync(winrt::Windows::Xbox::System::User user)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_UserStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_UserStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForMachineAsync()
    {
        if (machineStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            machineStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_MachineStorage);
        }

        co_return machineStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForMachineAsync(hstring serviceConfigurationId)
    {
        if (machineStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            machineStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_MachineStorage);
        }

        co_return machineStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_UserStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr))
        {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(wd::WinRT::g_UserStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Xbox::System::User ConnectedStorageSpace::User()
    {
        return winrt::Windows::Xbox::System::implementation::User::Users().GetAt(1); //Fun Fact: Forza has a seizure if you pass 0 as the id :)
    }
    hstring ConnectedStorageSpace::ServiceConfigurationId()
    {
        return L"";
    }
    bool ConnectedStorageSpace::IsReadOnly()
    {
        return false;
    }
    winrt::Windows::Xbox::Storage::ConnectedStorageContainer ConnectedStorageSpace::CreateContainer(hstring const& containerName)
    {
        if (wd::WinRT::g_UserStorage == nullptr || wd::WinRT::g_MachineStorage == nullptr)
            assert("g_UserStorage is null");

        if (!containers)
        {
            containers = winrt::single_threaded_map<hstring, winrt::Windows::Xbox::Storage::ConnectedStorageContainer>();
        }

        if (!containers.HasKey(containerName))
        {
            winrt::Windows::Xbox::Storage::ConnectedStorageContainer container = winrt::make<ConnectedStorageContainer>(containerName, m_connectedStorage);

            containers.Insert(containerName, container);
            return container;
        }

        return containers.Lookup(containerName);
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageSpace::DeleteContainerAsync(hstring containerName)
    {
        co_await m_connectedStorage->DeleteContainer(containerName);
        containers.Remove(containerName);
    }
    winrt::Windows::Xbox::Storage::ContainerInfoQueryResult ConnectedStorageSpace::CreateContainerInfoQuery(hstring const& unk)
    {
        return winrt::make<winrt::Windows::Xbox::Storage::implementation::ContainerInfoQueryResult>(unk, m_connectedStorage);
    }
    winrt::Windows::Foundation::IAsyncOperation<int32_t> ConnectedStorageSpace::GetRemainingBytesInQuotaAsync()
    {
        co_return INT_MAX; // Infinite storage remaining :)
    }
    winrt::Windows::Foundation::IAsyncOperation<int64_t> ConnectedStorageSpace::GetRemainingBytesInQuota64Async()
    {
        co_return INT64_MAX; // Infinite storage remaining :)
    }
}
