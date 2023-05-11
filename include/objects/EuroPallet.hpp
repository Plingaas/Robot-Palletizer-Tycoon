//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_EUROPALLET_HPP
#define ROBOTCONTROLLER_EUROPALLET_HPP

#include "items/Item.hpp"

/**
 * @brief Represents a pallet
 *
 * This class is a pallet that holds items that
 * the robot arm can stack on.
 */
class EuroPallet {
public:

    std::shared_ptr<Mesh> mesh;
    Vector3 corner_pos;

    List<Item> items;
    int item_count = 0;

    /**
     * @brief The EuroPallet constructor
     *
     * Sets the mesh to be an europallet by loading an STL file.
     * Also sets the color to rosybrown
     *
     */
    EuroPallet() {
        mesh = meshFromSTL("bin/data/models/euro_pallet.stl", Color::rosybrown);

    };

    /**
     * @brief Rotates the pallet clockwise.
     *
     * @param degrees The amount of degrees to rotate.
     * @return void.
     */
    void rotate(float degrees) const { mesh->rotateZ(math::degToRad(degrees)); }

    /**
     * @brief Sets the position of the pallet.
     *
     * The position of the pallet is located at the center.
     *
     * @param x The new x position.
     * @param y The new y position.
     * @param z The new z position.
     * @return void.
     */
    void setPosition(float x, float y, float z) { setPosition({x, y, z}); }

    /**
     * @brief Sets the position of the pallet.
     *
     * The position of the pallet is located at the center.
     *
     * @param pos The position to be set.
     * @return void.
     */
    void setPosition(Vector3 pos) {
        mesh->position = pos;
        corner_pos = pos.sub({360.0f, 120.0f, -43.2f});
    }

    /**
     * @brief Adds an item to the pallet
     *
     * Adds a new item to the tail of the list and
     * increases the item count by 1.
     *
     * @param item A const reference to the item being added.
     * @return void.
     */
    void addItem(const Item &item) {
        items.insertAtTail(item);
        item_count++;
    }

    /**
     * @brief Clears the pallet
     *
     * Removes all the items from the item list and removes
     * all the items' meshes from the scene. Also resets the
     * item count.
     *
     * @param scene A reference to the scene to delete items from.
     * @return void.
     */
    void clear(std::shared_ptr<Scene> &scene);

    /**
     * @brief Gets the position to place an item at.
     *
     * This function calculates where to put the items on the pallet
     * so that they dont intersect with other items.
     *
     * @param item A const reference to the item to be placed.
     * @return A Vector3 with the position to place at.
     */
    [[nodiscard]] Vector3 nextPosition(const Item &item);

    /**
     * @brief Gets the value of the full pallet reward.
     *
     * When a pallet is fully stacked with 32 items you get
     * a cash reward. This function calculates that value with
     * upgrades considered.
     *
     * @return Returns a float with the reward value.
     */
    [[nodiscard]] float getValue() const { return deliver_value * deliver_value_multiplier; }


    /**
     * @brief Upgrades the cash reward.
     *
     * Upgrades the cash reward for a fully stacked pallet
     * by a multiplier.
     *
     * @param multiplier The multiplier to upgrade with.
     * @return void.
     */
    void upgradeDeliverValue(float multiplier) { deliver_value_multiplier *= multiplier; }

private:

    /**
     * @brief The cash reward for a fully stacked pallet.
     */
    float deliver_value = 100.0f;

    /**
     * @brief The multiplier for the cash reward.
     *
     * When a fully stacked pallet is delivered
     * you get a cash reward that is multiplied by
     * this multiplier.
     */
    float deliver_value_multiplier = 1.0f;
};


#endif //ROBOTCONTROLLER_EUROPALLET_HPP
