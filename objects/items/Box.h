//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_BOX_H
#define ROBOTCONTROLLER_BOX_H
#include "../../helpers/Helper.h"
#include "Item.h"

using namespace threepp;

struct Box : Item {

public:
    explicit Box(Color color_ = Color::white);
    inline static float value = 1.0f;

    float get_value() const override {return value;}
};


#endif //ROBOTCONTROLLER_BOX_H
