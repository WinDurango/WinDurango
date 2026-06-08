#pragma once
#include "Windows.Xbox.Achievements.AchievementSource.g.h"
#include "Windows.Xbox.Achievements.AchievementUnlockedEventArgs.g.h"
#include "Windows.Xbox.Achievements.AchievementNotifier.g.h"

namespace winrt::Windows::Xbox::Achievements::implementation
{
    struct AchievementSource : AchievementSourceT<AchievementSource>
    {
        AchievementSource() = default;

        winrt::event_token AchievementUnlocked(winrt::Windows::Xbox::Achievements::AchievementUnlockedHandler const& handler);
        void AchievementUnlocked(winrt::event_token const& token) noexcept;
    };

    struct AchievementUnlockedEventArgs : AchievementUnlockedEventArgsT<AchievementUnlockedEventArgs>
    {
        AchievementUnlockedEventArgs() = default;

        winrt::Windows::System::User User();
        hstring TitleId();
        hstring ServiceConfigurationId();
        hstring AchievementId();
        winrt::Windows::Foundation::DateTime UnlockTime();
        winrt::Windows::Foundation::Uri ExtendedInfoUrl();
        winrt::Windows::Foundation::Collections::IVectorView<hstring> InAppRewardValue();
    };

    struct AchievementNotifier
    {
        AchievementNotifier() = default;

        static winrt::Windows::Xbox::Achievements::AchievementSource GetTitleIdFilteredSource();
        static winrt::Windows::Xbox::Achievements::AchievementSource GetUnfilteredSource();
    };
}

namespace winrt::Windows::Xbox::Achievements::factory_implementation
{
    struct AchievementNotifier : AchievementNotifierT<AchievementNotifier, implementation::AchievementNotifier>
    {
    };
}
