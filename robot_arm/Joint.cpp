//
// Created by peter on 2/20/2023.
//

#include "Joint.h"

using namespace AR2;


Joint::Joint(std::shared_ptr<BufferGeometry> &geometry, Color color)
{

    auto material = MeshPhongMaterial::create();
    material->color = color;

    mesh = Mesh::create(geometry, material);
};

void Joint::set_rotation_axis(Axis axis)
{
    rotation_axis = axis;
};

void Joint::set_rotation(Vector3 rot)
{
    mesh->rotation.set(rot.x, rot.y, rot.z);
};

void Joint::set_position(Vector3 pos)
{
    mesh->position.set(pos.x, pos.y, pos.z);

};

void Joint::go_to(float rad) {

    if (reverse_rotation)
        rad = -rad;

    // Set rotation
    switch (rotation_axis)
    {
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

void Joint::set_reverse_rotation(bool reverse)
{
    reverse_rotation = reverse;
}
