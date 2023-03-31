//
// Created by peter on 2/20/2023.
//

#include "Robot.h"

#include "threepp/threepp.hpp"

using namespace AR2;

AR2::Robot::Robot() {

    j0 = Joint::create(j0_geo, Color::pink);
    j1 = Joint::create(j1_geo, Color::purple);
    j2 = Joint::create(j2_geo, Color::pink);
    j3 = Joint::create(j3_geo, Color::purple);
    j4 = Joint::create(j4_geo, Color::pink);
    j5 = Joint::create(j5_geo, Color::purple);
    j6 = Joint::create(j6_geo, Color::pink);
    gripper = Joint::create(gripper_geo, Color::purple);

    j1->set_rotation_axis(z);
    j2->set_rotation_axis(y);
    j3->set_rotation_axis(y);
    j4->set_rotation_axis(x);
    j5->set_rotation_axis(y);
    j6->set_rotation_axis(x);

    j1->set_reverse_rotation(false);
    j2->set_reverse_rotation(true);
    j3->set_reverse_rotation(true);
    j4->set_reverse_rotation(true);
    j5->set_reverse_rotation(true);
    j6->set_reverse_rotation(true);

    Vector3 j0_offset{0, 0, 0};
    Vector3 j1_offset{0, 0, 87.12};
    Vector3 j2_offset{64.2, 51.4, 82.65};
    Vector3 j3_offset{305, -51.4, 0};
    Vector3 j4_offset{222.63, 0, 0};
    Vector3 j5_offset{0, 0, 0};
    Vector3 j6_offset{36.25, 0, 0};
    Vector3 gripper_offset{64,0,0};

    j0->set_position(j0_offset);
    j1->set_position(j1_offset);
    j2->set_position(j2_offset);
    j3->set_position(j3_offset);
    j4->set_position(j4_offset);
    j5->set_position(j5_offset);
    j6->set_position(j6_offset);
    gripper->set_position(gripper_offset);

    // Create links between joints by using parents
    j6->mesh->add(gripper->mesh);
    j5->mesh->add(j6->mesh);
    j4->mesh->add(j5->mesh);
    j3->mesh->add(j4->mesh);
    j2->mesh->add(j3->mesh);
    j1->mesh->add(j2->mesh);
    j0->mesh->add(j1->mesh);

    PID_controller.params().set_params(0.2f, 0.0005f, 0.0f);
    PID_controller.setWindupGuard(0.003f);
}

void Robot::move_base_to(Vector3 pos)
{
    base_pos = pos;
    j0->mesh->position = pos;
}

void Robot::go_to(float x, float y, float z)
{
    go_to({x, y, z});
}

void Robot::go_to(Vector3 pos)
{
    Vector3 relative_pos = pos - base_pos;
    Angles angles = IK(relative_pos, DOWN_LONG_X);

    go_to_angles(angles);
    current_pos = pos;
}

void Robot::go_to_steps(float j1_steps, float j2_steps, float j3_steps)
{
    float j1_angle = j1_steps * TO_RADIANS/J1_STEPS_PER_DEG;
    float j2_angle = j2_steps * TO_RADIANS/J2_STEPS_PER_DEG;
    float j3_angle = j3_steps * TO_RADIANS/J3_STEPS_PER_DEG;

    Angles angles = IK3_6(j1_angle, j2_angle, j3_angle);

    go_to_angles(angles);
}

void Robot::go_to_angles(Angles angles) const
{
    if (AR2::within_work_area(angles))
    {
        j1->go_to(angles.theta1);
        j2->go_to(angles.theta2);
        j3->go_to(angles.theta3);
        j4->go_to(angles.theta4);
        j5->go_to(angles.theta5);
        j6->go_to(angles.theta6);
    }
}

void Robot::update(float dt)
{

    if (program_running) {
        program.update(dt);

        if (!program.run)
            abort_program();

        if (PID_active)
        {
            Vector3 regulation = PID_controller.regulate(program.position, current_pos, dt);
            move(regulation);
        } else {
            go_to(program.position);
        }
    }

    conveyor_logic();

    // Not sure if this will be used
    /*else
    {
        if (PID_active)
        {
            Vector3 new_pos = PID_controller.regulate(target_pos, current_pos, dt);
            move(new_pos);
        }
    }*/
}


void Robot::move(float x, float y, float z)
{
    move({x, y, z});
}

void Robot::move(Vector3 rel)
{
    go_to(current_pos + rel);
}

void Robot::set_target(Vector3 target)
{
    target_pos = target;
}

void Robot::set_pid_parameters(float kp, float ti, float td)
{
    PID_controller.params().set_params(kp, ti, td);
}

void Robot::set_colors(Color _color1, Color _color2)
{
    color1 = _color1;
    color2 = _color2;
}

void Robot::run_program()
{
    program_running = true;
    program.run = true;
    program.pause = false;
}

void Robot::abort_program()
{
    program_running = false;
    program.run = false;
    program.pause = false;
}

void Robot::pause_program()
{
    program_running = true;
    program.run = true;
    program.pause = true;
}

bool Robot::is_running()
{
    return program_running;
}

void Robot::teach_position(Vector4 command)
{
    program.add(command);
}

void Robot::teach_pause(float time)
{
    program.add_pause(time);
}


void Robot::pick_up()
{
    is_holding = true;
    item = conveyor->items.getTailValue();
    Vector3 drop_position = pallet->next_position(item);
    drop_position.z += item.size.z*0.5f;
    program.replace_drop_sequence(drop_position);
    update_item_position();
    conveyor->remove_item();

}

void Robot::drop()
{
    is_holding = false;
    item.mesh->position = pallet->next_position(item);
    pallet->add_item(item);
}

Program Robot::get_program()
{
    return program;
}

Vector3 Robot::get_pos()
{
    return current_pos;
}

void Robot::update_item_position()
{

    Vector3 new_pos = current_pos;
    new_pos.z -= item.size.z*0.5f;

    item.mesh->position = new_pos;
}

void Robot::conveyor_logic()
{
    if (conveyor->pause && !program_running)
    {
        run_program();

    }

    if (program_running)
    {
        if (program.is_holding && !this->is_holding)
        {
            pick_up();
        }
        else if (!program.is_holding && this->is_holding)
        {
            drop();
        }

        if (is_holding)
            update_item_position();
    }
}
