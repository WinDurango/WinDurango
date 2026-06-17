#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <Xinput.h>
#include "Windows.Xbox.Input.Gamepad.g.h"
#include "Windows.Xbox.Input.GamepadAddedEventArgs.g.h"
#include "Windows.Xbox.Input.GamepadRemovedEventArgs.g.h"
#include "Windows.Xbox.Input.GamepadReading.g.h"
#include "Windows.Xbox.System.User.h"

namespace winrt::Windows::Xbox::Input::implementation
{
    struct GamepadAddedEventArgs : GamepadAddedEventArgsT<GamepadAddedEventArgs>
    {
        GamepadAddedEventArgs() = default;
        GamepadAddedEventArgs(winrt::Windows::Xbox::Input::Gamepad gamepad) : gamepad(gamepad) {} 

        winrt::Windows::Xbox::Input::Gamepad Gamepad();
    private:
        winrt::Windows::Xbox::Input::Gamepad gamepad;
    };

    struct GamepadRemovedEventArgs : GamepadRemovedEventArgsT<GamepadRemovedEventArgs>
    {
        GamepadRemovedEventArgs() = default;
        GamepadRemovedEventArgs(winrt::Windows::Xbox::Input::Gamepad gamepad) : gamepad(gamepad) {} 

        winrt::Windows::Xbox::Input::Gamepad Gamepad();
    private:
        winrt::Windows::Xbox::Input::Gamepad gamepad;
    };
    
    struct GamepadReading : GamepadReadingT<GamepadReading>
    {
        GamepadReading() = default;
        GamepadReading(winrt::Windows::Xbox::Input::RawGamepadReading reading)
            : reading(reading) {}

        winrt::Windows::Foundation::DateTime Timestamp();
        winrt::Windows::Xbox::Input::GamepadButtons Buttons();
        bool IsDPadUpPressed();
        bool IsDPadDownPressed();
        bool IsDPadLeftPressed();
        bool IsDPadRightPressed();
        bool IsMenuPressed();
        bool IsViewPressed();
        bool IsLeftThumbstickPressed();
        bool IsRightThumbstickPressed();
        bool IsLeftShoulderPressed();
        bool IsRightShoulderPressed();
        bool IsAPressed();
        bool IsBPressed();
        bool IsXPressed();
        bool IsYPressed();
        float LeftTrigger();
        float RightTrigger();
        float LeftThumbstickX();
        float LeftThumbstickY();
        float RightThumbstickX();
        float RightThumbstickY();
    private:
        winrt::Windows::Foundation::DateTime time;
        winrt::Windows::Xbox::Input::RawGamepadReading reading;
    };

    struct Gamepad : GamepadT<Gamepad>
    {
        Gamepad() = default;
        Gamepad(uint64_t id, bool gamepad) : id(id) {}

        static winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IGamepad> Gamepads();
        static winrt::event_token GamepadAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs> const& handler);
        static void GamepadAdded(winrt::event_token const& token) noexcept;
        static winrt::event_token GamepadRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs> const& handler);
        static void GamepadRemoved(winrt::event_token const& token) noexcept;
        uint64_t Id();
        hstring Type();
        winrt::Windows::Xbox::System::User User();
        winrt::Windows::Xbox::Input::INavigationReading GetNavigationReading();
        winrt::Windows::Xbox::Input::RawNavigationReading GetRawNavigationReading();
        void SetVibration(winrt::Windows::Xbox::Input::GamepadVibration const& value);
        winrt::Windows::Xbox::Input::GamepadReading GetCurrentReading();
        winrt::Windows::Xbox::Input::RawGamepadReading GetRawCurrentReading();
    private:
        POINT prev{ 0, 0 };
        float deltaSumX = 0.0f;
        float deltaSumY = 0.0f;
        bool firstFrame = true;
        
        uint64_t id = 0;
        bool gamepad = false;
        static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs>> e_GamepadAdded;
        static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs>> e_GamepadRemoved;
        static winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IGamepad> a_gamepads;
        bool m_IsMouseLockEnabled = false;
    };
}
namespace winrt::Windows::Xbox::Input::factory_implementation
{
    struct Gamepad : GamepadT<Gamepad, implementation::Gamepad>
    {
    };
}
