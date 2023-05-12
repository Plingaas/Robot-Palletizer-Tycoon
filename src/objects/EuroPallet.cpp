//
// Created by peter on 3/30/2023.
//

#include "objects/EuroPallet.hpp"

Vector3 EuroPallet::nextPosition(const Item &item) {
    Vector3 offset = {item.size.x, item.size.y, item.size.z};
    offset.multiplyScalar(0.5f);

    int z_index = (int) (itemCount / 8);
    int plane_index = (itemCount) % 8;

    offset.z += item.size.z * ((float) z_index);

    if (plane_index <= 3)
        offset.add({item.size.x * ((float) (plane_index)), 0.0f, 0.0f});
    else
        offset.add({item.size.x * ((float) (plane_index - 4)), item.size.y, 0.0f});

    Vector3 position = cornerPos + offset;

    return position;
}

void EuroPallet::clear(std::shared_ptr<Scene> &scene) {
    while (itemCount > 0) {
        scene->remove(items.getTailValue().mesh);
        items.deleteTail();
        itemCount--;
    }
}
