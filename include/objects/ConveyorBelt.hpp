//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_CONVEYORBELT_HPP
#define ROBOTCONTROLLER_CONVEYORBELT_HPP

#include "items/Box.hpp"
/**
 * @brief Represents a conveyor belt.
 *
 * This is a class that spawns items into the world
 * and move them along the belt so they can be picked
 * up by the robot arm to then be stacked on pallets.
 */
class ConveyorBelt {

public:

    // Meshes
    std::shared_ptr<Group> conveyor;
    std::shared_ptr<Mesh> leg_mesh;
    std::shared_ptr<Mesh> body_mesh;
    std::shared_ptr<Mesh> belt_mesh;

    std::shared_ptr<Scene> scene_;
    List<Item> items;

    // Position for conveyor and start offset for item start position.
    Vector3 position{};
    Vector3 start_offset{};

    // Spawn rate and belt speed
    float spawn_rate = 1.0f;
    float speed = 250.0f;

    // Whether belt is running or not.
    bool running = false;

    float time_since_last_spawn = spawn_rate;

    /**
     * @brief The constructor for the conveyor belt.
     *
     * @param leg_height How tall the legs should be.
     * @param pos Where to place the conveyor.
     */
    explicit ConveyorBelt(float leg_height, Vector3 pos = {0.0f, 0.0f, 0.0f});

    /**
     * @brief Updates everything related to the conveyor belt.
     *
     * This function takes care of moving the items on the belt
     * and also stop the belt when an item has moved the end position.
     * It also spawns new items when the accumulated time exceeds the
     * spawn_rate time.
     *
     * @param dt How much time the last frame took to complete in seconds.
     *
     * @return void.
     *
     */
    void update(float dt);

    /**
     * @brief Gets the z-value of the belt surface.
     *
     * @return A float with the z-value.
     *
     * @note This function is a nodiscard function and the return value
     * should not be disregarded but be taken care of appropriately.
     */
    [[nodiscard]] float getSurfaceHeight() const {
        return conveyor->position.z + 100;
    }

    /**
     * @brief Sets the color of the legs.
     *
     * This function changes the color of the legs in order
     * to have functionality for buying new colors in a shop.
     *
     * @param color The new color.
     * @return void.
     */
    void setLegColor(Color color) const { changeMeshColor(leg_mesh, color); }

    /**
     * @brief Sets the color of the body.
     *
     * This function changes the color of the body in order
     * to have functionality for buying new colors in a shop.
     *
     * @param color The new color.
     * @return void.
     */
    void setBodyColor(Color color) const { changeMeshColor(body_mesh, color); }

    /**
     * @brief Sets the color of the belt.
     *
     * This function changes the color of the belt in order
     * to have functionality for buying new colors in a shop.
     *
     * @param color The new color.
     * @return void.
     */
    void setBeltColor(Color color) const { changeMeshColor(belt_mesh, color); }

    /**
     * @brief Sets the position of the conveyor.
     *
     * The position of the conveyor is located at the center of the
     * end of the belt on the side where items stop.
     *
     * @param position_ The position to be set.
     * @return void.
     */
    void setPosition(Vector3 position_) {
        conveyor->position = position_;
        position = position_;
    }

    /**
     * @brief Rotates the conveyor clockwise.
     *
     * @param degrees The amount of degrees to rotate.
     * @return void.
     */
    void rotate(float degrees) const { conveyor->rotateZ(math::degToRad(degrees)); }

    /**
     * @brief Adds an item to the belt
     *
     * Adds a new item to the head of the list. And
     * adds the mesh to the scene.
     *
     * @return void.
     */
    void addItem();

    /**
     * @brief Removes the last item in the items list.
     *
     * Gets rid of the last item in the list containing
     * all the items on the belt.
     *
     * @return A float with the value.
     *
     */
    void removeItem();

    /**
     * @brief Upgrades the item spawn rate
     *
     * Upgrades the item spawn rate by decreasing
     * the time it takes to spawn a new item by a multiplier.
     *
     * @param multiplier The multitiplier to decrease the time by.
     * @return void.
     */
    void upgradeSpawnRate(float multiplier) { spawn_rate /= multiplier; }

    /**
     * @brief Upgrades the belt speed
     *
     * Upgrades the belt speed so that items move
     * faster along the belt. It is increased by a multiplier.
     *
     * @param multiplier The multitiplier to incease the speed by.
     * @return void.
     */
    void upgradeSpeed(float multiplier) { speed *= multiplier; }

private:

    float leg_height = 200.0f;
    unsigned int item_count = items.length();

};


#endif //ROBOTCONTROLLER_CONVEYORBELT_HPP
