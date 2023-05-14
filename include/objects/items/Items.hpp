//
// Created by peter on 5/14/2023.
//

#ifndef ROBOTCONTROLLER_ITEMS_H
#define ROBOTCONTROLLER_ITEMS_H

#include "Item.hpp"

/**
 * @brief Represents a box.
 *
 * This is a derived structure of the Item struct.
 * It's implemented to work as the default item.
 */
struct Box : public Item {

public:

    /**
     * @brief The value of the box when stacked.
     */
    inline static float value = 1.0f;
    inline static float percent = 0.1;

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
    [[nodiscard]] float getValue() const override { return value; }
};

struct EmeraldBlock : public Item {
public:
    inline static float value = 50.0f;
    inline static float percent = 0.1;
    EmeraldBlock() : Item("bin/data/textures/emerald_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };
};

struct DiamondBlock : public Item {
public:
    inline static float value = 30.0f;
    inline static float percent = 0.2;
    DiamondBlock() : Item("bin/data/textures/diamond_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };
};

struct GoldBlock : public Item {
public:
    inline static float value = 10.0f;
    inline static float percent = 0.3;
    GoldBlock() : Item("bin/data/textures/gold_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };
};

struct IronBlock : public Item {
public:
    inline static float value = 5.0f;
    inline static float percent = 0.4;
    IronBlock() : Item("bin/data/textures/iron_block.png"){};
    [[nodiscard]] float getValue() const override { return value; };
};

struct ItemGenerator {

    // Array must be in order from rarest to most common.
    inline static const std::array<float, 4> itemPercentages = {
            EmeraldBlock::percent,
            DiamondBlock::percent,
            GoldBlock::percent,
            IronBlock::percent
    };

    /**
     * @brief Creates a new item.
     *
     * By getting all the percentages from itemPercentages, this function
     * will take a random number from 1 to 100 and compare it with a variable
     * that starts at 0. While the variable is less than the random number, it will
     * go through the rarity list and add the rarities. This leads to the correct
     * distribution of items.
     *
     * @return Returns a shared_ptr to a random subclass of Item.
     */
    static std::shared_ptr<Item> generateRandomItem() {

        float number = math::randomInRange(0.01f, 1.0f);
        float p = 0.0f;
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
#endif //ROBOTCONTROLLER_ITEMS_H
