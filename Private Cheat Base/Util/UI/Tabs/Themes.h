#pragma once
#include "../CGui.h"
void CGui::ThemesTab(ImGuiStyle& style)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Themes");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Themes", ImVec2(0, 500), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        constexpr ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf
            | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

//        ImAdd::ToggleButtonClassic("Show Mouse Cursor", &UI::showCursor);
        ImAdd::ToggleButtonClassic("Menu Particles", &UI::particles::toggle);


        float fFrameWidth = static_cast<int>((ImGui::GetWindowWidth() - style.WindowPadding.x * 2 - style.ItemSpacing.x
            * 2) / 8);

        ImAdd::RadioFrameColor("DarkBlue", &iTheme, THEME_DARK_BLUE, ImAdd::HexToColorVec4(0x24292E, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("DarkPurple", &iTheme, THEME_DARK_PURPLE, ImAdd::HexToColorVec4(0x262532, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("Red", &iTheme, THEME_RED, ImAdd::HexToColorVec4(0x362323, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("Skeet", &iTheme, THEME_SKEET, ImAdd::HexToColorVec4(0x4AFF4A, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("Mocha", &iTheme, THEME_MOCHA, ImAdd::HexToColorVec4(0x1F1F1F, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("Dark", &iTheme, THEME_DARK, ImAdd::HexToColorVec4(0x272727, 1.0f),
            ImVec2(fFrameWidth, -0.1f));
        ImGui::SameLine();
        ImAdd::RadioFrameColor("WHITE", &iTheme, THEME_WHITE, ImAdd::HexToColorVec4(0xFFFFFF, 1.0f),
            ImVec2(fFrameWidth, -0.1f));

    }
    ImGui::EndChild();
}
