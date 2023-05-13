#ifndef ROBOTCONTROLLER_GOLDBLOCK_HPP
#define ROBOTCONTROLLER_ROBOTCONTROLLER_GOLDBLOCK_HPP_HPP
#include "Item.hpp"

class GoldBlock : public Item {

public:
    inline static float value = 10.0f;

    GoldBlock() {
        auto material = MeshPhongMaterial::create();
        material->map = loadTexture("bin/data/textures/gold_block.png");

        mesh = Mesh::create(geometry, material);
    };
    [[nodiscard]] float getValue() const override { return value; };

};
#endif //ROBOTCONTROLLER_ROBOTCONTROLLER_GOLDBLOCK_HPP_HPP
