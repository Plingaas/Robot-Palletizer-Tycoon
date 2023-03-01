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

        std::unique_ptr<Joint> j0;
        std::unique_ptr<Joint> j1;
        std::unique_ptr<Joint> j2;
        std::unique_ptr<Joint> j3;
        std::unique_ptr<Joint> j4;
        std::unique_ptr<Joint> j5;
        std::unique_ptr<Joint> j6;
        std::unique_ptr<Joint> gripper;

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void move_base_to(Vector3 pos);
        void go_to_xyz(float x, float y, float z);
        void go_to_xyz(Vector3 pos);
        void go_to_steps(float j1_steps, float j2_steps, float j3_steps);

        explicit Robot();

    private:

        Vector3 base_pos;
        void go_to_angles(Angles angles);

    };

}



#endif //THREEPP_VCPKG_TEST_ROBOT_H
