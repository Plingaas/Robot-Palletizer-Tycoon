#ifndef ROBOTCONTROLLER_ITEMGENERATOR_H
#define ROBOTCONTROLLER_ITEMGENERATOR_H
#include "EmeraldBlock.hpp"
#include "DiamondBlock.hpp"
#include "GoldBlock.hpp"
#include "IronBlock.hpp"
#include "Box.hpp"
#include <cmath>

struct ItemGenerator {

    // Must add up to 100
    inline static const int emerald = 10;
    inline static const int diamond = 20;
    inline static const int gold = 30;
    inline static const int iron = 40;

    // Create int array to gather the
    inline static const std::array<int, 4> itemPercentages = {emerald, diamond, gold, iron};

    static std::shared_ptr<Item> generateRandomItem() {

        int number = math::randomInRange(1, 100);
        int p = 0;

        int n = 0;
        while (p < number) {
            p += itemPercentages[n++];
        }

        switch (n) {
            case 1: return std::make_shared<EmeraldBlock>();
            case 2: return std::make_shared<DiamondBlock>();
            case 3: return std::make_shared<GoldBlock>();
            case 4: return std::make_shared<IronBlock>();
            default: return std::make_shared<Box>(); // Should never happen
        }
    }
};

#endif //ROBOTCONTROLLER_ITEMGENERATOR_H
