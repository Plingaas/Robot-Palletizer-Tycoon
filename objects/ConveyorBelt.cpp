//
// Created by peter on 3/30/2023.
//
#include "ConveyorBelt.h"


ConveyorBelt::ConveyorBelt(float leg_height, Vector3 pos)
{
    leg_mesh = mesh_from_stl("bin/data/models/conveyor_legs.stl", Color::whitesmoke, {1.0f, 1.0f, leg_height});
    body_mesh = mesh_from_stl("bin/data/models/conveyor_main.stl", Color::whitesmoke);
    belt_mesh = mesh_from_stl("bin/data/models/conveyor_belt.stl", Color::orange);

    leg_mesh->position.setZ(-leg_height);
    item_start_pos.z -= leg_height;

    conveyor = Group::create();
    conveyor->add(leg_mesh);
    conveyor->add(body_mesh);
    conveyor->add(belt_mesh);

    conveyor->position = pos;
}

void ConveyorBelt::update(float dt)
{

    if (!pause)
    {
        time_since_last_spawn += dt;
        if (time_since_last_spawn >= spawn_rate)
        {
            add_item();
        }

        ListItem<Item> *node = items.getHead();

        float distance = dt*speed;
        for (int i = 0; i < item_count; i++)
        {
            if (node->value.to_move() < distance)
            {
                node->value.move(distance, y);
                pause = true;
            }
            else
            {
                node->value.move(distance, y);
            }

            node = node->next;
        }

    }
}

void ConveyorBelt::remove_item()
{
    if (item_count > 0) {
        items.deleteTail();
        item_count--;
        pause = false;
    }
}

void ConveyorBelt::add_item()
{
    if (pause)
        return;

    Box box;
    box.mesh->position = item_start_pos;
    box.mesh->position.z += box.size.z*0.5f;
    items.insertAtHead(box);
    item_count++;
    scene_->add(box.mesh);
    time_since_last_spawn -= spawn_rate;
}
