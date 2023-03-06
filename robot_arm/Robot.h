//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_ROBOT_H
#define THREEPP_VCPKG_TEST_ROBOT_H
#include "threepp/threepp.hpp"
#include "Joint.h"
#include "tools/IK.h"
#include "tools/PID.h"

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

        bool PID_active;

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void update(float dt);
        void move_base_to(Vector3 pos);
        void go_to(float x, float y, float z);
        void go_to(Vector3 pos);
        void move_to(float x, float y, float z);
        void move_to(Vector3 rel);
        void go_to_steps(float j1_steps, float j2_steps, float j3_steps);

        void set_colors(Color _color1, Color _color2);
        void set_target(Vector3 target);
        void set_pid_parameters(float kp, float ti, float td);

        explicit Robot();

    private:
        Color color1;
        Color color2;

        Vector3 base_pos;
        Vector3 target_pos;
        Vector3 current_pos;
        PID PID_controller;
        void go_to_angles(Angles angles) const;
    };

}



#endif //THREEPP_VCPKG_TEST_ROBOT_H
