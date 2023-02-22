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

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void go_to_xyz(float x, float y, float z);
        void go_to_steps(float j1_steps, float j2_steps, float j3_steps);
        Joint* j0;
        Joint* j1;
        Joint* j2;
        Joint* j3;
        Joint* j4;
        Joint* j5;
        Joint* j6;

    private:

    };
}



#endif //THREEPP_VCPKG_TEST_ROBOT_H
