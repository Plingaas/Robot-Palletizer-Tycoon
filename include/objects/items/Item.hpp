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

protected:
    /**
     * @brief How far it should move on the belt.
     */
    float maxMove = 900.0f;

    /**
     * @brief How far it has moved since it was spawned.
     */
    float hasMoved = 0.0f;

public:

    /**
     * @brief The size of the item.
     */
    inline static Vector3 size = {90.0f, 120.0f, 96.0f};

    /**
     * @brief The item's geometry
     *
     *  All items should have the same geometry
     *  in order to make the stacking on pallets
     *  and easier. It also makes it easier to
     *  know when a pallet is full because pallets
     *  will always look the same.
     */
    inline static std::shared_ptr<BufferGeometry> geometry = BoxGeometry::create(size.x, size.y, size.z);

    /**
     * @brief The item's mesh.
     */
    std::shared_ptr<Mesh> mesh;

    /**
     * @brief
     * @param path Path to a .png texture file.
     * @param _receiveShadow If the item should receive shadows.
     * @param _castShadow If the item should cast shadows.
     *
     * @note Using receiveShadow as well as castShadow can cause artifacts.
     */
    explicit Item(const std::string &path, bool _receiveShadow = true, bool _castShadow = true) {

        auto material = MeshPhongMaterial::create();
        if (!path.empty()) {
            material->map = loadTexture(path);
        } else {
            material->color = Color::white;
        }
        mesh = Mesh::create(geometry, material);
        mesh->castShadow = _castShadow;
        mesh->receiveShadow = _receiveShadow;
    }

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
    [[nodiscard]] virtual float getValue() const { return 0.0f; };

};


#endif //ROBOTCONTROLLER_ITEM_HPP
