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

    float* upgradeRobotSpeedCost = nullptr;
    float* upgradeBeltSpeedCost = nullptr;
    float* upgradeSpawnRateCost = nullptr;
    float* upgradePalletRewardCost = nullptr;

    Vector3 pos;

    /**
     * @brief Constructor for the UpgradeUi.
     *
     * @param canvas The canvas the UpgradeUi will exist on.
     *
     * @return void.
     */
    explicit UpgradeUI(const Canvas &canvas) : imgui_context(canvas.window_ptr()) {};

    /**
     * @brief The update loop.
     *
     * This is where the UpgradeUi is constructed and events are looked for.
     *
     * @return void.
     */
    void onRender();
};


#endif //ROBOTCONTROLLER_UPGRADEUI_HPP
