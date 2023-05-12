//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_ITEM_HPP
#define ROBOTCONTROLLER_ITEM_HPP

#include "helpers/Helper.hpp"

/**
 * @brief Represents an item
 *
 * This struct is a blueprint for all items
 * to be created later.
 */
struct Item {

    /**
     * @brief The item's mesh.
     */
    std::shared_ptr<Mesh> mesh;

    /**
     * @brief The size of the item.
     */
    Vector3 size;

    /**
     * @brief How far it should move on the belt.
     */
    float maxMove = 900.0f;

    /**
     * @brief How far it has moved since it was spawned.
     */
    float hasMoved = 0.0f;

    /**
     * @brief Sets the color of the item.
     *
     * Uses the helper function changeMeshColor to set
     * the color of the mesh.
     *
     * @param color The new color.
     * @return void.
     *
     */
    void setColor(Color color) const {
        changeMeshColor(mesh, color);
    }


    /**
     * @brief Moves the item along an axis
     *
     * @param displacement How far to move.
     * @param axis Which axis to move along. 0 = x, 1 = y, 2 = z.
     * @return void.
     *
     */
    void move(float displacement, int axis) {
        if (axis < 0 || axis > 2)
            return;
        mesh->position[axis] += displacement;
        hasMoved += displacement;
    }

    /**
     * @brief Checks remaining distance to move.
     *
     * Checks how far the item is from reaching the endpoint
     * of the conveyor belt that it is positioned on.
     *
     * @return A float with the value of the remaining distance.
     *
     */
    float toMove() {
        return maxMove - hasMoved;
    }

    /**
     * @brief Gets the value of the item.
     *
     * Items have a value which is how much money you get
     * for every time the robot stacks it onto a pallet.
     * This function returns that value.
     *
     * @return A float with the value.
     *
     */
    virtual float getValue() const { return 0.0f; };

    // Destructor
    ~Item() = default;;
};


#endif //ROBOTCONTROLLER_ITEM_HPP
