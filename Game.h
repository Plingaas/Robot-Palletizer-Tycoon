//
// Created by peter on 3/31/2023.
//

#ifndef ROBOTCONTROLLER_GAME_H
#define ROBOTCONTROLLER_GAME_H
#include "robot_arm/Robot.h"

class Game {

    Game();

    List<std::shared_ptr<AR2::Robot>> robots;

    void update(float dt);

};


#endif //ROBOTCONTROLLER_GAME_H
