//
// Created by peter on 2/20/2023.
//

#include "Robot.h"

#include "threepp/threepp.hpp"

using namespace AR2;

AR2::Robot::Robot() {

    j0 = new Joint("bin/data/models/j0.stl");
    j1 = new Joint("bin/data/models/j1.stl");
    j2 = new Joint("bin/data/models/j2.stl");
    j3 = new Joint("bin/data/models/j3.stl");

    j1->set_rotation_axis(z);
    j2->set_rotation_axis(y);
    j3->set_rotation_axis(y);

    j1->set_reverse_rotation(true);
    j2->set_reverse_rotation(true);
    j3->set_reverse_rotation(true);

    Vector3 j0_offset{0, 0, 0};
    Vector3 j1_offset{0, 0, 87.12};
    Vector3 j2_offset{64.2, 51.4, 82.65};
    Vector3 j3_offset{305, -51.4, 0};

    j0->set_position(j0_offset);
    j1->set_position(j1_offset);
    j2->set_position(j2_offset);
    j3->set_position(j3_offset);

    // Create links between joints by using parents
    j2->mesh->add(j3->mesh);
    j1->mesh->add(j2->mesh);
    j0->mesh->add(j1->mesh);



}

void Robot::go_to_xyz(float x, float y, float z)
{
    Angles angles = IK(x, y, z);

    j1->go_to(angles.theta1);
    j2->go_to(angles.theta2);
    j3->go_to(angles.theta3);

}

void Robot::go_to_steps(float j1_steps, float j2_steps, float j3_steps)
{
    float j1_angle = j1_steps/J1_STEPS_PER_DEG;
    float j2_angle = j2_steps/J2_STEPS_PER_DEG;
    float j3_angle = j3_steps/J3_STEPS_PER_DEG;

    j1->go_to(j1_angle);
    j2->go_to(j2_angle);
    j3->go_to(j3_angle);
};
