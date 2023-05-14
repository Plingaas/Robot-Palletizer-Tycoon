#ifndef ROBOTCONTROLLER_IRONBLOCK_HPP
#define ROBOTCONTROLLER_IRONBLOCK_HPP
#include "Item.hpp"

class IronBlock : public Item {

public:
    inline static float value = 5.0f;
    IronBlock() : Item("bin/data/textures/iron_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };
};
#endif //ROBOTCONTROLLER_IRONBLOCK_HPP
