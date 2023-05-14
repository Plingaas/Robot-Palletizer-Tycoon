#include "objects/ConveyorBelt.hpp"

ConveyorBelt::ConveyorBelt(float leg_height, Vector3 pos) {
    legMesh = meshFromSTL(legSTLPath, 0x333333, {1.0f, 1.0f, leg_height});
    bodyMesh = meshFromSTL(bodySTLPath, 0x333333);
    beltMesh = meshFromSTL(beltSTLPath, Color::silver);

    legMesh->castShadow = true;
    bodyMesh->castShadow = true;
    beltMesh->receiveShadow = true;

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

        ListItem<std::shared_ptr<Item>> *node = items.getHead();

        float distance = dt * speed;
        for (int i = 0; i < itemCount; i++) {
            if (node->value->toMove() < distance) {
                node->value->move(distance, y);
                running = true;
            } else {
                node->value->move(distance, y);
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


    std::shared_ptr<Item> block = ItemGenerator::generateRandomItem();
    block->mesh->position = conveyor->position + startOffset;
    block->mesh->position.z += block->size.z * 0.5f;

    items.insertAtHead(block);
    itemCount++;
    scene_->add(block->mesh);
    timeSinceLastSpawn -= spawnRate;
}
