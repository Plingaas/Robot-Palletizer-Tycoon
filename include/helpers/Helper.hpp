//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_HELPER_H
#define ROBOTCONTROLLER_HELPER_H

#include "LinkedList.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<BufferGeometry> loadSTL(const std::string &path);

void changeMeshColor(std::shared_ptr<Mesh> old_mesh, Color new_color);

std::shared_ptr<Mesh>
meshFromSTL(const std::string &path, Color color = Color::white, Vector3 scaling = {1.0f, 1.0f, 1.0f});

//Vector4 v4_from_v3(const Vector3 &vector3, float w) {return {vector3.x, vector3.y, vector3.z, w};};

template<typename T>
[[maybe_unused]] void log(T input);

enum Axis {
    x, y, z
};
#endif //ROBOTCONTROLLER_HELPER_H
