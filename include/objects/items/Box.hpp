#ifndef ROBOTCONTROLLER_BOX_HPP
#define ROBOTCONTROLLER_BOX_HPP

#include "Item.hpp"

using namespace threepp;

/**
 * @brief Represents an box.
 *
 * This is a derived structure of the Item struct.
 * It has a cube shape and a value of $1 every time
 * its stacked onto a pallet.
 */
struct Box : public Item {

public:

    /**
     * @brief The value of the box when stacked.
     */
    inline static float value = 5.0f;

    /**
     * @brief The box's constructor
     *
     * @param color The color of the box.
     */
    explicit Box(const std::string &path = "", bool receiveShadow = false, bool castShadow = false) : Item(path, receiveShadow, castShadow) {
        auto color = math::randomInRange(0x555555, 0xffffff);
        auto mat = MeshPhongMaterial::create();
        mat->color = color;

        mesh = Mesh::create(geometry, mat);
        mesh->castShadow = true;
        mesh->receiveShadow = true;
    };

    /**
     * @brief Gets the value of the box.
     *
     * Boxes have a value which is how much money you get
     * for every time the robot stacks it onto a pallet.
     * This function returns that value.
     *
     * @return A float with the value.
     *
     */
    float getValue() const override { return value; }
};


#endif //ROBOTCONTROLLER_BOX_HPP
