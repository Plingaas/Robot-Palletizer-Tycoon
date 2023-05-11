//
// Created by peter on 2/20/2023.
//

#include "robot_arm/Joint.hpp"

using namespace AR2;


Joint::Joint(std::shared_ptr<BufferGeometry> &geometry, Color color) {

    auto material = MeshPhongMaterial::create();
    material->color = color;

    mesh = Mesh::create(geometry, material);
};

void Joint::setRotationAxis(Axis axis) {
    rotation_axis = axis;
};

void Joint::setRotation(Vector3 rot) const {
    mesh->rotation.set(rot.x, rot.y, rot.z);
};

void Joint::setPosition(Vector3 pos) const {
    mesh->position.set(pos.x, pos.y, pos.z);

};

void Joint::goTo(float rad) {

    if (reverse_rotation)
        rad = -rad;

    // Set rotation
    switch (rotation_axis) {
        case x:
            mesh->rotation.x = rad;
            break;
        case y:
            mesh->rotation.y = rad;
            break;
        case z:
            mesh->rotation.z = rad;
            break;
    }
}

void Joint::setReverseRotation(bool reverse) {
    reverse_rotation = reverse;
}
