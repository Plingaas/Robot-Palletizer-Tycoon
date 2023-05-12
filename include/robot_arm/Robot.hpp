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


    /**
     * @brief Represents a robot with joints.
     */
    class Robot {

    public:

        // Its joints
        std::unique_ptr<Joint> j0;
        std::unique_ptr<Joint> j1;
        std::unique_ptr<Joint> j2;
        std::unique_ptr<Joint> j3;
        std::unique_ptr<Joint> j4;
        std::unique_ptr<Joint> j5;
        std::unique_ptr<Joint> j6;
        std::unique_ptr<Joint> gripper;

        bool PIDActive = true;
        inline static double *money = nullptr;
        std::shared_ptr<Scene> scene;

        // Its attached conveyor and pallet
        std::shared_ptr<ConveyorBelt> conveyor = nullptr;
        std::shared_ptr<EuroPallet> pallet = nullptr;

        // Item related positions
        Vector3 restPos{};
        Vector3 pickPos{};
        Vector3 dropPos{};

        bool isHolding = false;
        Item item;

        /**
         * @brief The Robot's constructor.
         */
        explicit Robot();

        /**
         * @brief Creates a new robot.
         *
         * @return Returns a std::shared_ptr<Robot> for the created robot.
         */
        static std::shared_ptr<Robot> create() {
            return std::make_shared<Robot>();
        }

        /**
         * @brief Updates the robot
         *
         * This function takes care of moving the robot as well as letting its
         * program, conveyor and pallet update too. If the robot does not have
         * a conveyor belt as well as a pallet attached, it will return without
         * doing any actions.
         *
         * @param dt How much time the last frame took.
         *
         * @return void.
         */
        void update(float dt);

        /**
         * @brief Moves the base of the robot to a new position.
         *
         * @param pos The new position to move to.
         *
         * @return void.
         */
        void moveBaseTo(Vector3 pos);

        /**
         * @brief Moves the end effector.
         *
         * @param x The desired x position.
         * @param y The desired y position.
         * @param z The desired z position.
         *
         * @return void.
         */
        void goTo(float x, float y, float z);

        /**
         * @brief Moves the end effector.
         *
         * @param pos The desired position.
         *
         * @return void.
         */
        void goTo(Vector3 pos);

        /**
         * @brief Moves by a relative amount
         *
         * @param x Desired displacement in x direction.
         * @param y Desired displacement in y direction.
         * @param z Desired displacement in z direction.
         */
        void move(float x, float y, float z);

        /**
         * @brief Moves by a relative amount
         *
         * @param rel Desired displacement.
         *
         * @return void.
         */
        void move(Vector3 rel);

        /**
         * @brief Moves the three first joints.
         *
         * This is used for connecting to the real robot.
         * The real robot is controlled by stepper motors and its position
         * is sent in the steps domain. This function will translate steps to
         * degrees and move the joints correspondingly.
         *
         * @param steps Array with all stepper motors' step count.
         */
        void goToSteps(const std::array<int, 3> &steps);

        /**
         * @brief Sets the color of the robot.
         *
         * The color of the robot is bicolored. Every second
         * joint will be color 1 and color 2 respectively.
         * @param color1 The first color.
         * @param color2 The second color.
         *
         * @return void.
         */
        void setColors(Color color1, Color color2);

        /**
         * @brief Sets the target position.
         *
         * Used for thg visualization tool when you want
         * to move the robot to a target position.
         *
         * @param target The target position.
         *
         * @return void.
         */
        void setTarget(Vector3 target);

        /**
         * @brief Sets the PID parameters.
         *
         * @param kp Proportional variable.
         * @param ti Integral variable.
         * @param td Derivative variable.
         *
         * @return void.
         */
        void setPIDParameters(float kp, float ti, float td);

        /**
         * @brief Runs or stops the program.
         *
         * @param run If it should run or not.
         * @return void.
         */
        void runProgram(bool run);

        /**
         * @brief Getter for the program.
         *
         * @return Returns the program.
         */
        Program getProgram();

        /**
         * @brief Checks if program is running.
         *
         * @return Returns true if running, false if not.
         */
        bool isRunning();

        /**
         * @brief Getter for the current end effector position.
         *
         * @return Returns the position as a Vector3.
         */
        Vector3 getPos();

        /**
         * @brief Teaches the robot a new position.
         *
         * This adds another command to the program.
         *
         * @param command The command to teach.
         *
         * @return void.
         */
        void teachPosition(Vector4 command);

        /**
         * @brief Teaches the robot to pause.
         *
         * This adds a pause to the back of the program.
         *
         * @param time The amount of time in seconds to pause.
         *
         * @return void.
         */
        void teachPause(float time);

        /**
         * @brief Updates the position of the held item.
         *
         * @return void.
         */
        void updateItemPosition();

        /**
         * @brief Picks up the last item from the conveyor belt.
         *
         * @return void.
         */
        void pickUp();

        /**
         * @brief Drops the held item onto the pallet.
         *
         * @return void.
         */
        void drop();

        /**
         * @brief Runs the logic.
         *
         * This function takes care off starting to run the robot.
         * It also takes care of picking up items, holding onto items and
         * dropping them.
         *
         * @return void.
         */
        void runLogic();

        /**
         * @brief Attaches a conveyor belt to the robot.
         *
         * The attached conveyor is the conveyor that the robot
         * will be picking items from.
         *
         * @param conveyor_ The conveyor belt to attach.
         *
         * @return void.
         */
        void attachConveyor(const std::shared_ptr<ConveyorBelt> &conveyor_);

        /**
         * @brief Attaches a pallet to the robot.
         *
         * The attached pallet is the belt that the robot
         * will be dropping off items on.
         * @param pallet The pallet to attach.
         *
         * @return void.
         */
        void attachPallet(const std::shared_ptr<EuroPallet> &pallet);

        /**
         * @brief Upgrades the robot speed.
         *
         * This sets the time multiplier for the robot's
         * program so that it takes less time to reach the
         * desired positions.
         *
         * @param multiplier The amount to multiply by.
         *
         * @return void.
         */
        void upgradeSpeed(float multiplier);

        /**
         * @brief Gets the robot's mesh.
         *
         * @return Returns a std::shared_ptr<Mesh> for its mesh.
         */
        [[nodiscard]] std::shared_ptr<Mesh> getMesh() const { return j0->mesh; }

    private:

        float speedMultiplier = 1.0f;
        float upgradeCost = 5.0f;

        Vector3 basePos;
        Vector3 targetPos{0, 0, 0};
        Vector3 currentPos{0.0f, -350.0f, 150.0f};
        PID PIDController;

        Program program;

        /**
         * @brief Moves the robot joints to the given angles.
         *
         * The robot will only move to the location if it is within the workspace.
         *
         * @param angles The set of angles to move to.
         *
         * @return void.
         */
        void goToAngles(Angles angles) const;

    };

}

#endif //THREEPP_VCPKG_TEST_ROBOT_H
