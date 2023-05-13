#ifndef ROBOTCONTROLLER_UPGRADEUI_HPP
#define ROBOTCONTROLLER_UPGRADEUI_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"

using namespace threepp;

struct UpgradeUI : imgui_context {

    bool mouseHovered = false;

    bool upgradeRobotSpeed = false;
    bool upgradeBeltSpeed = false;
    bool upgradeSpawnRate = false;
    bool upgradePalletReward = false;

    float* upgradeRobotSpeedCost;
    float* upgradeBeltSpeedCost;
    float* upgradeSpawnRateCost;
    float* upgradePalletRewardCost;

    Vector3 pos;

    explicit UpgradeUI(const Canvas &canvas) : imgui_context(canvas.window_ptr()) {};

    void onRender();
};


#endif //ROBOTCONTROLLER_UPGRADEUI_HPP
