#include "pch.h"
#include "Windows.Xbox.Media.GameTransportControls.h"
#include "Windows.Xbox.Media.GameTransportControls.g.cpp"

namespace winrt::Windows::Xbox::Media::implementation
{
    hstring GameTransportControls::Title()
    {
        LOG_FUNCTION_NAME();

        return L"null";
    }

    hstring GameTransportControls::Subtitle()
    {
        LOG_FUNCTION_NAME();

        return L"null";
    }

    GamePlaybackStatus GameTransportControls::PlaybackStatus()
    {
        LOG_FUNCTION_NAME();

        return m_gamePlaybackStatus;
    }

    void GameTransportControls::PlaybackStatus(GamePlaybackStatus const& value)
    {
        LOG_FUNCTION_NAME();

        m_gamePlaybackStatus = value;
    }

    SoundLevel GameTransportControls::SoundLevel()
    {
        LOG_FUNCTION_NAME();

        return SoundLevel::Muted;
    }

    bool GameTransportControls::IsEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_enabled;
    }

    void GameTransportControls::IsEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_enabled = value;
    }

    bool GameTransportControls::IsPlayEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_playEnabled;
    }

    void GameTransportControls::IsPlayEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_playEnabled = value;
    }

    bool GameTransportControls::IsPauseEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_pauseEnabled;
    }

    void GameTransportControls::IsPauseEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_pauseEnabled = value;
    }

    bool GameTransportControls::IsMenuEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_menuEnabled;
    }

    void GameTransportControls::IsMenuEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_menuEnabled = value;
    }

    bool GameTransportControls::IsViewEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_viewEnabled;
    }

    void GameTransportControls::IsViewEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_viewEnabled = value;
    }

    bool GameTransportControls::IsBackEnabled()
    {
        LOG_FUNCTION_NAME();

        return m_backEnabled;
    }

    void GameTransportControls::IsBackEnabled(bool value)
    {
        LOG_FUNCTION_NAME();

        m_backEnabled = value;
    }

    event_token GameTransportControls::ButtonPressed(Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsButtonPressedEventArgs> const& handler)
    {
        LOG_FUNCTION_NAME();

        return m_gameTransportControlsButtonPressedEventArgs.add(handler);
    }

    void GameTransportControls::ButtonPressed(event_token const& token) noexcept
    {
        LOG_FUNCTION_NAME();

        m_gameTransportControlsButtonPressedEventArgs.remove(token);
    }

    event_token GameTransportControls::PropertyChanged(Foundation::TypedEventHandler<Media::GameTransportControls, GameTransportControlsPropertyChangedEventArgs> const& handler)
    {
        LOG_FUNCTION_NAME();

        return m_gameTransportControlsPropertyChangedEventArgs.add(handler);
    }

    void GameTransportControls::PropertyChanged(winrt::event_token const& token) noexcept
    {
        LOG_FUNCTION_NAME();

        m_gameTransportControlsPropertyChangedEventArgs.remove(token);
    }
}
