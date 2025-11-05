#pragma once
#include "../../imgui/imgui.h"
#include <string>
#include "../natives.h"
#include "../../includes.h"
#include <functional>  
#include <cstdlib>    

//#ifndef PUB
//const char* buildver = "Public Build";    //- ich fixx das later cba 10/6/2025
//#endif


#ifndef DEV
const char* buildver = "dev-0JM";
#endif

const std::string watermark = "BS | Ez ImGui Steal Get Raped Broke Niggas Lost 3k In An Instance Would Suck To Be Yall  | " + std::string(buildver);
ImVec2 watermarkSize{ 0, 0 };

ImVec2 dvdPos = ImVec2(100, 100);
ImVec2 dvdVelocity = ImVec2(1.5f, 1.5f);
ImVec4 dvdColor = ImVec4(1, 1, 1, 1);

bool firstexec = false;
std::size_t watermarkHash = 0;


std::size_t CalculateDevHash(const std::string& input) {
    return std::hash<std::string>{}(input);
}

void WaterMark() {
    // Save current style
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiStyle backup_style = style;
    ImVec4* colors = style.Colors;
    ImVec4 backup_colors[ImGuiCol_COUNT];
    memcpy(backup_colors, colors, sizeof(backup_colors));

    // Apply your custom style
    style.WindowPadding = ImVec2(8, 8);
    style.FramePadding = ImVec2(6, 4);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.WindowRounding = 6.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.30f, 0.60f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.20f, 0.35f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.28f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.20f, 0.90f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.26f, 0.41f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.31f, 0.46f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.35f, 0.85f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.45f, 0.55f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.35f, 0.85f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.55f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.28f, 0.85f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.30f, 0.35f, 0.75f);
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.45f, 0.50f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.16f, 0.95f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.19f, 0.26f, 0.80f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.34f, 0.30f, 0.42f, 1.00f);


    if (!firstexec)
    {
        watermarkHash = CalculateDevHash(watermark);
        firstexec = true;
    }
    else
    {
        if (watermarkHash != CalculateDevHash(watermark))
            exit(-1);
    }

    if (watermarkSize.x == 0.0f && watermarkSize.y == 0.0f) {
        watermarkSize = ImGui::CalcTextSize(watermark.c_str());
    }

    ImGui::SetNextWindowSize(watermarkSize);
    ImGui::SetNextWindowBgAlpha(0.75f);
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin("watermark", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoBringToFrontOnFocus);
    /// purple
    ImVec4 lightPurple = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);
    ImVec4 darkPurple = ImVec4(0.407843137f, 0.254901961f, 0.62745098f, 1.0f);

    /// red
    //ImVec4 lightPurple = ImVec4(0.953f, 0.337f, 0.337f, 1.0f);
    //ImVec4 darkPurple = ImVec4(0.498f, 0.035f, 0.035f, 1.0f);

    ///blue
    //ImVec4 lightPurple = ImVec4(0.337f, 0.627f, 0.953f, 1.0f);
    //ImVec4 darkPurple = ImVec4(0.035f, 0.149f, 0.498f, 1.0f);

    //ImVec4 blue = ImVec4(0.2118f, 0.8314f, 1.0f, 1.0f);
    //ImVec4 pink = ImVec4(1.0f, 0.2118f, 0.8314f, 1.0f);

    GradientText(watermark.c_str(), 0.7f, lightPurple, darkPurple);
    ImGui::End();

    memcpy(colors, backup_colors, sizeof(backup_colors));
    style = backup_style;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("dvd watermark window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar);

    if (UI::show) {

        ImGuiIO& io = ImGui::GetIO();
        ImVec2 screenSize = io.DisplaySize;

        ImVec2 textSize = ImGui::CalcTextSize("Base");

        dvdPos.x += dvdVelocity.x;
        dvdPos.y += dvdVelocity.y;

        if (dvdPos.x <= 0.0f || dvdPos.x + textSize.x >= screenSize.x)
        {
            dvdVelocity.x *= -1.0f;
            dvdColor = ImVec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f); // Change color on bounce
        }

        if (dvdPos.y <= 0.0f || dvdPos.y + textSize.y >= screenSize.y)
        {
            dvdVelocity.y *= -1.0f;
            dvdColor = ImVec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f); // Change color on bounce
        }

        ImGui::SetCursorPos(dvdPos);
        ImGui::TextColored(dvdColor, "Ez Lost 3k Dumbass Niggas");

    }
    ImGui::End();
}