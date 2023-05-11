//
// Created by peter on 3/30/2023.
//
#include "objects/ConveyorBelt.hpp"


ConveyorBelt::ConveyorBelt(float leg_height, Vector3 pos) {
    leg_mesh = meshFromSTL("bin/data/models/conveyor_legs.stl", Color::whitesmoke, {1.0f, 1.0f, leg_height});
    body_mesh = meshFromSTL("bin/data/models/conveyor_main.stl", Color::whitesmoke);
    belt_mesh = meshFromSTL("bin/data/models/conveyor_belt.stl", Color::orange);

    leg_mesh->position.setZ(-leg_height);

    conveyor = Group::create();
    conveyor->add(leg_mesh);
    conveyor->add(body_mesh);
    conveyor->add(belt_mesh);

    rotate(90);
    setPosition(pos);
    start_offset = {0.0f, -1000.0f, leg_height};
}

void ConveyorBelt::update(float dt) {

    if (!running) {
        time_since_last_spawn += dt;
        if (time_since_last_spawn >= spawn_rate) {
            addItem();
        }

        ListItem<Item> *node = items.getHead();

        float distance = dt * speed;
        for (int i = 0; i < item_count; i++) {
            if (node->value.toMove() < distance) {
                node->value.move(distance, y);
                running = true;
            } else {
                node->value.move(distance, y);
            }

            node = node->next;
        }

    }
}

void ConveyorBelt::removeItem() {
    if (item_count > 0) {
        items.deleteTail();
        item_count--;
        running = false;
    }
}

void ConveyorBelt::addItem() {
    if (running)
        return;

    Box box;
    box.mesh->position = conveyor->position + start_offset;
    box.mesh->position.z += box.size.z * 0.5f;
    items.insertAtHead(box);
    item_count++;
    scene_->add(box.mesh);
    time_since_last_spawn -= spawn_rate;
}
