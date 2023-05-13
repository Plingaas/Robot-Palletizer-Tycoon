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

    changeMeshColor(j6->mesh, Color::white);

    PIDController.params().set_params(0.2f, 0.0005f, 0.0f);
    PIDController.setWindupGuard(0.003f);

}

void Robot::moveBaseTo(Vector3 pos) {
    basePos = pos;
    j0->mesh->position = pos;
}

void Robot::goTo(float x, float y, float z) {
    goTo({x, y, z});
}


void Robot::goTo(Vector3 pos) {
    Vector3 relative_pos = pos - basePos;
    Angles angles = IK(relative_pos, DOWN_LONG_X);

    goToAngles(angles);
    currentPos = pos;
}

void Robot::goToSteps(const std::array<int, 3> &steps) {
    float j1_angle = steps[0] * TO_RADIANS / J1_STEPS_PER_DEG;
    float j2_angle = steps[1] * TO_RADIANS / J2_STEPS_PER_DEG;
    float j3_angle = steps[2] * TO_RADIANS / J3_STEPS_PER_DEG;

    Angles angles = IK3_6(Vector3{j1_angle, j2_angle, j3_angle});

    goToAngles(angles);
}
void Robot::moveWithPID(float dt) {
    Vector3 new_pos = PIDController.regulate(targetPos, currentPos, dt);
    move(new_pos);
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
    runLogic();

    if (program.running) {
        program.update(dt);

        if (PIDActive) {
            Vector3 regulation = PIDController.regulate(program.position, currentPos, dt);
            move(regulation);
        } else {
            goTo(program.position);
        }
    } else {
        runProgram(false);
    }
}


void Robot::move(float x, float y, float z) {
    move({x, y, z});
}

void Robot::move(Vector3 rel) {
    goTo(currentPos + rel);
}

void Robot::setTarget(Vector3 target) {
    targetPos = target;
}

void Robot::setPIDParameters(float kp, float ti, float td) {
    PIDController.params().set_params(kp, ti, td);
}

void Robot::setColors(Color color1, Color color2) {
    changeMeshColor(j0->mesh, color1);
    changeMeshColor(j1->mesh, color2);
    changeMeshColor(j2->mesh, color1);
    changeMeshColor(j3->mesh, color2);
    changeMeshColor(j4->mesh, color1);
    changeMeshColor(j5->mesh, color2);
    changeMeshColor(j6->mesh, color1);
    changeMeshColor(gripper->mesh, color2);
}

void Robot::runProgram(bool run) {
    program.running = run;
}

bool Robot::isRunning() {
    return program.running;
}

void Robot::teachPosition(Vector4 command) {
    program.add(command);
}

void Robot::teachPause(float time) {
    program.addPause(time);
}

void Robot::attachPallet(const std::shared_ptr<EuroPallet> &pallet_) {
    pallet = pallet_;

    restPos = pickPos + (pallet->cornerPos - pickPos) * 0.5f;
    restPos.z = pickPos.z + 100.0f;
    program.setRestPosition(restPos);
}

void Robot::attachConveyor(const std::shared_ptr<ConveyorBelt> &conveyor_) {
    conveyor = conveyor_;
    pickPos = conveyor->position.clone() + Vector3{0.0f, -100.0f, 196.0f};
    program.generateSequence(pickPos, false);

    if (pallet) {
        restPos = pickPos + (pallet->cornerPos - pickPos) * 0.5f;
        restPos.z = pickPos.z + 100.0f;
        program.setRestPosition(restPos);
    }

}

void Robot::pickUp() {
    isHolding = true;
    item = conveyor->items.getTailValue();
    Vector3 drop_position = pallet->nextPosition(item);
    drop_position.z += item.size.z * 0.5f;
    program.generateSequence(drop_position, true);
    updateItemPosition();
    conveyor->removeItem();
}

void Robot::drop() {
    isHolding = false;
    item.mesh->position = pallet->nextPosition(item);
    pallet->addItem(item);
    *money += Box::value;
    if (pallet->itemCount == 32) {
        pallet->clear(scene);
        *money += pallet->getValue();
    }

}

Program Robot::getProgram() {
    return program;
}

Vector3 Robot::getPos() {
    return currentPos;
}

void Robot::updateItemPosition() {

    Vector3 new_pos = currentPos;
    new_pos.z -= item.size.z * 0.5f;

    item.mesh->position = new_pos;
}

void Robot::runLogic() {
    if (conveyor->running && !program.running)
        runProgram(true);

    if (program.running) {
        if (program.isHolding && !isHolding) {
            pickUp();
        } else if (!program.isHolding && isHolding) {
            drop();
        }

        if (isHolding)
            updateItemPosition();
    }
}

void Robot::upgradeSpeed(float rate) {
    upgradeCost *= upgradeCostMultiplier;
    speedMultiplier *= rate;
    program.setR(1.0f / speedMultiplier);
}
