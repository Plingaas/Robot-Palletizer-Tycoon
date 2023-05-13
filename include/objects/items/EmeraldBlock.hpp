#ifndef ROBOTCONTROLLER_EmeraldBlock_HPP
#define ROBOTCONTROLLER_EmeraldBlock_HPP
#include "Item.hpp"

class EmeraldBlock : public Item {

public:
    inline static float value = 50.0f;

    EmeraldBlock() {
        auto material = MeshPhongMaterial::create();
        material->map = loadTexture("bin/data/textures/emerald_block.png");

        mesh = Mesh::create(geometry, material);
    };
    [[nodiscard]] float getValue() const override { return value; };

};
#endif //ROBOTCONTROLLER_EmeraldBlock_HPP
