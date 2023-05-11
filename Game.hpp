//
// Created by peter on 2/21/2023.
//

#ifndef THREEPP_VCPKG_TEST_APP_H
#define THREEPP_VCPKG_TEST_APP_H

#include "threepp/extras/imgui/imgui_context.hpp"

#include "threepp/threepp.hpp"
#include "threepp/core/Raycaster.hpp"
#include "robot_arm/Robot.hpp"
#include "UI/UI.hpp"
#include "listener/Listener.hpp"
#include "serial_communication/Serial.hpp"
#include "helpers/LinkedList.hpp"
#include "objects/ConveyorBelt.hpp"
#include "objects/EuroPallet.hpp"

using namespace threepp;

/**
 * @brief Represents the game.
 *
 * This class takes care of running the game in this project.
 *
 */
class Game {

private:

    std::shared_ptr<PerspectiveCamera> camera;
    std::shared_ptr<Scene> scene;
    Raycaster raycaster;
    Vector2 mouse;


public:

    List<std::shared_ptr<AR2::Robot>> robots;

    /**
     * @brief The Game's constructor.
     */
    Game(){};

    /**
     * @brief Starts the game.
     *
     * This is the function that starts the whole game.
     * Once this function is called the game is ran until
     * the window is closed.
     *
     * @param serialData The serial data for visualizing a real robot.
     * @param port The port to connect to.
     *
     * @return void.
     */
    void run(const std::array<int, 3> *serialData, char **port);

    /**
     * @brief Adds a robot to the back of the list.
     *
     * @return void.
     */
    void addRobot();

    /**
     * @brief Creates a conveyor belt for the robot.
     *
     * The conveyor is made for the last robot in the list.
     * If the robot already has a conveyor, the function will return
     * without doing anything.
     *
     * @return Returns a std::shared_ptr<ConveyorBelt> for the newly created conveyor belt.
     */
    std::shared_ptr<ConveyorBelt> createConveyor();

    /**
     * @brief Creates a pallet for the robot.
     *
     * The pallet is made for the last robot in the list.
     * If the robot already has a pallet, the function will return
     * without doing anything.
     *
     * @return Returns a std::shared_ptr<EuroPallet> for the newly created pallet.
     */
    std::shared_ptr<EuroPallet> createPallet();

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
    void checkListenerActions(KListener* keyListener, MListener* mouseListener);

};


#endif //THREEPP_VCPKG_TEST_APP_H
