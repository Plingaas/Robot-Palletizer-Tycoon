//
// Created by peter on 2/21/2023.
//

#include "IK.h"

bool isWithinWorkarea(Angles angles)
{

    if (angles.theta1 < J1_LOWER_LIMIT || angles.theta1 > J1_UPPER_LIMIT || isnan(angles.theta1)) return false;
    if (angles.theta2 < J2_LOWER_LIMIT || angles.theta2 > J2_UPPER_LIMIT || isnan(angles.theta2)) return false;
    if (angles.theta3 < J3_LOWER_LIMIT || angles.theta3 > J3_UPPER_LIMIT || isnan(angles.theta3)) return false;

    return true;
};


// Solves the inverse kinematics for J1, J2, J3 for a given position (x, y, z).
Angles IK(float x, float y, float z)
{

    Angles angles{};

    float theta1 = atan2(y, x);

    float z1_3 = z - a1;
    float x0_1 = a2*cos(theta1);
    float x1_3 = x - x0_1;
    float phi2 = atan2(z1_3, x1_3);
    float r1 = sqrt(x1_3*x1_3 + z1_3*z1_3);
    float phi1 = acos((a4*a4 - r1*r1 - a3*a3)/(-2*r1*a3));


    float theta2 = phi2 + phi1;

    float num = (r1*r1-a3*a3-a4*a4)/(-2*a3*a4);


    // sqrt() inaccuracy. This is needed to include certain edge case positions.
    if (num > -1.0000012 && num < -1.0) num = -1;

    float phi3 = acos(num);
    float theta3 = phi3 - threepp::math::PI;

    theta1 *= TO_DEGREES;
    theta2 *= TO_DEGREES;
    theta3 *= TO_DEGREES;

    angles.theta1 = theta1;
    angles.theta2 = theta2;
    angles.theta3 = theta3;
    angles.legal = isWithinWorkarea(angles);

    return angles;
};
