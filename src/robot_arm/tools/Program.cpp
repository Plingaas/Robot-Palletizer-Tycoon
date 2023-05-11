//
// Created by peter on 3/29/2023.
//

#include "robot_arm/tools/Program.hpp"

void Program::generateSequence(Vector3 pos, bool drop, float z_offset) {
    std::vector<Vector4> sequence{};

    pos.z += z_offset;
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 1.0f * r});
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 0.25f * r});
    pos.z -= z_offset;
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 0.5f * r});
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 0.25f * r});
    pos.z += z_offset;
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 0.5f * r});
    sequence.emplace_back(Vector4{pos.x, pos.y, pos.z, 0.25f * r});

    int startIndex = 1 + drop * (6 + 1);
    for (int i = 0; i < 6; i++) {
        program[startIndex + i] = sequence[i];
    }
}

void Program::update(float dt) {
    if (!commands || !run || pause)
        return;

    t += dt / getNext().w;
    if (t > 1.0f) {
        t -= 1.0f;
        if (index == commands - 1) {

            index = 0;
            if (!repeat)
                run = false;
        } else {
            index++;
            if (index == pick_index)
                is_holding = true;
            if (index == drop_index)
                is_holding = false;
        }
    }

    Vector4 current = getCurrent();
    Vector4 next = getNext();

    // Linear interoplation between points;
    position = extractPosition(current) + (extractPosition(next) - extractPosition(current)) * t;
}

void Program::setProgram(const std::vector<Vector4> &program_) {
    program = program_;
    commands = program.size();
}

void Program::addPause(float time) {
    if (program.empty())
        return;

    Vector4 command = program.back();
    command[3] = time;
    add(command);
}

void Program::add(Vector4 command, int n) {
    if (n != -1) {
        program.insert(program.begin() + n, command);
    } else {
        program.emplace_back(command);
    }
    commands++;
}

void Program::remove(int n) {
    program.erase(program.begin() + n);
    index = 0;
    t = 0;
    commands--;
}

void Program::setR(float new_r) {
    for (Vector4 &v: program) {
        v.w *= (new_r / r);
    }

    r = new_r;
};