#include "robot_arm/Joint.hpp"

using namespace AR2;

Joint::Joint(std::shared_ptr<BufferGeometry> &geometry,
             Color color,
             Axis rotationAxis,
             bool reverseRotation,
             Vector3 position) {

    auto material = MeshPhongMaterial::create();
    material->color = color;

    mesh = Mesh::create(geometry, material);
    mesh->castShadow = true;
    setRotationAxis(rotationAxis);
    setReverseRotation(reverseRotation);
    setPosition(position);
};

void Joint::setRotationAxis(Axis axis) {
    rotationAxis = axis;
};

void Joint::setRotation(Vector3 rot) const {
    mesh->rotation.set(rot.x, rot.y, rot.z);
};

void Joint::setPosition(Vector3 pos) const {
    mesh->position.set(pos.x, pos.y, pos.z);

};

void Joint::goTo(float rad) {

    if (reverseRotation)
        rad = -rad;

    // Set rotation
    switch (rotationAxis) {
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
    reverseRotation = reverse;
}
