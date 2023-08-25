//
// Created by peter on 2/21/2023.
//

#ifndef THREEPP_VCPKG_TEST_APP_H
#define THREEPP_VCPKG_TEST_APP_H
#include "threepp/threepp.hpp"
#include "threepp/core/Raycaster.hpp"
#include "robot_arm/Robot.hpp"
#include "ui/UpgradeUI.hpp"
#include "listener/Listener.hpp"
#include "helpers/LinkedList.hpp"
#include "objects/ConveyorBelt.hpp"
#include "objects/EuroPallet.hpp"
#include "threepp/helpers/SpotLightHelper.hpp"
#include "threepp/lights/LightShadow.hpp"
using namespace threepp;

/**
 * @brief Represents the game.
 *
 * This class takes care of running the game in this project.
 *
 */
class Game {

private:

    Canvas canvas;
    GLRenderer renderer;
    std::shared_ptr<PerspectiveCamera> camera;
    std::shared_ptr<Scene> scene;
    std::unique_ptr<UpgradeUI> ui;
    OrbitControls controls;

    // For listeners
    float t1 = 0;
    float t2 = 0;

    KListener keyListener;
    MListener mouseListener;
    Vector2 mouse;
    std::unique_ptr<MouseMoveListener> l;

    Raycaster raycaster;

    float money = 999999999.0f;

protected:

public:

    List<std::shared_ptr<AR2::Robot>> robots;

    /**
     * @brief The Game's constructor.
     */
    Game();

    /**
     * @brief Sets up the scene
     *
     * Adds floor, light, etc...
     *
     * @return void.
     */
    void setupScene();

    /**
     * @brief Sets up the listeners
     *
     * Adds mouse and keyboard listeners
     *
     * @return void.
     */
    void setupListeners();

    /**
     * @brief Starts the game.
     *
     * This is the function that starts the game.
     * Once this function is called the game is ran until
     * the window is closed.
     *
     * @return void.
     */
    void runGame();

    /**
     * @brief Calls every update function.
     * @param dt How much time the last frame took.
     */
    void updateGame(float dt);

    /**
     * @brief Updates all the robots.
     *
     * @param dt How much time the last frame took.
     */
    void updateRobots(float dt);

    /**
     * @brief Casts a ray and returns intersections.
     *
     * @return Returns std::vector<Intersection>.
     */
    std::vector<Intersection> castRay();

    /**
     * @brief Adds a robot to the back of the list.
     *
     * @param pos Position to place the robot.
     * @return void.
     */
    void createRobot(Vector3 pos = {0.0f, 0.0f, 0.0f});

    /**
     * @brief Creates a conveyor belt for the robot.
     *
     * The conveyor is made for the last robot in the list.
     * If the robot already has a conveyor, the function will return
     * without doing anything.
     *
     * @param pos The position to be set.
     *
     * @return Returns a std::shared_ptr<ConveyorBelt> for the newly created conveyor belt.
     */
    void createConveyor(Vector3 pos = {0.0f, 0.0f, 0.0f});

    /**
     * @brief Creates a pallet for the robot.
     *
     * The pallet is made for the last robot in the list.
     * If the robot already has a pallet, the function will return
     * without doing anything.
     *
     * @param pos The position to be set.
     *
     * @return Returns a std::shared_ptr<EuroPallet> for the newly created pallet.
     */
    void createPallet(Vector3 pos = {0.0f, 0.0f, 0.0f});

    /**
     * @brief Looks for actions to respond to user input.
     *
     * Actions related to key and mouse events are taken care
     * of in this function. Actions such as upgrading items,
     * creating new robots, conveyor belts and pallets.
     *
     * @param keyListener A pointer to the key listener.
     * @param mouseListener A pointer to the mouse listener.
     *
     * @return void.
     */
    void checkListenerActions();

    /**
     * @brief Checks if user has tried to upgrade
     *
     * Checks the UpgradeUI object to see if there
     * are any UI-buttons pressed. If there is a pressed
     * button it will try to upgrade whatever the user
     * tried to.
     *
     * @return void.
     */
    void checkUpgrades();

};


#endif //THREEPP_VCPKG_TEST_APP_H
