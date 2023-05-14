#ifndef ROBOTCONTROLLER_GOLDBLOCK_HPP
#define ROBOTCONTROLLER_ROBOTCONTROLLER_GOLDBLOCK_HPP_HPP
#include "Item.hpp"

class GoldBlock : public Item {

public:
    inline static float value = 10.0f;
    GoldBlock() : Item("bin/data/textures/gold_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };

};
#endif //ROBOTCONTROLLER_ROBOTCONTROLLER_GOLDBLOCK_HPP_HPP
