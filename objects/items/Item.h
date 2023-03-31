//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_ITEM_H
#define ROBOTCONTROLLER_ITEM_H
#include "../../helpers/Helper.h"

struct Item {

    std::shared_ptr<Mesh> mesh;
    Vector3 size;
    float max_move = 900.0f;
    float has_moved = 0.0f;

    void set_color(Color color) const
    {
        change_mesh_color(mesh, color);
    }

    void move(float displacement, int axis)
    {
        mesh->position[axis] += displacement;
        has_moved += displacement;
    }

    float to_move()
    {
        return max_move - has_moved;
    }
};


#endif //ROBOTCONTROLLER_ITEM_H
