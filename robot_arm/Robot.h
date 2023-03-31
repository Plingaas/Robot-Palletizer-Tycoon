//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_ROBOT_H
#define THREEPP_VCPKG_TEST_ROBOT_H
#include "threepp/threepp.hpp"
#include "Joint.h"
#include "tools/IK.h"
#include "tools/PID.h"
#include "tools/Program.h"
#include "../objects/items/Box.h"
#include "../objects/ConveyorBelt.h"
#include "../objects/EuroPallet.h"

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

        bool PID_active = true;
        inline static float *money = nullptr;
        std::shared_ptr<Scene> scene;
        ConveyorBelt* conveyor = nullptr;
        EuroPallet* pallet = nullptr;
        Vector3 rest_pos{};
        Vector3 pick_pos{};
        Vector3 drop_pos{};

        bool is_holding = false;
        Item item;

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void update(float dt);
        void move_base_to(Vector3 pos);
        void go_to(float x, float y, float z);
        void go_to(Vector3 pos);
        void move(float x, float y, float z);
        void move(Vector3 rel);
        void go_to_steps(float j1_steps, float j2_steps, float j3_steps);

        void set_colors(Color _color1, Color _color2);
        void set_target(Vector3 target);
        void set_pid_parameters(float kp, float ti, float td);
        void run_program();
        void abort_program();
        void pause_program();
        Program get_program();
        bool is_running();
        Vector3 get_pos();

        void teach_position(Vector4 command);
        void teach_pause(float time);
        void update_item_position();
        void pick_up();
        void drop();
        void conveyor_logic();
        void attach_conveyor(ConveyorBelt *conveyor_);
        void attach_pallet(EuroPallet *pallet);
        void upgrade_speed(float rate);

        [[nodiscard]] std::shared_ptr<Mesh> get_mesh() const { return j0->mesh; }

        explicit Robot();

    private:
        Color color1;
        Color color2;

        float speed_multiplier = 1.0f;
        float upgrade_cost = 5.0f;

        Vector3 base_pos;
        Vector3 target_pos{0, 0, 0};
        Vector3 current_pos{0.0f, -350.0f, 150.0f};
        PID PID_controller;

        Program program;
        bool program_running = false;

        void go_to_angles(Angles angles) const;


    };

}

#endif //THREEPP_VCPKG_TEST_ROBOT_H
