#ifndef ROBOTCONTROLLER_DIAMONDBLOCK_HPP
#define ROBOTCONTROLLER_DIAMONDBLOCK_HPP

#include "Item.hpp"

class DiamondBlock : public Item {

public:
    inline static float value = 30.0f;

    DiamondBlock() {
        auto material = MeshPhongMaterial::create();
        material->map = loadTexture("bin/data/textures/diamond_block.png");

        mesh = Mesh::create(geometry, material);
    };
    [[nodiscard]] float getValue() const override { return value; };

};
#endif //ROBOTCONTROLLER_DIAMONDBLOCK_HPP
