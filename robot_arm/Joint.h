//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_JOINT_H
#define THREEPP_VCPKG_TEST_JOINT_H
#include "../helpers/Helper.h"

namespace AR2 {

    static std::shared_ptr<BufferGeometry> j0_geo = load_stl("bin/data/models/j0_simplified.stl");
    static std::shared_ptr<BufferGeometry> j1_geo = load_stl("bin/data/models/j1_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j2_geo = load_stl("bin/data/models/j2_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j3_geo = load_stl("bin/data/models/j3_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j4_geo = load_stl("bin/data/models/j4_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j5_geo = load_stl("bin/data/models/j5_very_simplified.stl");
    static std::shared_ptr<BufferGeometry> j6_geo = load_stl("bin/data/models/j6_simplified.stl");
    static std::shared_ptr<BufferGeometry> gripper_geo = load_stl("bin/data/models/servo_gripper_simplified.stl");

    class Joint {

    private:
        Axis rotation_axis = z;
        bool reverse_rotation = false;

    public:
        std::shared_ptr<Mesh> mesh;

        static std::unique_ptr<Joint> create(std::shared_ptr<BufferGeometry> &geometry, Color color)
        {
            return std::make_unique<Joint>(geometry, color);
        }

        explicit Joint(std::shared_ptr<BufferGeometry> &geometry, Color color);
        void set_rotation_axis(Axis axis);
        void set_reverse_rotation(bool reverse);
        void set_rotation(Vector3 rot);
        void set_position(Vector3 pos);
        void go_to(float degrees);

    };
}


#endif //THREEPP_VCPKG_TEST_JOINT_H
