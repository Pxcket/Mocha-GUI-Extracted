#include "includes.h"
#include "Util/natives.h"
#include "Util/Hooks.h"
#include <chrono>
#include <algorithm>  
#include <string>     
#include "Util/Font.h"
#include "Util/UI/watermark.h"
#include "Util/UI/menu.hpp"
#include "Util/UI/changelogs.h"
#include "Util/UI/CGui.h"
#include <dwmapi.h>
#include "Util/UI/circles.h"
#include "logger.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;




bool init = false;



void DrawCustomCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    ImVec2 mouse_pos = io.MousePos;
    ImU32 red_color = IM_COL32(255, 255, 255, 255);
    float size = 8.0f; 
    draw_list->AddLine(ImVec2(mouse_pos.x - size, mouse_pos.y),
        ImVec2(mouse_pos.x + size, mouse_pos.y),
        red_color, 2.0f); 
    draw_list->AddLine(ImVec2(mouse_pos.x, mouse_pos.y - size),
        ImVec2(mouse_pos.x, mouse_pos.y + size),
        red_color, 2.0f); 
}

void CreateConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    SetConsoleTitleA("Dev Console");
	system("cls");
    Log::log("Console Created");
    Log::log("Console Allocated");

}

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavEnableKeyboard;


    //ImGuiStyle& style = ImGui::GetStyle();
    //ImVec4* colors = style.Colors;
    //ImGui::GetStyle().Alpha = 1.0f;

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);

    //ImFontConfig font;
    //font.FontDataOwnedByAtlas = false;

    //io.Fonts->AddFontFromMemoryTTF((void*)rawData, sizeof(rawData), 20.5f, &font);

}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (GetAsyncKeyState(VK_DELETE) & 1)
        UI::show = !UI::show;
    if (UI::show)
    {
        ImGui::GetIO().WantCaptureMouse = 1;

    }
    else
    {
        ImGui::GetIO().WantCaptureMouse = 0;

    }

    if (UI::show)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return 1;
    }
    else
    {
        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
    }


    if (UI::show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            Hooks();
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (pBackBuffer != nullptr)
            {
                pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
                pBackBuffer->Release();
                oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

                pTextures = new CTextures();
                bool textures_result = pTextures->Initialize(pDevice);
                if (!textures_result)
                {
                    Log::error("Could not initialize Textures.");
                }

                if (textures_result)
                {
                    bool gui_result = false;

                    pGui = new CGui(pTextures);
                    gui_result = pGui->Initialize(window, pDevice, pContext);
                    if (!gui_result)
                    {
                        Log::error("Could not initialize Gui.");
                    }
                }


                init = true;
               Log::log("ImGui initialized.");
            }
            else
            {
                Log::error("ImGui pBackBuffer is NULL.");
            }
        }

        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    WaterMark();
    ImGui::PushFont(pGui->m_Fonts.BigFont);
    {
        pGui->notify.Render();
    }
    ImGui::PopFont();
    if (UI::show)
    {
        RenderParticles();
        DrawCustomCursor();
        pGui->PreRender();
        ChangelogCreditsWindow();
    }
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    CreateConsole();
    if (MH_Initialize() != MH_OK)
    {
        MessageBox(NULL, "MinHook failed", "Error!!!", MB_OK);
        return 0;
    }

    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        std::thread(MainThread, hMod).detach(); 
        break;                                  
    case DLL_PROCESS_DETACH:
        CleanupParticles();
        kiero::shutdown();
        MH_Uninitialize();
        break;
    }
    return TRUE;
}
