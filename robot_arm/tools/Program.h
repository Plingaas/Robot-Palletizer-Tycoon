//
// Created by peter on 3/29/2023.
//

#ifndef ROBOTCONTROLLER_PROGRAM_H
#define ROBOTCONTROLLER_PROGRAM_H

#include "threepp/threepp.hpp"
#include <cstdio>
#include "../../objects/items/Box.h"

using namespace threepp;

class Program {

public:

    float r = 0.02f;
    std::vector<Vector4> program
    {
            {0.0f, -350.0f, 200.0f, 1.0f*r},
            {300.0f, -100.0f, 146.0f, 1.0f*r},
            {300.0f, -100.0f, 146.0f, 0.25f*r},
            {300.0f, -100.0f, 96.0f, 0.5f*r},
            {300.0f, -100.0f, 96.0f, 0.25f*r},
            {300.0f, -100.0f, 146.0f, 1.0f*r},
            {300.0f, -100.0f, 146.0f, 0.25f*r},
            {0.0f, -350.0f, 200.0f, 1.0f*r},
            {-360.0f, -420.0f, -47.8f, 1.0f*r},
            {-360.0f, -420.0f, -47.8f, 0.25f*r},
            {-360.0f, -420.0f, -97.8f, 0.5f*r},
            {-360.0f, -420.0f, -97.8f, 0.25f*r},
            {-360.0f, -420.0f, -47.8f, 1.0f*r},
            {-360.0f, -420.0f, -47.8f, 0.25f*r}
    };

    float t = 0.0f; // lerp variable 0 -> 1
    Vector3 position{0, 0, 0};
    unsigned int index = 0;
    unsigned int commands = program.size();
    bool repeat = false;
    bool run = false;
    bool pause = false;

    void replace_drop_sequence(Vector3 drop_position)
    {
        std::vector<Vector4> sequence{};

        drop_position.z += 50.0f;
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,1.0f*r});
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,0.25f*r});
        drop_position.z -= 50.0f;
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,0.5f*r});
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,0.25f*r});
        drop_position.z += 50.0f;
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,1.0f*r});
        sequence.emplace_back(Vector4{drop_position.x,drop_position.y, drop_position.z,0.25f*r});

        for (int i = 8; i < program.size(); i++)
        {
            program[i] = sequence[i-8];
        }
    }

    unsigned int pick_index = 4;
    unsigned int drop_index = 11;
    bool is_holding = false;

    void remove_all() {
        program = std::vector<Vector4>{};
    }

    void update(float dt) {
        if (!commands || !run || pause)
            return;

        t += dt/get_next().w;
        if (t > 1.0f) {
            t -= 1.0f;
            if (index == commands-1)
            {

                index = 0;
                if (!repeat)
                    run = false;
            }
            else
            {
                index++;
                if (index == pick_index)
                    is_holding = true;
                if (index == drop_index)
                    is_holding = false;
            }
        }

        Vector4 current = get_current();
        Vector4 next = get_next();

        // Linear interoplation between points;
        position = extract_position(current) + (extract_position(next) - extract_position(current))*t;
    }

    void set_program(const std::vector<Vector4> &program_)
    {
        program = program_;
        commands = program.size();
    }

    Vector4 get_current() {
        return program.at(index);
    }


    Vector4 get_next() {
        if (index == commands-1) return program.front();
        else return program.at(index + 1);
    }

    void add_pause(float time) {
        if (program.empty())
            return;

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
