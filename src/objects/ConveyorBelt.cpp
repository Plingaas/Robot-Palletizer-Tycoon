//
// Created by peter on 3/30/2023.
//
#include "objects/ConveyorBelt.hpp"


ConveyorBelt::ConveyorBelt(float leg_height, Vector3 pos) {
    legMesh = meshFromSTL("bin/data/models/conveyor_legs.stl", Color::whitesmoke, {1.0f, 1.0f, leg_height});
    bodyMesh = meshFromSTL("bin/data/models/conveyor_main.stl", Color::whitesmoke);
    beltMesh = meshFromSTL("bin/data/models/conveyor_belt.stl", Color::orange);

    legMesh->position.setZ(-leg_height);

    conveyor = Group::create();
    conveyor->add(legMesh);
    conveyor->add(bodyMesh);
    conveyor->add(beltMesh);

    rotate(90);
    setPosition(pos);
    startOffset = {0.0f, -1000.0f, leg_height};
}

void ConveyorBelt::update(float dt) {

    if (!running) {
        timeSinceLastSpawn += dt;
        if (timeSinceLastSpawn >= spawnRate) {
            addItem();
        }

        ListItem<Item> *node = items.getHead();

        float distance = dt * speed;
        for (int i = 0; i < itemCount; i++) {
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
    if (itemCount > 0) {
        items.deleteTail();
        itemCount--;
        running = false;
    }
}

void ConveyorBelt::addItem() {
    if (running)
        return;

    Box box;
    box.mesh->position = conveyor->position + startOffset;
    box.mesh->position.z += box.size.z * 0.5f;
    items.insertAtHead(box);
    itemCount++;
    scene_->add(box.mesh);
    timeSinceLastSpawn -= spawnRate;
}
