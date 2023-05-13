#include "ui/UpgradeUI.hpp"
#include <iostream>
void UpgradeUI::onRender() {

    ImGui::SetNextWindowSize(ImVec2(200, 200));
    ImGui::Begin("");
    ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
    ImGui::Text("Upgrades");

    ImGui::Text("b -> Spawn a robot.");
    ImGui::Text("n -> Spawn a pallet.");
    ImGui::Text("m -> Spawn a conveyor.");

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