//
// Created by peter on 3/29/2023.
//

#ifndef ROBOTCONTROLLER_PROGRAM_HPP
#define ROBOTCONTROLLER_PROGRAM_HPP

#include "threepp/threepp.hpp"
#include "objects/items/Box.hpp"

using namespace threepp;

class Program {

public:

    float r = 0.7f;
    std::vector<Vector4> program = {{0.0f,    -350.0f, 200.0f, 1.0f * r},
                                    {300.0f,  -100.0f, 146.0f, 1.0f * r},
                                    {300.0f,  -100.0f, 146.0f, 0.25f * r},
                                    {300.0f,  -100.0f, 96.0f,  0.5f * r},
                                    {300.0f,  -100.0f, 96.0f,  0.25f * r},
                                    {300.0f,  -100.0f, 146.0f, 1.0f * r},
                                    {300.0f,  -100.0f, 146.0f, 0.25f * r},
                                    {0.0f,    -350.0f, 200.0f, 1.0f * r},
                                    {-360.0f, -420.0f, -47.8f, 1.0f * r},
                                    {-360.0f, -420.0f, -47.8f, 0.25f * r},
                                    {-360.0f, -420.0f, -97.8f, 0.5f * r},
                                    {-360.0f, -420.0f, -97.8f, 0.25f * r},
                                    {-360.0f, -420.0f, -47.8f, 1.0f * r},
                                    {-360.0f, -420.0f, -47.8f, 0.25f * r}};

    float t = 0.0f; // lerp variable 0 -> 1
    Vector3 position{0, 0, 0};
    unsigned int index = 0;
    unsigned int commands = program.size();
    bool repeat = false;
    bool run = false;
    bool pause = false;
    unsigned int pick_index = 4;
    unsigned int drop_index = 11;
    bool is_holding = false;

    void generateSequence(Vector3 pos, bool drop, float z_offset = 50.0f);

    void setRestPosition(Vector3 pos, float w = 1.0f) {
        program[0] = {pos.x, pos.y, pos.z, w * r};
        program[7] = {pos.x, pos.y, pos.z, w * r};
    }


    void removeAll() { program = std::vector<Vector4>{}; };

    void update(float dt);

    void setProgram(const std::vector<Vector4> &program_);

    Vector4 getCurrent() { return program.at(index); };

    Vector4 getNext() {
        if (index == commands - 1) return program.front();
        else return program.at(index + 1);
    };

    void addPause(float time);

    void add(Vector4 command, int n = -1);

    void remove(int n);

    void setR(float new_r);

private:
    Vector3 extractPosition(Vector4 command) { return {command.x, command.y, command.z}; };
};


#endif //ROBOTCONTROLLER_PROGRAM_HPP
