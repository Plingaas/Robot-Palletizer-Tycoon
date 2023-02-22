//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_JOINT_H
#define THREEPP_VCPKG_TEST_JOINT_H
#include "threepp/threepp.hpp"
using namespace threepp;

namespace AR2 {

    enum Axis {x, y, z};
    class Joint {

    private:
        Axis rotation_axis = z;
        bool reverse_rotation = false;

    public:
        std::shared_ptr<Mesh> mesh;

        explicit Joint(const std::string &path);
        void set_rotation_axis(Axis axis);
        void set_reverse_rotation(bool reverse);
        void set_rotation(Vector3 rot);
        void set_position(Vector3 pos);
        void go_to(float degrees);

    };
}


#endif //THREEPP_VCPKG_TEST_JOINT_H
