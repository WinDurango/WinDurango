#include "Windows.Xbox.Management.Deployment.PackageTransferManager.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Management::Deployment::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Management::Deployment::CheckForUpdateResult> PackageTransferManager::CheckForUpdateAsync(winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackage unk)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: CheckForUpdateAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Management::Deployment::RequestUpdatePackageResult> PackageTransferManager::RequestUpdatePackageAsync(winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackage unk)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: RequestUpdatePackageAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Management::Deployment::RequestUpdatePackageResult> PackageTransferManager::RequestUpdateCurrentPackageAsync()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: RequestUpdateCurrentPackageAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Management::Deployment::PackageTransferManager PackageTransferManager::Current()
    {
        return winrt::make<PackageTransferManager>();
    }
    winrt::Windows::Xbox::Management::Deployment::PackageTransferManager PackageTransferManager::Create(winrt::Windows::ApplicationModel::Package const &package)
    {
        return winrt::make<PackageTransferManager>();
    }
    winrt::Windows::Xbox::Management::Deployment::ChunkSpecifiers PackageTransferManager::AvailableChunkSpecifiers()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: AvailableChunkSpecifiers");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Management::Deployment::InstallationState PackageTransferManager::GetInstallationState(winrt::Windows::Foundation::Collections::IIterable<uint32_t> const& unk)
    {
        return winrt::Windows::Xbox::Management::Deployment::InstallationState::Installed;
    }
    winrt::Windows::Xbox::Management::Deployment::InstallationState PackageTransferManager::GetInstallationState(winrt::Windows::Xbox::Management::Deployment::ChunkSpecifiers const& unk)
    {
        return winrt::Windows::Xbox::Management::Deployment::InstallationState::Installed;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Management::Deployment::PackageTransferWatcher> PackageTransferManager::AddChunkSpecifiersAsync(winrt::Windows::Xbox::Management::Deployment::ChunkSpecifiers unk)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: AddChunkSpecifiersAsync");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction PackageTransferManager::RemoveChunkSpecifiersAsync(winrt::Windows::Xbox::Management::Deployment::ChunkSpecifiers unk)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: RemoveChunkSpecifiersAsync");
        return {};
    }
    winrt::Windows::Xbox::Management::Deployment::PackageTransferType PackageTransferManager::TransferType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: TransferType");
        throw hresult_not_implemented();
    }
    void PackageTransferManager::UpdateInstallOrder(winrt::Windows::Foundation::Collections::IIterable<uint32_t> const& unk, winrt::Windows::Xbox::Management::Deployment::UpdateInstallOrderBehavior const& unka)
    {

    }
    bool PackageTransferManager::IsChunkInstalled(uint32_t chunkId)
    {
        return true;
    }
    bool PackageTransferManager::AreChunksInstalled(winrt::Windows::Foundation::Collections::IIterable<uint32_t> const &chunkIds)
    {
        return true;
    }
    uint32_t PackageTransferManager::FindChunkFromFile(hstring const& unk)
    {
        return 0;
    }
    winrt::Windows::Xbox::Management::Deployment::PackageTransferStatus PackageTransferManager::TransferStatus()
    {
        return PackageTransferStatus::None;
    }
}
