//
// Created by peter on 3/29/2023.
//

#ifndef ROBOTCONTROLLER_PROGRAM_H
#define ROBOTCONTROLLER_PROGRAM_H

#include "threepp/threepp.hpp"
#include <cstdio>

using namespace threepp;

class Program {

public:
    std::vector<Vector4> program
    {
            {1000.0f, 200.0f, -200.0f, 1.0f},
            {1000.0f, 200.0f, 200.0f, 2.1f},
            {1000.0f, 800.0f, 200.0f, 1.7f},
            {1000.0f, 800.0f, -200.0f, 1.5f}

    };

    // lerp value from 0 to 1;
    float t = 0.0f;
    Vector3 position{0, 0, 0};
    int index = 0;
    int commands = program.size();

    void remove_all() {
        program = std::vector<Vector4>{};
    }

    void update(float dt) {
        if (!commands)
            return;

        t += dt/get_current().w;
        if (t > 1.0f) {
            t -= 1.0f;
            if (index == commands-1) index = 0;
            else index++;
        }

        Vector4 current = get_current();
        Vector4 next = get_next();

        // Linear interoplation between points;
        position = extract_position(current) + (extract_position(next) - extract_position(current))*t;

    }

    Vector4 get_current() {
        return program.at(index);
    }
    // Gets next command
    Vector4 get_next() {
        if (index == program.size()-1) return program.at(0);
        else return program.at(index + 1);
    }

    void add_pause(float time) {
        Vector4 command = program.back();
        command[3] = time;
        add(command);
    }

    void add(Vector4 command, int n = -1) {
        if (n != -1)
        {
            program.insert(program.begin() + n, command);
        }
        else
        {
            program.emplace_back(command);
        }
        commands++;
    }

    void remove(int n) {
        program.erase(program.begin() + n);
        index = 0;
        t = 0;
        commands--;
    }

private:
    Vector3 extract_position(Vector4 command) {
        return {command.x, command.y, command.z};
    }
};


#endif //ROBOTCONTROLLER_PROGRAM_H
