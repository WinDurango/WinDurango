#include "Windows.Xbox.Management.Deployment.DownloadableContentPackageManager.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Management::Deployment::implementation
{
    bool CheckForUpdateResult::IsUpdateAvailable()
    {
        return updateAvail;
    }
    bool CheckForUpdateResult::IsUpdateMandatory()
    {
        return updateMandatory;
    }
    uint32_t ChunkCompletedEventArgs::ChunkId()
    {
        return chunkID;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> ChunkSpecifiers::Languages()
    {
        return langs;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> ChunkSpecifiers::Tags()
    {
        return tags;
    }
    hstring ContentPackage::TitleId()
    {
        return title;
    }
    hstring ContentPackage::ContentId()
    {
        return content;
    }
    hstring ContentPackage::ProductId()
    {
        return product;
    }
    hstring ContentPackage::PackageFullName()
    {
        return packageFullName;
    }
    uint32_t ContentPackage::ContentType()
    {
        return contentType;
    }
    hstring ContentPackage::DisplayName()
    {
        return displayName;
    }
    hstring ContentPackage::Description()
    {
        return description;
    }
    hstring ContentPackage::Publisher()
    {
        return publisher;
    }
    hstring ContentPackage::Version()
    {
        return version;
    }
    winrt::hresult LicenseTerminatedEventArgs::Reason()
    {
        return reason;
    }
    hstring LicenseTerminatedEventArgs::PackageFullName()
    {
        return packageFullName;
    }
    hstring LicenseTerminatedEventArgs::UserXuidIfCausedBySignout()
    {
        return userXuid;
    }
    winrt::hresult RequestUpdatePackageResult::Result()
    {
        return result;
    }
    winrt::Windows::Xbox::Management::Deployment::TransferOperationType DownloadableContentPackageInstallCompletedEventArgs::OperationType()
    {
        return operationType;
    }
    hstring DownloadableContentPackageInstallCompletedEventArgs::PackageFullName()
    {
        return packageFullName;
    }
    winrt::guid DownloadableContentPackageInstallCompletedEventArgs::ContentId()
    {
        return contentId;
    }
    winrt::hresult DownloadableContentPackageInstallCompletedEventArgs::Result()
    {
        return result;
    }
    hstring DownloadableContentPackage::TitleId()
    {
        return title;
    }
    hstring DownloadableContentPackage::ContentId()
    {
        return content;
    }
    hstring DownloadableContentPackage::ProductId()
    {
        return product;
    }
    hstring DownloadableContentPackage::PackageFullName()
    {
        return packageFullName;
    }
    hstring DownloadableContentPackage::MountPath()
    {
        return mountPath;
    }
    bool DownloadableContentPackage::IsMounted()
    {
        return isMounted;
    }
    uint32_t DownloadableContentPackage::ContentType()
    {
        return contentType;
    }
    hstring DownloadableContentPackage::DisplayName()
    {
        return displayName;
    }
    hstring DownloadableContentPackage::Description()
    {
        return description;
    }
    hstring DownloadableContentPackage::Publisher()
    {
        return publisher;
    }
    hstring DownloadableContentPackage::Version()
    {
        return version;
    }
    hstring DownloadableContentPackage::Mount()
    {
        return mount;
    }
    void DownloadableContentPackage::Unmount()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: Unmount");
        throw hresult_not_implemented();
    }
    void DownloadableContentPackage::CheckLicense(bool& unk, bool& unka)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Management::Deployment", "Unimplemented: CheckLicense");
        unk = false; // trial
        unka = true; // licence
    }
    winrt::event_token DownloadableContentPackage::LicenseTerminated(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackage, winrt::Windows::Xbox::Management::Deployment::LicenseTerminatedEventArgs> const& handler)
    {
        return e_LicenseTerminated.add(handler);
    }
    void DownloadableContentPackage::LicenseTerminated(winrt::event_token const& token) noexcept
    {
        e_LicenseTerminated.remove(token);
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackage> DownloadableContentPackageManager::FindPackages(winrt::Windows::Xbox::Management::Deployment::InstalledPackagesFilter const& unk)
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackage>().GetView();
    }
    winrt::event_token DownloadableContentPackageManager::DownloadableContentPackageInstallCompleted(winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackageInstallCompletedEventHandler const& handler)
    {
        return {};
    }
    void DownloadableContentPackageManager::DownloadableContentPackageInstallCompleted(winrt::event_token const& token) noexcept
    {

    }
    winrt::event_token DownloadableContentPackageManager::DownloadableContentPackageInstallCompletedWithDetails(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackageInstallCompletedEventArgs> const& handler)
    {
        return {};
    }
    void DownloadableContentPackageManager::DownloadableContentPackageInstallCompletedWithDetails(winrt::event_token const& token) noexcept
    {

    }
}
