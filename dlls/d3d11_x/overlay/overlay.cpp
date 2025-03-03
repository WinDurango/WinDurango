#include "overlay.h"

#include "../../../thirdparty/imgui/imgui.h"
#include "../../../thirdparty/imgui/backends/imgui_impl_dx11.h"
#include "../../../thirdparty/imgui_impl_uwp.h"
#include <winrt/windows.graphics.display.h>

wd::Overlay::Overlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, IDXGISwapChain1* pSwapchain):
	m_pRenderTargetView(nullptr)
{
	m_pDevice = pDevice;
	m_pContext = pContext;
	m_pSwapchain = pSwapchain;
}

wd::Overlay::~Overlay()
{
	Shutdown( );
	m_pDevice = nullptr;
	m_pContext = nullptr;
	m_pSwapchain = nullptr;
}

void wd::Overlay::Initialize()
{
	g_KeyboardFinished = CreateEventA(NULL, FALSE, FALSE, "KeyboardFinished");

	ID3D11Texture2D* pBackBuffer;

	m_pSwapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);

	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );
	ImGuiIO& io = ImGui::GetIO( ); (void) io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);

	ImGui::StyleColorsDark( );

	ImGui_ImplUwp_InitForCurrentView( );
	ImGui_ImplDX11_Init(m_pDevice, m_pContext);
}

void wd::Overlay::Shutdown()
{
	ImGui_ImplDX11_Shutdown( );
	ImGui_ImplUwp_Shutdown( );
	ImGui::DestroyContext( );
}

void wd::Overlay::EnableKeyboard()
{
	m_bKeyboard = true;
}

void wd::Overlay::Present( )
{
    ImGui_ImplDX11_NewFrame( );
    ImGui_ImplUwp_NewFrame( );
    ImGui::NewFrame( );

    if (m_bKeyboard)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 300));
        ImGui::Begin("WinDurango Keyboard Input", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

        static bool isUppercase = false;
        static bool isSymbols = false;

        const char* keys[] = {
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
            "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]",
            "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'",
            "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"
        };

        const char* symbols[] = {
            "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
            "~", "`", "|", "\\", "{", "}", "[", "]", ":", ";", "\"", "'",
            "<", ">", "?", "/", ",", ".", "=", "-"
        };

        ImGui::InputText("Buffer", g_KeyboardText, IM_ARRAYSIZE(g_KeyboardText));

        if (ImGui::Button(isUppercase ? "Lowercase" : "Uppercase"))
        {
            isUppercase = !isUppercase;
        }
        ImGui::SameLine();
        if (ImGui::Button(isSymbols ? "Letters" : "Symbols"))
        {
            isSymbols = !isSymbols;
        }
        ImGui::NewLine();

        const char** currentKeys = isSymbols ? symbols : keys;
        ImVec2 buttonSize = ImVec2(30, 30);

        for (int i = 0; i < 12; ++i)
        {
            if (ImGui::Button(currentKeys[i], buttonSize))
            {
                size_t len = strlen(g_KeyboardText);
                if (len < 255)
                {
                    g_KeyboardText[len] = isUppercase ? currentKeys[i][0] : tolower(currentKeys[i][0]);
                    g_KeyboardText[len + 1] = '\0';
                }
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();

        for (int i = 12; i < 24; ++i)
        {
            if (ImGui::Button(currentKeys[i], buttonSize))
            {
                size_t len = strlen(g_KeyboardText);
                if (len < 255)
                {
                    g_KeyboardText[len] = isUppercase ? currentKeys[i][0] : tolower(currentKeys[i][0]);
                    g_KeyboardText[len + 1] = '\0';
                }
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();

        if (!isSymbols)
        {
            for (int i = 24; i < 35; ++i)
            {
                if (ImGui::Button(currentKeys[ i ], buttonSize))
                {
                    size_t len = strlen(g_KeyboardText);
                    if (len < 255)
                    {
                        g_KeyboardText[ len ] = isUppercase ? currentKeys[ i ][ 0 ] : tolower(currentKeys[ i ][ 0 ]);
                        g_KeyboardText[ len + 1 ] = '\0';
                    }
                }
                ImGui::SameLine( );
            }
        }
        else
        {
            for (int i = 24; i < 32; ++i)
            {
                if (ImGui::Button(currentKeys[ i ], buttonSize))
                {
                    size_t len = strlen(g_KeyboardText);
                    if (len < 255)
                    {
                        g_KeyboardText[ len ] = isUppercase ? currentKeys[ i ][ 0 ] : tolower(currentKeys[ i ][ 0 ]);
                        g_KeyboardText[ len + 1 ] = '\0';
                    }
                }
                ImGui::SameLine( );
            }
        }

        ImGui::NewLine();

        if (!isSymbols)
        {
            for (int i = 35; i < 44; ++i)
            {
                if (ImGui::Button(currentKeys[ i ], buttonSize))
                {
                    size_t len = strlen(g_KeyboardText);
                    if (len < 255)
                    {
                        g_KeyboardText[ len ] = isUppercase ? currentKeys[ i ][ 0 ] : tolower(currentKeys[ i ][ 0 ]);
                        g_KeyboardText[ len + 1 ] = '\0';
                    }
                }
                ImGui::SameLine( );
            }
        }

        ImGui::NewLine();

        if (ImGui::Button("OK", buttonSize) || ImGui::IsKeyPressed(ImGuiKey_GamepadStart))
        {
            m_bKeyboard = false;
            SetEvent(g_KeyboardFinished);
        }

        if (ImGui::IsKeyPressed(ImGuiKey_GamepadBack))
        {
            size_t len = strlen(g_KeyboardText);
            if (len > 0)
            {
                g_KeyboardText[len - 1] = '\0';
            }
        }

        ImGui::End();
    }

    ImGui::Render();

    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
