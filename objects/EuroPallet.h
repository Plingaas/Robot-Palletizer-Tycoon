//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_EUROPALLET_H
#define ROBOTCONTROLLER_EUROPALLET_H

#include "../helpers/Helper.h"
#include "items/Item.h"

struct EuroPallet {

    EuroPallet()
    {
        mesh = mesh_from_stl("bin/data/models/euro_pallet.stl", Color::rosybrown);
    };

    std::shared_ptr<Mesh> mesh;
    Vector3 corner_pos;

    List<Item> items;
    int item_count = 0;

    void rotate(float degrees) const
    {
        mesh->rotateZ(math::degToRad(degrees));
    }

    void set_position(float x, float y, float z)
    {
        set_position({x, y, z});
    }

    void set_position(Vector3 pos)
    {
        mesh->position = pos;
        corner_pos = pos.sub({360.0f, 120.0f, -43.2f});
    }

    void add_item(const Item &item)
    {
        items.insertAtTail(item);
        item_count++;
    }

    void clear(std::shared_ptr<Scene> &scene)
    {
        while (item_count > 0)
        {
            scene->remove(items.getTailValue().mesh);
            items.deleteTail();
            item_count--;
        }
    }

    [[nodiscard]] Vector3 next_position(const Item &item)
    {
        Vector3 offset = {item.size.x, item.size.y, item.size.z};
        offset.multiplyScalar(0.5f);

        int z_index = (int)(item_count / 8);
        int plane_index = (item_count) % 8;

        offset.z += item.size.z * ((float)z_index);

        if (plane_index <= 3)
            offset.add({item.size.x * ((float)(plane_index)), 0.0f, 0.0f});
        else
            offset.add({item.size.x  * ((float)(plane_index-4)), item.size.y, 0.0f});

        Vector3 position = corner_pos + offset;

        return position;
    }
};


#endif //ROBOTCONTROLLER_EUROPALLET_H
