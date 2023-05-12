//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_JOINT_H
#define THREEPP_VCPKG_TEST_JOINT_H

#include "helpers/Helper.hpp"

namespace AR2 {

    // Geometries of all the different parts of the robot.
    static std::shared_ptr<BufferGeometry> j0_geo = loadSTL("bin/data/models/j0_simplified.stl");
    static std::shared_ptr<BufferGeometry> j1_geo = loadSTL("bin/data/models/j1_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j2_geo = loadSTL("bin/data/models/j2_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j3_geo = loadSTL("bin/data/models/j3_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j4_geo = loadSTL("bin/data/models/j4_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j5_geo = loadSTL("bin/data/models/j5_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j6_geo = loadSTL("bin/data/models/j6_simplified.stl");
    static std::shared_ptr<BufferGeometry> gripper_geo = loadSTL("bin/data/models/servo_gripper_simplified.stl");

    /**
     * @brief A class for a robot joint.
     */
    class Joint {

    private:
        Axis rotationAxis = z;
        bool reverseRotation = false;

    public:

        std::shared_ptr<Mesh> mesh;

        /**
         * @brief The constructor for a joint.
         *
         * @param geometry Its geometry.
         * @param color Its mesh's color.
         */
        explicit Joint(std::shared_ptr<BufferGeometry> &geometry, Color color);

        /**
         * @brief Creates a new joint.
         *
         * This static function creates a new joint given its
         * geometry and color.
         *
         * @param geometry The geometry of the joint.
         * @param color The color of its mesh.
         * @return Returns a std::unique_ptr<Joint> for the newly created Joint.
         */
        static std::unique_ptr<Joint> create(std::shared_ptr<BufferGeometry> &geometry, Color color) {
            return std::make_unique<Joint>(geometry, color);
        }

        /**
         * @brief Sets the axis to rotate around.
         *
         * @param axis The axis to rotate around. x = 0, y = 1, z = 2.
         *
         * @return void.
         */
        void setRotationAxis(Axis axis);

        /**
         * @brief Sets the reverseRotation variable.
         *
         * Sometimes the robot has to have reverse rotation
         * because of the inverse kinematics. This is a simple fix
         * where you can just reverse the rotation if needed.
         *
         * @param reverse Whether it should be reverse or not.
         *
         * @return void.
         */
        void setReverseRotation(bool reverse);

        /**
         * @brief Sets the absolute rotation of its mesh.
         *
         * @param rot The rotation to set.
         *
         * @return void.
         */
        void setRotation(Vector3 rot) const;

        /**
         * @brief Sets the absolute position of its mesh.
         *
         * @param pos The position to set.
         *
         * @return void.
         */
        void setPosition(Vector3 pos) const;

        /**
         * @brief Sets absolute rotation around its rotation axis.
         *
         * This differs from setRotation because it only rotates
         * around the rotation axis for the joint rather than
         * all three axis.
         *
         * @param degrees Absolute rotation of joint in its rotation axis.
         *
         * @return void.
         */
        void goTo(float degrees);

    };
}


#endif //THREEPP_VCPKG_TEST_JOINT_H
