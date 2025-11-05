
// Old Retard Code Dont use 


//#pragma once
//#include "../natives.h"
//#include "../../imgui/imgui.h"
//#include "../../imgui/addons/imgui_addons.h"
//
//ImVec4 lightPurple = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);
//ImVec4 darkPurple = ImVec4(0.4078f, 0.2549f, 0.6274f, 1.0f);
//
//
//void Help(const char* text) {
//    if (ImGui::IsItemHovered()) {
//        ImGui::BeginTooltip();
//        ImGui::TextUnformatted(text);
//        ImGui::EndTooltip();
//	}
//}
//void RenderTabButton(const char* label, int tabIndex, float width = 100.0f, float height = 40.0f) {
//    if (UI::tab == tabIndex)
//        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.45f, 0.45f, 0.55f, 1.00f));
//    else
//        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); 
//
//    if (ImGui::Button(label, ImVec2(width, height)))
//        UI::tab = tabIndex;
//
//    ImGui::PopStyleColor();
//}
//
//void Watermark()
//{
//
//}
//
//void Menu()
//{
//
//	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
//    ImGui::SetNextWindowSize(ImVec2(450, 650));
//    ImGui::Begin("Mxde FT13 Internal", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
//
//    ImGui::BeginChild("Sidebar", ImVec2(120, 0), true);
//    {
//        RenderTabButton("Main", 0);
//        RenderTabButton("Visuals", 2);
//        RenderTabButton("Misc", 3);
//        RenderTabButton("Settings", 4);
//    }
//    ImGui::EndChild();
//
//    ImGui::SameLine();
//
//    ImGui::BeginChild("Content", ImVec2(0, 0), true);
//    {
//        switch (UI::tab) {
//        case 0:
//            // First Tab: Main
//            // First Tab: Main
//            // First Tab: Main
//            // First Tab: Main
//
//
//
//            GradientText("Main", 0.7f, lightPurple, darkPurple);
//			ImGui::Separator();
//
//            ImAdd::ToggleButton("FOV Changer", &UI::Camera::FovChanger);
//            if (UI::Camera::FovChanger)
//            {
//                ImGui::SliderFloat("FOV: ", &UI::Camera::NewFOV, 1.0f, 179.0f);
//            }
//
//
//            // First Tab: Main
//            // First Tab: Main
//            // First Tab: Main
//            // First Tab: Main
//            break;
//        case 2:
//			// second Tab: Visuals
//			// second Tab: Visuals
//			// second Tab: Visuals
//			// second Tab: Visuals
//
//
//
//            GradientText("Visual", 0.7f, lightPurple, darkPurple);
//            ImGui::Separator();
//
//
//
//            // second Tab: Visuals
//            // second Tab: Visuals
//            // second Tab: Visuals
//            // second Tab: Visuals
//            break;
//        case 3:
//            GradientText("Misc", 0.7f, lightPurple, darkPurple);
//            ImGui::Separator();
//
//
//
//            // Third Tab: Misc
//            // Third Tab: Misc
//            // Third Tab: Misc
//            // Third Tab: Misc
//            break;
//        case 4:
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//
//
//
//            GradientText("Settings", 0.7f, lightPurple, darkPurple);
//            ImGui::Separator();
//            if (ImGui::Button("Free VBucks"))
//            {
//                kiero::shutdown();
//            }
//            Help("Uninject From The Game!");
//
//
//			if (ImGui::Button("Free Robux")) 
//            {
//                exit(0);
//            }
//            Help("Easily Crash Youre game!");
//
//
//
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//            // 4rd Tab: Settings
//            break;
//        }
//    }
//    ImGui::EndChild();
//
//    ImGui::End();
//}