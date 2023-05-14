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
    inline static std::shared_ptr<BufferGeometry> geometry = loadSTL("bin/data/models/euro_pallet.stl");

    std::shared_ptr<Mesh> mesh;
    Vector3 cornerPos;

    List<std::shared_ptr<Item>> items;
    int itemCount = 0;

    float uPalletRewardCost = 5.0f;

    /**
     * @brief The EuroPallet constructor
     *
     * Sets the mesh to be an europallet by loading an STL file.
     * Also sets the color to rosybrown
     *
     */
    explicit EuroPallet(Vector3 pos = {0.0f, 0.0f, 0.0f}) {

        auto material = MeshPhongMaterial::create();
        material->color = 0xF5DCA6;
        mesh = Mesh::create(geometry, material);
        mesh->receiveShadow = true;
        mesh->castShadow = true;
        setPosition(pos);
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
        cornerPos = pos.sub({360.0f, 120.0f, -43.2f});
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
    void addItem(const std::shared_ptr<Item> &item) {
        items.insertAtTail(item);
        itemCount++;
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
    [[nodiscard]] Vector3 nextPosition(const std::shared_ptr<Item> &item) const;

    /**
     * @brief Gets the value of the full pallet reward.
     *
     * When a pallet is fully stacked with 32 items you get
     * a cash reward. This function calculates that value with
     * upgrades considered.
     *
     * @return Returns a float with the reward value.
     */
    [[nodiscard]] float getValue() const { return palletReward * palletRewardMultiplier; }


    /**
     * @brief Upgrades the cash reward.
     *
     * Upgrades the cash reward for a fully stacked pallet
     * by a multiplier.
     *
     * @param multiplier The multiplier to upgrade with.
     * @return void.
     */
    void upgradePalletReward(float multiplier) {
        palletRewardMultiplier *= multiplier;
        uPalletRewardCost *= upgradeCostMultiplier;
    }

private:

    /**
     * @brief The cash reward for a fully stacked pallet.
     */
    float palletReward = 100.0f;

    /**
     * @brief The multiplier for the cash reward.
     *
     * When a fully stacked pallet is delivered
     * you get a cash reward that is multiplied by
     * this multiplier.
     */
    float palletRewardMultiplier = 1.0f;
};


#endif //ROBOTCONTROLLER_EUROPALLET_HPP
