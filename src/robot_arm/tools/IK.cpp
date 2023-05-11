//
// Created by peter on 2/21/2023.
//

#include <iostream>
#include "robot_arm/tools/IK.hpp"

namespace AR2 {

    // STANDARD ROTATION MATRIXES
    Matrix3 RX(float angle) {
        return Matrix3
                {
                        1, 0, 0,
                        0, cos(angle), -sin(angle),
                        0, sin(angle), cos(angle)
                };
    }

    Matrix3 RY(float angle) {
        return Matrix3
                {
                        cos(angle), 0, sin(angle),
                        0, 1, 0,
                        -sin(angle), 0, cos(angle)
                };
    }

    Matrix3 RZ(float angle) {
        return Matrix3
                {
                        cos(angle), -sin(angle), 0,
                        sin(angle), cos(angle), 0,
                        0, 0, 1
                };
    }

    // ROTATION MATRIXES
    Matrix3 R0_1(float angle) {

        return RZ(angle).premultiply(P0_1);
    }

    Matrix3 R1_2(float angle) {

        return RZ(angle).premultiply(P1_2);
    }

    Matrix3 R2_3(float angle) {

        return RZ(angle).premultiply(P2_3);
    }

    Matrix3 R3_4(float angle) {

        return RZ(angle).premultiply(P3_4);
    }

    Matrix3 R4_5(float angle) {

        return RZ(angle).premultiply(P4_5);
    }

    Matrix3 R5_6(float angle) {

        return RZ(angle).premultiply(P5_6);
    }

    // DISPLACEMENT MATRIXES
    Vector3 D0_1(float angle) {
        return Vector3
                {
                        a2 * cos(angle),
                        a2 * sin(angle),
                        a1
                };
    };

    Vector3 D1_2(float angle) {
        return Vector3
                {
                        a3 * cos(angle),
                        a3 * sin(angle),
                        0
                };
    };

    Vector3 D2_3(float angle) {
        return Vector3
                {
                        0,
                        0,
                        0
                };
    };

    Vector3 D3_4(float angle) {
        return Vector3
                {
                        0,
                        0,
                        a4
                };
    };

    Vector3 D4_5(float angle) {
        return Vector3
                {
                        0,
                        0,
                        0
                };
    };

    Vector3 D5_6(float angle) {
        return Vector3
                {
                        (a5 + a6) * sin(angle),
                        0,
                        (a5 + a6) * cos(angle)
                };
    };

    // Denavit-Hartenberg parameter table
    Vector4 DH_TABLE(int n, float angle) {

        switch (n) {
            case 1: // 0 -> 1
                return Vector4{angle, HALF_PI, a2, a1};
            case 2: // 1 -> 2
                return Vector4{angle, 0.0f, a3, 0.0f};
            case 3: // 2 -> 3
                return Vector4{angle + HALF_PI, -HALF_PI, 0.0f, 0.0f};
            case 4: // 3 -> 4
                return Vector4{angle, HALF_PI, 0.0f, -a4};
            case 5: // 4 -> 5
                return Vector4{angle, -HALF_PI, 0.0f, 0.0f};
            case 6: // 5 -> 6
                return Vector4{angle, 0.0f, 0.0f, -(a5 + a6)};
            default:
                std::cerr << "Illegal n-value for DH frame.\n";
                return Vector4{}.setLength(0);
        };
    };

    // Returns the HTM for frame n-1 to n
    Matrix4 DH_HTM(int n, float angle) {
        Vector4 DH_values = DH_TABLE(n, angle);
        float theta = DH_values[0];
        float alpha = DH_values[1];
        float r = DH_values[2];
        float d = DH_values[3];

        float ct = cos(theta);
        float ca = cos(alpha);
        float st = sin(theta);
        float sa = sin(alpha);

        // Denavit-Hartenberg transformation matrix
        return Matrix4
                {
                        ct, -st * ca, st * sa, r * ct,
                        st, ct * ca, -ct * sa, r * st,
                        0, sa, ca, d,
                        0, 0, 0, 1
                };
    };

    Matrix3 getR0_3(Vector3 angles) {
        // Find HTM for frame 0 to 3
        Matrix4 H0_1 = DH_HTM(1, angles.x);
        Matrix4 H1_2 = DH_HTM(2, angles.y);
        Matrix4 H2_3 = DH_HTM(3, angles.z);

        Matrix4 H0_3 = H0_1.premultiply(H1_2).premultiply(H2_3);

        // Extract rotation matrix
        Matrix3 R0_3 =
                {
                        H0_3.elements[0], H0_3.elements[1], H0_3.elements[2],
                        H0_3.elements[4], H0_3.elements[5], H0_3.elements[6],
                        H0_3.elements[8], H0_3.elements[9], H0_3.elements[10]
                };

        return R0_3;
    };

    Matrix3 getR3_6(Vector3 angles, const Matrix3 &R_target) {
        Matrix3 R0_3 = getR0_3(angles);
        return R0_3.transpose().premultiply(R_target);
    };

    bool withinWorkArea(Angles angles) {
        if (angles.theta1 < J1_LOWER_LIMIT || angles.theta1 > J1_UPPER_LIMIT || isnan(angles.theta1)) return false;
        if (angles.theta2 < J2_LOWER_LIMIT || angles.theta2 > J2_UPPER_LIMIT || isnan(angles.theta2)) return false;
        if (angles.theta3 < J3_LOWER_LIMIT || angles.theta3 > J3_UPPER_LIMIT || isnan(angles.theta3)) return false;
        if (angles.theta4 < J4_LOWER_LIMIT || angles.theta1 > J4_UPPER_LIMIT || isnan(angles.theta4)) return false;
        if (angles.theta5 < J5_LOWER_LIMIT || angles.theta2 > J5_UPPER_LIMIT || isnan(angles.theta5)) return false;
        if (angles.theta6 < J6_LOWER_LIMIT || angles.theta3 > J6_UPPER_LIMIT || isnan(angles.theta6)) return false;

        return true;
    };


    // Solves the inverse kinematics for a given position (x, y, z).
    Angles IK(const Vector3 &pos, const Matrix3 &R_target) {

        Vector3 j3_offset = Vector3{0.0f, 0.0f, -(a5 + a6)}.applyMatrix3(R_target);
        Vector3 j3_pos = pos - j3_offset;

        return IK0_3(j3_pos, R_target);
    };

    Angles IK(float x, float y, float z, const Matrix3 &R_target ) {
        return IK({x, y, z}, R_target);
    };

    Angles IK0_3(const Vector3 &position, const Matrix3 &R_target) {
        float theta1 = atan2(position.y, position.x);
        float z1_3 = position.z - a1;
        float rx = position.x - a2 * cos(theta1);
        float ry = position.y - a2 * sin(theta1);
        float r = sqrt(rx * rx + ry * ry);
        float phi2 = atan2(z1_3, r);
        float r1 = sqrt(r * r + z1_3 * z1_3);
        float phi1 = acos((a4 * a4 - r1 * r1 - a3 * a3) / (-2 * r1 * a3));
        float theta2 = phi2 + phi1;
        float num = (r1 * r1 - a3 * a3 - a4 * a4) / (-2 * a3 * a4);

        // sqrt() inaccuracy. This is needed to include certain edge case positions.
        if (num > -1.0000012 && num < -1.0) num = -1;
        float phi3 = acos(num);
        float theta3 = phi3 - PI;

        return IK3_6(Vector3{theta1, theta2, theta3}, R_target);
    }

    Angles IK3_6(const Vector3 &angles, const Matrix3 &R_target) {
        Matrix3 R3_6 = getR3_6(angles, R_target);

        float r13 = R3_6.elements[2];
        float r23 = R3_6.elements[5];
        float r31 = R3_6.elements[6];
        float r32 = R3_6.elements[7];
        float r33 = R3_6.elements[8];

        float theta4 = atan2(r23, r13) + PI;
        float theta5 = acos(r33);
        float theta6 = atan2(-r32, r31);

        return {angles.x, angles.y, angles.z, theta4, theta5, theta6};
    }
}