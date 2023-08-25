#include "robot_arm/Robot.hpp"

#include "threepp/threepp.hpp"

using namespace AR2;

AR2::Robot::Robot() {

    Color color1 = Color::lightcoral;
    Color color2 = Color::lightblue;

    j0 = Joint::create(j0_geo, color1);
    j1 = Joint::create(j1_geo, color2, z, false, {0, 0, 87.12});
    j2 = Joint::create(j2_geo, color2, y, true, {64.2, 51.4, 82.65});
    j3 = Joint::create(j3_geo, color1, y, true, {305, -51.4, 0});
    j4 = Joint::create(j4_geo, color1, x, true, {222.63, 0, 0});
    j5 = Joint::create(j5_geo, color2, y, true);
    j6 = Joint::create(j6_geo, color2, x, true, {36.25, 0, 0});
    gripper = Joint::create(gripper_geo, color2, z, false, {64, 0, 0});

    j2_logo = Joint::create(j2_logo_geo, color1);
    j4_logo = Joint::create(j4_logo_geo, color2);

    // Attach logo
    j2->mesh->add(j2_logo->mesh);
    j4->mesh->add(j4_logo->mesh);

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
    Angles angles = IK(relative_pos, LOOKDOWN);

    goToAngles(angles);
    currentPos = pos;
}

void Robot::goToSteps(const std::array<int, 3> &steps) {
    float j1_angle = static_cast<float>(steps[0]) * TO_RADIANS / J1_STEPS_PER_DEG;
    float j2_angle = static_cast<float>(steps[1]) * TO_RADIANS / J2_STEPS_PER_DEG;
    float j3_angle = static_cast<float>(steps[2]) * TO_RADIANS / J3_STEPS_PER_DEG;

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
    changeMeshColor(j1->mesh, color1);
    changeMeshColor(j2->mesh, color2);
    changeMeshColor(j3->mesh, color2);
    changeMeshColor(j4->mesh, color2);
    changeMeshColor(j5->mesh, color1);
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
    drop_position.z += item->size.z * 0.5f;
    program.generateSequence(drop_position, true);
    updateItemPosition();
    conveyor->removeItem();
}

void Robot::drop() {
    isHolding = false;
    item->mesh->position = pallet->nextPosition(item);
    pallet->addItem(item);
    *money += item->getValue();
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
    new_pos.z -= item->size.z * 0.5f;

    item->mesh->position = new_pos;
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
    uSpeedCost *= upgradeCostMultiplier;
    speedMultiplier *= rate;
    program.setR(1.0f / speedMultiplier);
}