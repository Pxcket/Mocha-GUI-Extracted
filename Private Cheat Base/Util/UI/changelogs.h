#pragma once
#include "../natives.h"
#include "../../imgui/imgui.h"
void ChangelogCreditsWindow() {

    if (UI::show) {

        // Set the window size and position
        ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);

        // Set the window to be rounded and transparent
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.75f)); // Transparent background

        // Begin the window with no title bar, no move, and no resize
        ImGui::Begin("Changelog / Credits", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

        // Add a button to switch between Changelog and Credits
        static bool showChangelog = true;
        if (ImGui::Button(showChangelog ? "Show Credits" : "Show Changelog", ImVec2(ImGui::GetWindowWidth() - 20, 30))) {
            showChangelog = !showChangelog;
        }

        ImGui::Separator();

        // Display the content based on the current state
        if (showChangelog) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Changelog");
            ImGui::Separator();
            ImGui::TextWrapped("v4.2.0 - Update Nigga");
            ImGui::TextWrapped(" + Changelog 1");
            ImGui::TextWrapped(" + Changelog 2");
            ImGui::TextWrapped(" + Changelog 3");
            ImGui::TextWrapped(" + Changelog 4");
            ImGui::TextWrapped(" + Changelog 5");
            ImGui::TextWrapped(" + Changelog 6");
            ImGui::TextWrapped(" + Changelog 7");
            ImGui::TextWrapped(" + Changelog 8");
            ImGui::TextWrapped(" + Changelog 9");
            ImGui::TextWrapped(" + Changelog 10");
            ImGui::TextWrapped(" + Changelog 11");
            ImGui::TextWrapped(" / Changelog 12");
            ImGui::TextWrapped(" / Changelog 13");
            ImGui::TextWrapped(" / Changelog 14");
            ImGui::TextWrapped(" / Changelog 15");
        }
        else {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Credits");
            ImGui::Separator();
            ImGui::TextWrapped("Captain - PlaceHolderChangelog1");
            ImGui::TextWrapped("Dev - PlaceHolderChangelog2");
            ImGui::TextWrapped("Dev - PlaceHolderChangelog3");
            ImGui::TextWrapped("Dev - PlaceHolderChangelog4");
            ImGui::TextWrapped("Dev - PlaceHolderChangelog5");
            ImGui::TextWrapped("Intern - PlaceHolderChangelog6");
            ImGui::TextWrapped("Intern - PlaceHolderChangelog7");
            ImGui::TextWrapped("Intern - PlaceHolderChangelog8");
            ImGui::TextWrapped("Intern - PlaceHolderChangelog9");
            ImGui::TextWrapped("Intern - PlaceHolderChangelog10");
            ImGui::TextWrapped("Lead Designer - PlaceHolderChangelog11");
            ImGui::TextWrapped("Designer - PlaceHolderChangelog12");
            ImGui::TextWrapped("Designer - PlaceHolderChangelog13");
            ImGui::TextWrapped("Designer - PlaceHolderChangelog14");
            ImGui::TextWrapped("Designer - PlaceHolderChangelog15");
        }

        // End the window
        ImGui::End();

        // Pop the style variables and colors
        ImGui::PopStyleVar(3);
        ImGui::PopStyleColor();
    }
}
