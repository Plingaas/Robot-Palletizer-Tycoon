//
// Created by peter on 2/21/2023.
//

#ifndef THREEPP_VCPKG_TEST_IK_H
#define THREEPP_VCPKG_TEST_IK_H

#include "threepp/threepp.hpp"

using namespace threepp;

namespace AR2 {


    // LINK LENGTHS
    const float a1 = 169.77f;
    const float a2 = 64.2f;
    const float a3 = 305.0f;
    const float a4 = 222.63f;
    const float a5 = 36.25f;
    //const float a6 = 52.0f; // End effector full length is 64
    const float a6 = 0.0f; // temporary use
    const float a7 = 32.66f; // End effector pinch offset;

    // LINK MAX ROTATION LIMITS
    const float J1_LOWER_LIMIT = -2.96705972839f; // -170 deg
    const float J1_UPPER_LIMIT = 2.96705972839f; // 170 deg

    const float J2_LOWER_LIMIT = -0.87266462599f; // 50 deg
    const float J2_UPPER_LIMIT = 2.30383461263f; // 132 deg

    const float J3_LOWER_LIMIT = -2.44346095279f; // -140 deg
    const float J3_UPPER_LIMIT = 0.01745329251f; // 1 deg

    const float J4_LOWER_LIMIT = -math::PI; // -180 deg
    const float J4_UPPER_LIMIT = math::PI; // 180 deg

    const float J5_LOWER_LIMIT = -2.35619449019f; // -135 deg
    const float J5_UPPER_LIMIT = 2.35619449019f; // 135 deg

    const float J6_LOWER_LIMIT = -math::PI; // -180 deg
    const float J6_UPPER_LIMIT = math::PI; // 180 deg

    // CONSTANTS
    const float TO_DEGREES = 180.0f / math::PI;
    const float TO_RADIANS = math::PI / 180.0f;
    const float PI = math::PI;
    const float HALF_PI = math::PI * 0.5f;

    // Stepper motor steps per degree rotation.
    // Used to convert serial data from the real robot to fit this project.
    const float J1_STEPS_PER_DEG = 88.88888889;
    const float J2_STEPS_PER_DEG = 55.55555567;
    const float J3_STEPS_PER_DEG = 55.55555567;
    const float J4_STEPS_PER_DEG = 0;
    const float J5_STEPS_PER_DEG = 0;
    const float J6_STEPS_PER_DEG = 0;

    // PROJECTION MATRIXES AT REST POSITION
    static const Matrix3 P0_1
            {
                    1, 0, 0,
                    0, 0, -1,
                    0, 1, 0
            };

    // Projection of joint 2 on joint 1
    static const Matrix3 P1_2
            {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            };

    // Projection of joint 3 on joint 2
    static const Matrix3 P2_3
            {
                    0, 0, -1,
                    1, 0, 0,
                    0, -1, 0
            };

    // Projection of joint 4 on joint 3
    static const Matrix3 P3_4
            {
                    1, 0, 0,
                    0, 0, -1,
                    0, 1, 0
            };

    // Projection of joint 5 on joint 4
    static const Matrix3 P4_5
            {
                    1, 0, 0,
                    0, 0, 1,
                    0, -1, 0
            };

    // Projection of joint 6 on joint 5
    static const Matrix3 P5_6
            {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            };

    // Projection of joint 6 on joint 0
    static const Matrix3 P6_0
            {
                    0, 0, -1,
                    0, 1, 0,
                    1, 0, 0
            };

    static const Matrix3 DOWN_LONG_X
            {
                    0, 1, 0,
                    -1, 0, 0,
                    0, 0, 1
            };

    struct Angles {
        float theta1;
        float theta2;
        float theta3;
        float theta4;
        float theta5;
        float theta6;

        inline void operator*=(float value) {
            theta1 *= value;
            theta2 *= value;
            theta3 *= value;
            theta4 *= value;
            theta5 *= value;
            theta6 *= value;
        };

        inline void operator*(float value) {
            return *this *= value;
        }
    };

    // Calculates the IK for the robot
    Angles IK(float x, float y, float z, const Matrix3 &R_target = P6_0);

    Angles IK(const Vector3 &position, const Matrix3 &R_target = P6_0);

    // Calculates the IK for frame 0 to 3 (POSITIONING)
    Angles IK0_3(const Vector3 &position, const Matrix3 &R_target = P6_0);

    // Calculates the IK for frame 3 to 6 (ORIENTATION)
    Angles IK3_6(float theta1, float theta2, float theta3, const Matrix3 &R_target = P6_0);

    bool withinWorkArea(Angles);

}
#endif //THREEPP_VCPKG_TEST_IK_H