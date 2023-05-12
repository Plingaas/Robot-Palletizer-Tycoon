#include "ui/UpgradeUI.hpp"

void UpgradeUI::onRender() {

    ImGui::Begin("", false, ImGuiWindowFlags_NoResize);
    ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
    ImGui::Text("Upgrades");

    if (ImGui::Button("Robot Speed")) upgradeRobotSpeed = true;
    ImGui::SameLine();
    ImGui::Text("Cost: $50");

    if (ImGui::Button("Belt Speed")) upgradeBeltSpeed = true;
    ImGui::SameLine();
    ImGui::Text("Cost: $50");

    if (ImGui::Button("Spawn Rate")) upgradeSpawnRate = true;
    ImGui::SameLine();
    ImGui::Text("Cost: $50");

    if (ImGui::Button("Pallet Reward")) upgradePalletReward = true;
    ImGui::SameLine();
    ImGui::Text("Cost: $50");

    mouseHovered = ImGui::IsWindowHovered();
    ImGui::End();
}