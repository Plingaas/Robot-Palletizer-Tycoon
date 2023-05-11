//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_ITEM_HPP
#define ROBOTCONTROLLER_ITEM_HPP

#include "helpers/Helper.hpp"

struct Item {

    std::shared_ptr<Mesh> mesh;
    Vector3 size;
    float max_move = 900.0f;
    float has_moved = 0.0f;

    void setColor(Color color) const {
        changeMeshColor(mesh, color);
    }

    void move(float displacement, int axis) {
        mesh->position[axis] += displacement;
        has_moved += displacement;
    }

    float toMove() {
        return max_move - has_moved;
    }

    virtual float getValue() const { return 0.0f; };

    virtual ~Item() {};
};


#endif //ROBOTCONTROLLER_ITEM_HPP
