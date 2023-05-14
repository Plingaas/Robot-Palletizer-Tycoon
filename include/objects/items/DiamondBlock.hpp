#ifndef ROBOTCONTROLLER_DIAMONDBLOCK_HPP
#define ROBOTCONTROLLER_DIAMONDBLOCK_HPP

#include "Item.hpp"

class DiamondBlock : public Item {

public:
    inline static float value = 30.0f;
    DiamondBlock() : Item("bin/data/textures/diamond_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };

};
#endif //ROBOTCONTROLLER_DIAMONDBLOCK_HPP
