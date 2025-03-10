#pragma once
#include "Windows.Xbox.Media.GameTransportControls.g.h"

namespace winrt::Windows::Xbox::Media::implementation
{
    struct GameTransportControls : GameTransportControlsT<GameTransportControls>
    {
        GameTransportControls() = default;

        hstring Title();
        hstring Subtitle();
        GamePlaybackStatus PlaybackStatus();
        void PlaybackStatus(GamePlaybackStatus const& value);
        SoundLevel SoundLevel();
        bool IsEnabled();
        void IsEnabled(bool value);
        bool IsPlayEnabled();
        void IsPlayEnabled(bool value);
        bool IsPauseEnabled();
        void IsPauseEnabled(bool value);
        bool IsMenuEnabled();
        void IsMenuEnabled(bool value);
        bool IsViewEnabled();
        void IsViewEnabled(bool value);
        bool IsBackEnabled();
        void IsBackEnabled(bool value);
        event_token ButtonPressed(Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsButtonPressedEventArgs> const& handler);
        void ButtonPressed(event_token const& token) noexcept;
        event_token PropertyChanged(Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsPropertyChangedEventArgs> const& handler);
        void PropertyChanged(event_token const& token) noexcept;

    private:
        GamePlaybackStatus m_gamePlaybackStatus = GamePlaybackStatus::Closed;

    	bool m_enabled = false;
        bool m_playEnabled = false;
        bool m_pauseEnabled = false;
        bool m_menuEnabled = false;
        bool m_viewEnabled = false;
        bool m_backEnabled = false;

        event<Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsButtonPressedEventArgs>> m_gameTransportControlsButtonPressedEventArgs;
        event<Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsPropertyChangedEventArgs>> m_gameTransportControlsPropertyChangedEventArgs;
    };
}
namespace winrt::Windows::Xbox::Media::factory_implementation
{
    struct GameTransportControls : GameTransportControlsT<GameTransportControls, implementation::GameTransportControls>
    {
    };
}
