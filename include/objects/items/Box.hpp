//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_BOX_HPP
#define ROBOTCONTROLLER_BOX_HPP

#include "Item.hpp"

using namespace threepp;

struct Box : Item {

public:
    explicit Box(Color color_ = Color::white);

    inline static float value = 1.0f;

    float getValue() const override { return value; }
};


#endif //ROBOTCONTROLLER_BOX_HPP
