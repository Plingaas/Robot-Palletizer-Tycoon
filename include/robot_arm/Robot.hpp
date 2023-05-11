//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_ROBOT_H
#define THREEPP_VCPKG_TEST_ROBOT_H

#include "threepp/threepp.hpp"
#include "Joint.hpp"
#include "tools/IK.hpp"
#include "tools/PID.hpp"
#include "tools/Program.hpp"
#include "objects/ConveyorBelt.hpp"
#include "objects/EuroPallet.hpp"

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
        inline static double *money = nullptr;
        std::shared_ptr<Scene> scene;
        std::shared_ptr<ConveyorBelt> conveyor = nullptr;
        std::shared_ptr<EuroPallet> pallet = nullptr;
        Vector3 rest_pos{};
        Vector3 pick_pos{};
        Vector3 drop_pos{};

        bool is_holding = false;
        Item item;

        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        void update(float dt);

        void moveBaseTo(Vector3 pos);

        void goTo(float x, float y, float z);

        void goTo(Vector3 pos);

        void move(float x, float y, float z);

        void move(Vector3 rel);

        void goToSteps(float j1_steps, float j2_steps, float j3_steps);

        void setColors(Color _color1, Color _color2);

        void setTarget(Vector3 target);

        void setPIDParameters(float kp, float ti, float td);

        void runProgram();

        void abortProgram();

        void pauseProgram();

        Program getProgram();

        bool isRunning();

        Vector3 getPos();

        void teachPosition(Vector4 command);

        void teachPause(float time);

        void updateItemPosition();

        void pickUp();

        void drop();

        void runConveyorLogic();

        void attachConveyor(std::shared_ptr<ConveyorBelt> conveyor_);

        void attachPallet(std::shared_ptr<EuroPallet> pallet);

        void upgradeSpeed(float rate);

        [[nodiscard]] std::shared_ptr<Mesh> getMesh() const { return j0->mesh; }

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

        void goToAngles(Angles angles) const;


    };

}

#endif //THREEPP_VCPKG_TEST_ROBOT_H
