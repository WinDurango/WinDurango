#include "Windows.Xbox.Achievements.AchievementNotifier.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Achievements::implementation
{
    winrt::event<winrt::Windows::Xbox::Achievements::AchievementUnlockedHandler> g_AchievementUnlockedHandle;
    winrt::Windows::Xbox::Achievements::AchievementSource AchievementNotifier::GetTitleIdFilteredSource()
    {
        return winrt::make<implementation::AchievementSource>();
    }

    winrt::Windows::Xbox::Achievements::AchievementSource AchievementNotifier::GetUnfilteredSource()
    {
        return winrt::make<implementation::AchievementSource>();
    }

    winrt::event_token AchievementSource::AchievementUnlocked(winrt::Windows::Xbox::Achievements::AchievementUnlockedHandler const& handler)
    {
        return g_AchievementUnlockedHandle.add(handler);
    }

    void AchievementSource::AchievementUnlocked(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: AchievementUnlocked");
    }

    winrt::Windows::System::User AchievementUnlockedEventArgs::User()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: User");
        throw hresult_not_implemented();
    }

    hstring AchievementUnlockedEventArgs::TitleId()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: TitleId");
        throw hresult_not_implemented();
    }
    
    hstring AchievementUnlockedEventArgs::ServiceConfigurationId()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: ServiceConfigurationId");
        throw hresult_not_implemented();
    }

    hstring AchievementUnlockedEventArgs::AchievementId()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: AchievementId");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::DateTime AchievementUnlockedEventArgs::UnlockTime()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: UnlockTime");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Uri AchievementUnlockedEventArgs::ExtendedInfoUrl()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: ExtendedInfoUrl");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> AchievementUnlockedEventArgs::InAppRewardValue()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Achievements", "Unimplemented: InAppRewardValue");
        throw hresult_not_implemented();
    }
}
