//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_ROBOT_H
#define THREEPP_VCPKG_TEST_ROBOT_H
#include "threepp/threepp.hpp"
#include "Joint.h"
#include "IK.h"

using namespace threepp;

namespace AR2 {


    class Robot {

    public:

        Robot();

        Joint* j0;
        Joint* j1;
        Joint* j2;
        Joint* j3;
        Joint* j4;
        Joint* j5;
        Joint* j6;
        Joint* gripper;

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void move_base_to(Vector3 pos);
        void go_to_xyz(float x, float y, float z);
        void go_to_xyz(Vector3 pos);
        void go_to_steps(float j1_steps, float j2_steps, float j3_steps);


    private:
        Vector3 base_pos;
        void go_to_angles(Angles angles);
    };
}



#endif //THREEPP_VCPKG_TEST_ROBOT_H
