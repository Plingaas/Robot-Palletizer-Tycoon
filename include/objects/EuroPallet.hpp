//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_EUROPALLET_HPP
#define ROBOTCONTROLLER_EUROPALLET_HPP

#include "items/Item.hpp"

class EuroPallet {
public:
    EuroPallet() {
        mesh = meshFromSTL("bin/data/models/euro_pallet.stl", Color::rosybrown);

    };

    std::shared_ptr<Mesh> mesh;
    Vector3 corner_pos;

    List<Item> items;
    int item_count = 0;

    void rotate(float degrees) const { mesh->rotateZ(math::degToRad(degrees)); }

    void setPosition(float x, float y, float z) { setPosition({x, y, z}); }

    void setPosition(Vector3 pos) {
        mesh->position = pos;
        corner_pos = pos.sub({360.0f, 120.0f, -43.2f});
    }

    void addItem(const Item &item) {
        items.insertAtTail(item);
        item_count++;
    }

    void clear(std::shared_ptr<Scene> &scene);

    [[nodiscard]] Vector3 nextPosition(const Item &item);

    [[nodiscard]] float getValue() const { return deliver_value * deliver_value_multiplier; }

    void upgradeDeliverValue(float rate) { deliver_value_multiplier *= rate; }

private:
    float deliver_value = 100.0f;
    float deliver_value_multiplier = 1.0f;
};


#endif //ROBOTCONTROLLER_EUROPALLET_HPP
