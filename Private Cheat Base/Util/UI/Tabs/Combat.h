#pragma once
#include "../CGui.h"

void CGui::CombatTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Combat Modules");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Combat Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 60), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        ImGui::SeparatorText("Combat");
        {
            if (ImGui::Button("Notification Test"))
            {
                notify.PushNotification<ImVec4(1, 0, 0, 1), 3.0f>(m_pTextures->tExplosion,
                    "Hello, I'm a indian Scammer! Thanks for the 3k Losers");
            }
        }


    }
    ImGui::EndChild();

}