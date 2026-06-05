#include "Windows.Xbox.Input.Gamepad.h"
#include "WinDurangoWinRT.h"

HMODULE XInput = nullptr;
typedef DWORD (WINAPI* PFN_XInputGetState)(
    DWORD dwUserIndex,
    XINPUT_STATE* pState
);

typedef DWORD (WINAPI* PFN_XInputGetCapabilities)(
    DWORD dwUserIndex,
    DWORD dwFlags,
    XINPUT_CAPABILITIES* pCapabilities
);

typedef DWORD (WINAPI* PFN_XInputSetState)(
    DWORD dwUserIndex,
    XINPUT_VIBRATION* pVibration
);

PFN_XInputGetState XInput1_3GetState;
PFN_XInputGetCapabilities XInput1_3GetCapabilities;
PFN_XInputSetState XInput1_3SetState;

namespace winrt::Windows::Xbox::Input::implementation
{
    winrt::Windows::Xbox::Input::Gamepad GamepadAddedEventArgs::Gamepad()
    {
        return gamepad;
    }

    winrt::Windows::Xbox::Input::Gamepad GamepadRemovedEventArgs::Gamepad()
    {
        return gamepad;
    }

    winrt::Windows::Foundation::DateTime GamepadReading::Timestamp()
    {
        return time;
    }

    winrt::Windows::Xbox::Input::GamepadButtons GamepadReading::Buttons()
    {
        return reading.Buttons;
    }

    bool GamepadReading::IsDPadUpPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::DPadUp;
    }
    bool GamepadReading::IsDPadDownPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::DPadDown;
    }
    bool GamepadReading::IsDPadLeftPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::DPadLeft;
    }
    bool GamepadReading::IsDPadRightPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::DPadRight;
    }
    bool GamepadReading::IsMenuPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::Menu;
    }
    bool GamepadReading::IsViewPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::View;
    }
    bool GamepadReading::IsLeftThumbstickPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::LeftThumbstick;
    }
    bool GamepadReading::IsRightThumbstickPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::RightThumbstick;
    }
    bool GamepadReading::IsLeftShoulderPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::LeftShoulder;
    }
    bool GamepadReading::IsRightShoulderPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::RightShoulder;
    }
    bool GamepadReading::IsAPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::A;
    }
    bool GamepadReading::IsBPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::B;
    }
    bool GamepadReading::IsXPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::X;
    }
    bool GamepadReading::IsYPressed()
    {
        return (int)reading.Buttons & (int)GamepadButtons::Y;
    }
    float GamepadReading::LeftTrigger()
    {
        return reading.LeftTrigger;
    }
    float GamepadReading::RightTrigger()
    {
        return reading.RightTrigger;
    }
    float GamepadReading::LeftThumbstickX()
    {
        return reading.LeftThumbstickX;
    }
    float GamepadReading::LeftThumbstickY()
    {
        return reading.LeftThumbstickY;
    }
    float GamepadReading::RightThumbstickX()
    {
        return reading.RightThumbstickX;
    }
    float GamepadReading::RightThumbstickY()
    {
        return reading.RightThumbstickY;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IGamepad> Gamepad::Gamepads()
    {
        if (!XInput || !XInput1_3GetState || !XInput1_3GetCapabilities || !XInput1_3SetState)
        {
            XInput = LoadLibraryW(L"xinput1_3.dll");
            if (XInput)
            {
                XInput1_3GetState = (PFN_XInputGetState)GetProcAddress(XInput, "XInputGetState");
                XInput1_3GetCapabilities = (PFN_XInputGetCapabilities)GetProcAddress(XInput, "XInputGetCapabilities");
                XInput1_3SetState = (PFN_XInputSetState)GetProcAddress(XInput, "XInputSetState");
            }
        }

        if (a_gamepads == winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IGamepad>(nullptr) || a_gamepads.Size() == 0)
        {
            a_gamepads = winrt::single_threaded_vector<winrt::Windows::Xbox::Input::IGamepad>();

            p_wd->log.Log("WinDurango::WinRT::Windows::Xbox::Input", "Creating static a_gamepads");

            bool controllerFound = false;

            for (DWORD gamepad = 0; gamepad < XUSER_MAX_COUNT; gamepad++)
            {
                XINPUT_CAPABILITIES capabilities{};
                XINPUT_STATE state{};
                
                bool Result = XInput1_3GetCapabilities(gamepad, XINPUT_FLAG_GAMEPAD, &capabilities) == ERROR_SUCCESS || XInput1_3GetState(gamepad, &state) == ERROR_SUCCESS;
                if (Result) // should work now btw
                {
                    p_wd->log.Log("WinDurango::WinRT::Windows::Xbox::Input", "Creating gamepad");
                    winrt::Windows::Xbox::Input::IGamepad NewGamepad = winrt::make<Gamepad>(gamepad, true);
                    a_gamepads.Append(NewGamepad);
                    controllerFound = true;
                    continue;
                }
            }

            if (!controllerFound) 
            {
                p_wd->log.Log("WinDurango::WinRT::Windows::Xbox::Input", "No XInput Controller found");
                winrt::Windows::Xbox::Input::IGamepad NewGamepad = winrt::make<Gamepad>(XUSER_MAX_COUNT, false);
                a_gamepads.Append(NewGamepad);
            }
        }

        const HWND hwnd = GetFocus();

        ShowCursor(FALSE);

		RECT rc;

		GetClientRect(hwnd, &rc);

		POINT tl = { rc.left, rc.top };
		POINT br = { rc.right, rc.bottom };

		MapWindowPoints(hwnd, nullptr, &tl, 1);
		MapWindowPoints(hwnd, nullptr, &br, 1);

		const RECT screenRect = { tl.x, tl.y, br.x, br.y };

		ClipCursor(&screenRect);
		ShowCursor(FALSE);

        return a_gamepads.GetView();
    }

    winrt::event_token Gamepad::GamepadAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs> const& handler)
    {
        return {};
    }

    void Gamepad::GamepadAdded(winrt::event_token const& token) noexcept
    {
        throw hresult_not_implemented();
    }

    winrt::event_token Gamepad::GamepadRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs> const& handler)
    {
        return {};
    }

    void Gamepad::GamepadRemoved(winrt::event_token const& token) noexcept
    {
        throw hresult_not_implemented();
    }

    uint64_t Gamepad::Id()
    {
        return 1;
    }

    hstring Gamepad::Type()
    {
        return L"Windows.Xbox.Input.Gamepad";
    }

    winrt::Windows::Xbox::System::User Gamepad::User()
    {
        p_wd->log.Log("WinDurango::WinRT::Windows::Xbox::Input", "Getting User");
        return winrt::Windows::Xbox::System::implementation::User::Users().GetAt(Id());
    }

    winrt::Windows::Xbox::Input::INavigationReading Gamepad::GetNavigationReading()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Input", "Unimplemented: GetNavigationReading");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Input::RawNavigationReading Gamepad::GetRawNavigationReading()
    {
        RawNavigationReading dummyNavigationReading = RawNavigationReading();
        dummyNavigationReading.Timestamp = GetTickCount64();
        dummyNavigationReading.Buttons |= NavigationButtons::Up;
        return dummyNavigationReading;
    }

    void Gamepad::SetVibration(winrt::Windows::Xbox::Input::GamepadVibration const& value)
    {
        XINPUT_VIBRATION Vibration{};
        Vibration.wLeftMotorSpeed = value.LeftMotorLevel * 65535;
        Vibration.wRightMotorSpeed = value.RightMotorLevel * 65535;
        XInput1_3SetState(id, &Vibration);
    }

    winrt::Windows::Xbox::Input::GamepadReading Gamepad::GetCurrentReading()
    {
        return winrt::make<implementation::GamepadReading>(GetRawCurrentReading());
    }

    winrt::Windows::Xbox::Input::RawGamepadReading Gamepad::GetRawCurrentReading()
    {
        XINPUT_STATE xiState;
        ZeroMemory(&xiState, sizeof(XINPUT_STATE));
        RawGamepadReading reading = {};

        WORD gp_up;
        WORD gp_down;
        WORD gp_left;
        WORD gp_right;
        WORD gp_start;
        WORD gp_back;
        WORD gp_lt;
        WORD gp_rt;
        WORD gp_ls;
        WORD gp_rs;
        WORD gp_a;
        WORD gp_b;
        WORD gp_x;
        WORD gp_y;

        if (p_wd->config.jsonData().contains("controls") && p_wd->config["controls"].is_object()) 
        {
            if (p_wd->config["controls"].contains("Up") && p_wd->config["controls"]["Up"].is_number())
            {
                gp_up = p_wd->config["controls"]["Up"];
            }
            if (p_wd->config["controls"].contains("Down") && p_wd->config["controls"]["Down"].is_number())
            {
                gp_down = p_wd->config["controls"]["Down"];
            }
            if (p_wd->config["controls"].contains("Left") && p_wd->config["controls"]["Left"].is_number())
            {
                gp_left = p_wd->config["controls"]["Left"];
            }
            if (p_wd->config["controls"].contains("Right") && p_wd->config["controls"]["Right"].is_number())
            {
                gp_right = p_wd->config["controls"]["Right"];
            }
            if (p_wd->config["controls"].contains("Start") && p_wd->config["controls"]["Start"].is_number())
            {
                gp_start = p_wd->config["controls"]["Start"];
            }
            if (p_wd->config["controls"].contains("Back") && p_wd->config["controls"]["Back"].is_number())
            {
                gp_back = p_wd->config["controls"]["Back"];
            }
            if (p_wd->config["controls"].contains("LeftTrigger") && p_wd->config["controls"]["LeftTrigger"].is_number())
            {
                gp_lt = p_wd->config["controls"]["LeftTrigger"];
            }
            if (p_wd->config["controls"].contains("RightTrigger") && p_wd->config["controls"]["RightTrigger"].is_number())
            {
                gp_rt = p_wd->config["controls"]["RightTrigger"];
            }
            if (p_wd->config["controls"].contains("LeftShoulder") && p_wd->config["controls"]["LeftShoulder"].is_number())
            {
                gp_ls = p_wd->config["controls"]["LeftShoulder"];
            }
            if (p_wd->config["controls"].contains("RightShoulder") && p_wd->config["controls"]["RightShoulder"].is_number())
            {
                gp_rs = p_wd->config["controls"]["RightShoulder"];
            }
            if (p_wd->config["controls"].contains("A") && p_wd->config["controls"]["A"].is_number())
            {
                gp_a = p_wd->config["controls"]["A"];
            }
            if (p_wd->config["controls"].contains("B") && p_wd->config["controls"]["B"].is_number())
            {
                gp_b = p_wd->config["controls"]["B"];
            }
            if (p_wd->config["controls"].contains("X") && p_wd->config["controls"]["X"].is_number())
            {
                gp_x = p_wd->config["controls"]["X"];
            }
            if (p_wd->config["controls"].contains("Y") && p_wd->config["controls"]["Y"].is_number())
            {
                gp_y = p_wd->config["controls"]["Y"];
            }
        }

        static std::pair<WORD, GamepadButtons> const buttons[] = {
            {gp_up, GamepadButtons::DPadUp},
            {gp_down, GamepadButtons::DPadDown},
            {gp_left, GamepadButtons::DPadLeft},
            {gp_right, GamepadButtons::DPadRight},
            {gp_start, GamepadButtons::Menu},
            {gp_back, GamepadButtons::View},
            {gp_lt, GamepadButtons::LeftThumbstick},
            {gp_rt, GamepadButtons::RightThumbstick},
            {gp_ls, GamepadButtons::LeftShoulder},
            {gp_rs, GamepadButtons::RightShoulder},
            {gp_a, GamepadButtons::A},
            {gp_b, GamepadButtons::B},
            {gp_x, GamepadButtons::X},
            {gp_y, GamepadButtons::Y},
        };

        if (XInput1_3GetState(id, &xiState) == ERROR_SUCCESS)
        {
            for (int i = 0; i < ARRAYSIZE(buttons); i++)
            {
                if (xiState.Gamepad.wButtons & buttons[i].first)
                {
                    reading.Buttons |= buttons[i].second;
                }
            }

            reading.LeftTrigger = xiState.Gamepad.bLeftTrigger / 255.f;
            reading.RightTrigger = xiState.Gamepad.bRightTrigger / 255.f;
            reading.LeftThumbstickX = xiState.Gamepad.sThumbLX / 32768.f;
            reading.LeftThumbstickY = xiState.Gamepad.sThumbLY / 32768.f;
            reading.RightThumbstickX = xiState.Gamepad.sThumbRX / 32768.f;
            reading.RightThumbstickY = xiState.Gamepad.sThumbRY / 32768.f;
        }

        SHORT kb_wm = 0;
        SHORT kb_am = 0;
        SHORT kb_sm = 0;
        SHORT kb_dm = 0;
        SHORT kb_a = 0;
        SHORT kb_b = 0;
        SHORT kb_x = 0;
        SHORT kb_y = 0;
        SHORT kb_up = 0;
        SHORT kb_down = 0;
        SHORT kb_left = 0;
        SHORT kb_right = 0;
        SHORT kb_menu = 0;
        SHORT kb_view = 0;
        SHORT kb_lt = 0;
        SHORT kb_rt = 0;
        SHORT kb_ls = 0;
        SHORT kb_rs = 0;
        SHORT kb_rtr = 0;
        SHORT kb_ltr = 0;

        if (p_wd->config.jsonData().contains("keyboard") && p_wd->config["keyboard"].is_object()) 
        {
            if (p_wd->config["keyboard"].contains("WM") && p_wd->config["keyboard"]["WM"].is_number())
            {
                kb_wm = p_wd->config["keyboard"]["WM"];
            }
            if (p_wd->config["keyboard"].contains("AM") && p_wd->config["keyboard"]["AM"].is_number())
            {
                kb_am = p_wd->config["keyboard"]["AM"];
            }
            if (p_wd->config["keyboard"].contains("SM") && p_wd->config["keyboard"]["SM"].is_number())
            {
                kb_sm = p_wd->config["keyboard"]["SM"];
            }
            if (p_wd->config["keyboard"].contains("DM") && p_wd->config["keyboard"]["DM"].is_number())
            {
                kb_dm = p_wd->config["keyboard"]["DM"];
            }
            if (p_wd->config["keyboard"].contains("A") && p_wd->config["keyboard"]["A"].is_number())
            {
                kb_a = p_wd->config["keyboard"]["A"];
            }
            if (p_wd->config["keyboard"].contains("B") && p_wd->config["keyboard"]["B"].is_number())
            {
                kb_b = p_wd->config["keyboard"]["B"];
            }
            if (p_wd->config["keyboard"].contains("X") && p_wd->config["keyboard"]["X"].is_number())
            {
                kb_x = p_wd->config["keyboard"]["X"];
            }
            if (p_wd->config["keyboard"].contains("Y") && p_wd->config["keyboard"]["Y"].is_number())
            {
                kb_y = p_wd->config["keyboard"]["Y"];
            }
            if (p_wd->config["keyboard"].contains("Up") && p_wd->config["keyboard"]["Up"].is_number())
            {
                kb_up = p_wd->config["keyboard"]["Up"];
            }
            if (p_wd->config["keyboard"].contains("Down") && p_wd->config["keyboard"]["Down"].is_number())
            {
                kb_down = p_wd->config["keyboard"]["Down"];
            }
            if (p_wd->config["keyboard"].contains("Left") && p_wd->config["keyboard"]["Left"].is_number())
            {
                kb_left = p_wd->config["keyboard"]["Left"];
            }
            if (p_wd->config["keyboard"].contains("Right") && p_wd->config["keyboard"]["Right"].is_number())
            {
                kb_right = p_wd->config["keyboard"]["Right"];
            }
            if (p_wd->config["keyboard"].contains("Menu") && p_wd->config["keyboard"]["Menu"].is_number())
            {
                kb_menu = p_wd->config["keyboard"]["Menu"];
            }
            if (p_wd->config["keyboard"].contains("View") && p_wd->config["keyboard"]["View"].is_number())
            {
                kb_view = p_wd->config["keyboard"]["View"];
            }
            if (p_wd->config["keyboard"].contains("LeftThumb") && p_wd->config["keyboard"]["LeftThumb"].is_number())
            {
                kb_lt = p_wd->config["keyboard"]["LeftThumb"];
            }
            if (p_wd->config["keyboard"].contains("RightThumb") && p_wd->config["keyboard"]["RightThumb"].is_number())
            {
                kb_rt = p_wd->config["keyboard"]["RightThumb"];
            }
            if (p_wd->config["keyboard"].contains("LeftShoulder") && p_wd->config["keyboard"]["LeftShoulder"].is_number())
            {
                kb_ls = p_wd->config["keyboard"]["LeftShoulder"];
            }
            if (p_wd->config["keyboard"].contains("RightShoulder") && p_wd->config["keyboard"]["RightShoulder"].is_number())
            {
                kb_rs = p_wd->config["keyboard"]["RightShoulder"];
            }
            if (p_wd->config["keyboard"].contains("LeftTrigger") && p_wd->config["keyboard"]["LeftTrigger"].is_number())
            {
                kb_ltr = p_wd->config["keyboard"]["LeftTrigger"];
            }
            if (p_wd->config["keyboard"].contains("RightTrigger") && p_wd->config["keyboard"]["RightTrigger"].is_number())
            {
                kb_rtr = p_wd->config["keyboard"]["RightTrigger"];
            }
        }

        float lx = 0.0f;
        float ly = 0.0f;

        if (GetAsyncKeyState(kb_wm) & 0x8000) {
            ly = 1.0f;
        }

        if (GetAsyncKeyState(kb_am) & 0x8000) {
            lx = -1.0f;
        }

        if (GetAsyncKeyState(kb_sm) & 0x8000) {
            ly = -1.0;
        }

        if (GetAsyncKeyState(kb_dm) & 0x8000) {
            lx = 1.0f;
        }

        lx = std::clamp(lx, -1.0f, 1.0f);
        ly = std::clamp(ly, -1.0f, 1.0f);

        if (lx != 0.0f || ly != 0.0f) {
            reading.LeftThumbstickX = lx;
            reading.LeftThumbstickY = ly;
        }

        if (GetAsyncKeyState(kb_a) & 0x8000) {
            reading.Buttons |= GamepadButtons::A;
        }
        if (GetAsyncKeyState(kb_b) & 0x8000) {
            reading.Buttons |= GamepadButtons::B;
        }
        if (GetAsyncKeyState(kb_x) & 0x8000) {
            reading.Buttons |= GamepadButtons::X;
        }
        if (GetAsyncKeyState(kb_y) & 0x8000) {
            reading.Buttons |= GamepadButtons::Y;
        }
        if (GetAsyncKeyState(kb_up) & 0x8000) {
            reading.Buttons |= GamepadButtons::DPadUp;
        }
        if (GetAsyncKeyState(kb_down) & 0x8000) {
            reading.Buttons |= GamepadButtons::DPadDown;
        }
        if (GetAsyncKeyState(kb_left) & 0x8000) {
            reading.Buttons |= GamepadButtons::DPadLeft;
        }
        if (GetAsyncKeyState(kb_right) & 0x8000) {
            reading.Buttons |= GamepadButtons::DPadRight;
        }
        if (GetAsyncKeyState(kb_menu) & 0x8000) {
            reading.Buttons |= GamepadButtons::Menu;
        }
        if (GetAsyncKeyState(kb_view) & 0x8000) {
            reading.Buttons |= GamepadButtons::View;
        }
        if (GetAsyncKeyState(kb_lt) & 0x8000) {
            reading.Buttons |= GamepadButtons::LeftThumbstick;
        }
        if (GetAsyncKeyState(kb_rt) & 0x8000) {
            reading.Buttons |= GamepadButtons::RightThumbstick;
        }
        if (GetAsyncKeyState(kb_ls) & 0x8000) {
            reading.Buttons |= GamepadButtons::LeftShoulder;
        }
        if (GetAsyncKeyState(kb_rs) & 0x8000) {
            reading.Buttons |= GamepadButtons::RightShoulder;
        }

        if (GetAsyncKeyState(kb_ltr) & 0x8000) {
            reading.RightTrigger = 1.0f;
        }
        if (GetAsyncKeyState(kb_rtr) & 0x8000) {
            reading.LeftTrigger = 1.0f;
        }

        POINT pos;
        GetCursorPos(&pos);

        if (firstFrame) {
            prev = pos;
            firstFrame = false;
        }

        const int dx = pos.x - prev.x;
        const int dy = pos.y - prev.y;

        deltaSumX += dx;
        deltaSumY += dy;
        prev = pos;

        const int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
        const int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;

        SetCursorPos(centerX, centerY);

        prev.x = centerX;
        prev.y = centerY;

        auto sign = [](float v) { return (v > 0) - (v < 0); };
        
        float x = -std::exp((-1.0f / 5.0f) * std::abs(deltaSumX)) + 1.0f;
        float y = -std::exp((-1.0f / 5.0f) * std::abs(deltaSumY)) + 1.0f;

        x *= sign(deltaSumX);
        y *= -sign(deltaSumY);

        if (x != 0 || y != 0) {
            reading.RightThumbstickX = std::clamp(x, -1.0f, 1.0f);
            reading.RightThumbstickY = std::clamp(y, -1.0f, 1.0f);
        }

        deltaSumX = 0.0f;
        deltaSumY = 0.0f;

        return reading;
    }

    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs>> Gamepad::e_GamepadAdded{};
    winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs>> Gamepad::e_GamepadRemoved{};
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IGamepad> Gamepad::a_gamepads;
}
