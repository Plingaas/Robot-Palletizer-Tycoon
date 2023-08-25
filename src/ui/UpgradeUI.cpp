#include "ui/UpgradeUI.hpp"
#include <iostream>
void UpgradeUI::onRender() {

    ImGui::SetNextWindowSize(ImVec2(260, 220));
    ImGui::Begin("");
    ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

    ImGui::Text("To spawn - Key + Left Click");
    ImGui::Text("(R) Robot,");
    ImGui::SameLine();
    ImGui::Text("(C) Conveyor,");
    ImGui::SameLine();
    ImGui::Text("(P) Pallet");

    ImGui::Text("Upgrades");
    if (upgradeRobotSpeedCost != nullptr) {
        if (ImGui::Button("Robot Speed")) upgradeRobotSpeed = true;
        ImGui::SameLine();
        ImGui::Text("Cost: $%d", static_cast<int>(*upgradeRobotSpeedCost));
    }

    if (upgradeBeltSpeedCost != nullptr) {
        if (ImGui::Button("Belt Speed")) upgradeBeltSpeed = true;
        ImGui::SameLine();
        ImGui::Text("Cost: $%d", static_cast<int>(*upgradeBeltSpeedCost));
    }

    if (upgradeSpawnRateCost != nullptr) {
        if (ImGui::Button("Spawn rate")) upgradeSpawnRate = true;
        ImGui::SameLine();
        ImGui::Text("Cost: $%d", static_cast<int>(*upgradeSpawnRateCost));
    }

    if (upgradePalletRewardCost != nullptr) {
        if (ImGui::Button("Pallet Reward")) upgradePalletReward = true;
        ImGui::SameLine();
        ImGui::Text("Cost: $%d", static_cast<int>(*upgradePalletRewardCost));
    }

    mouseHovered = ImGui::IsWindowHovered();
    ImGui::End();
}