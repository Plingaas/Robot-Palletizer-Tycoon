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

class Game {

private:

    std::shared_ptr<PerspectiveCamera> camera;
    std::shared_ptr<Scene> scene;
    Raycaster raycaster;
    Vector2 mouse;

    //KeyboardListener keyListener;
    //MouseListener mouseListener;

public:

    List<std::shared_ptr<AR2::Robot>> robots;

    Game(){};

    void run(const int *A, const int *B, const int *C, char **port);

    void addRobot();
    std::shared_ptr<ConveyorBelt> createConveyor();
    std::shared_ptr<EuroPallet> createPallet();

    void checkListenerActions(KListener* keyListener, MListener* mouseListener, double &money);

};


#endif //THREEPP_VCPKG_TEST_APP_H
