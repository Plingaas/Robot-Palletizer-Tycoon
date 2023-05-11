//
// Created by peter on 2/20/2023.
//

#include "robot_arm/Robot.hpp"

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

    j1->setRotationAxis(z);
    j2->setRotationAxis(y);
    j3->setRotationAxis(y);
    j4->setRotationAxis(x);
    j5->setRotationAxis(y);
    j6->setRotationAxis(x);

    j1->setReverseRotation(false);
    j2->setReverseRotation(true);
    j3->setReverseRotation(true);
    j4->setReverseRotation(true);
    j5->setReverseRotation(true);
    j6->setReverseRotation(true);

    Vector3 j0_offset{0, 0, 0};
    Vector3 j1_offset{0, 0, 87.12};
    Vector3 j2_offset{64.2, 51.4, 82.65};
    Vector3 j3_offset{305, -51.4, 0};
    Vector3 j4_offset{222.63, 0, 0};
    Vector3 j5_offset{0, 0, 0};
    Vector3 j6_offset{36.25, 0, 0};
    Vector3 gripper_offset{64, 0, 0};

    j0->setPosition(j0_offset);
    j1->setPosition(j1_offset);
    j2->setPosition(j2_offset);
    j3->setPosition(j3_offset);
    j4->setPosition(j4_offset);
    j5->setPosition(j5_offset);
    j6->setPosition(j6_offset);
    gripper->setPosition(gripper_offset);

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

void Robot::moveBaseTo(Vector3 pos) {
    base_pos = pos;
    j0->mesh->position = pos;
}

void Robot::goTo(float x, float y, float z) {
    goTo({x, y, z});
}


void Robot::goTo(Vector3 pos) {
    Vector3 relative_pos = pos - base_pos;
    Angles angles = IK(relative_pos, DOWN_LONG_X);

    goToAngles(angles);
    current_pos = pos;
}

void Robot::goToSteps(float j1_steps, float j2_steps, float j3_steps) {
    float j1_angle = j1_steps * TO_RADIANS / J1_STEPS_PER_DEG;
    float j2_angle = j2_steps * TO_RADIANS / J2_STEPS_PER_DEG;
    float j3_angle = j3_steps * TO_RADIANS / J3_STEPS_PER_DEG;

    Angles angles = IK3_6(j1_angle, j2_angle, j3_angle);

    goToAngles(angles);
}

void Robot::goToAngles(Angles angles) const {
    if (AR2::withinWorkArea(angles)) {
        j1->goTo(angles.theta1);
        j2->goTo(angles.theta2);
        j3->goTo(angles.theta3);
        j4->goTo(angles.theta4);
        j5->goTo(angles.theta5);
        j6->goTo(angles.theta6);
    }
}

void Robot::update(float dt) {
    if (conveyor == nullptr || pallet == nullptr)
        return;

    conveyor->update(dt);
    runConveyorLogic();

    if (program_running) {
        program.update(dt);

        if (!program.run)
            abortProgram();

        if (PID_active) {
            Vector3 regulation = PID_controller.regulate(program.position, current_pos, dt);
            move(regulation);
        } else {
            goTo(program.position);
        }
    }


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


void Robot::move(float x, float y, float z) {
    move({x, y, z});
}

void Robot::move(Vector3 rel) {
    goTo(current_pos + rel);
}

void Robot::setTarget(Vector3 target) {
    target_pos = target;
}

void Robot::setPIDParameters(float kp, float ti, float td) {
    PID_controller.params().set_params(kp, ti, td);
}

void Robot::setColors(Color _color1, Color _color2) {
    color1 = _color1;
    color2 = _color2;
}

void Robot::runProgram() {
    program_running = true;
    program.run = true;
    program.pause = false;
}

void Robot::abortProgram() {
    program_running = false;
    program.run = false;
    program.pause = false;
}

void Robot::pauseProgram() {
    program_running = true;
    program.run = true;
    program.pause = true;
}

bool Robot::isRunning() {
    return program_running;
}

void Robot::teachPosition(Vector4 command) {
    program.add(command);
}

void Robot::teachPause(float time) {
    program.addPause(time);
}

void Robot::attachPallet(std::shared_ptr<EuroPallet> pallet_) {
    pallet = pallet_;

    rest_pos = pick_pos + (pallet->corner_pos - pick_pos) * 0.5f;
    rest_pos.z = pick_pos.z + 100.0f;
    program.setRestPosition(rest_pos);
}

void Robot::attachConveyor(std::shared_ptr<ConveyorBelt> conveyor_) {
    conveyor = conveyor_;
    pick_pos = conveyor->position.clone() + Vector3{0.0f, -100.0f, 196.0f};
    program.generateSequence(pick_pos, false);

    if (pallet) {
        rest_pos = pick_pos + (pallet->corner_pos - pick_pos) * 0.5f;
        rest_pos.z = pick_pos.z + 100.0f;
        program.setRestPosition(rest_pos);
    }

}

void Robot::pickUp() {
    is_holding = true;
    item = conveyor->items.getTailValue();
    Vector3 drop_position = pallet->nextPosition(item);
    drop_position.z += item.size.z * 0.5f;
    program.generateSequence(drop_position, true);
    updateItemPosition();
    conveyor->removeItem();
}

void Robot::drop() {
    is_holding = false;
    item.mesh->position = pallet->nextPosition(item);
    pallet->addItem(item);
    *money += Box::value;
    if (pallet->item_count == 32) {
        pallet->clear(scene);
        *money += pallet->getValue();
    }

}

Program Robot::getProgram() {
    return program;
}

Vector3 Robot::getPos() {
    return current_pos;
}

void Robot::updateItemPosition() {

    Vector3 new_pos = current_pos;
    new_pos.z -= item.size.z * 0.5f;

    item.mesh->position = new_pos;
}

void Robot::runConveyorLogic() {
    if (conveyor->pause && !program_running) {
        runProgram();

    }

    if (program_running) {
        if (program.is_holding && !is_holding) {
            pickUp();
        } else if (!program.is_holding && is_holding) {
            drop();
        }

        if (is_holding)
            updateItemPosition();
    }
}

void Robot::upgradeSpeed(float rate) {
    if (*money > upgrade_cost) {
        *money -= upgrade_cost;
        upgrade_cost *= rate * rate;
        speed_multiplier *= rate;
        program.setR(1.0f / speed_multiplier);
    }

}
