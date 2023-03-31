//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_CONVEYORBELT_H
#define ROBOTCONTROLLER_CONVEYORBELT_H

#include "../helpers/Helper.h"
#include "items/Item.h"
#include "items/Box.h"

struct ConveyorBelt {

public:
    explicit ConveyorBelt(float leg_height, Vector3 pos = {0.0f, 0.0f, 0.0f});

    std::shared_ptr<Group> conveyor;
    std::shared_ptr<Mesh> leg_mesh;
    std::shared_ptr<Mesh> body_mesh;
    std::shared_ptr<Mesh> belt_mesh;

    std::shared_ptr<Scene> scene_;
    List<Item> items;

    Vector3 position{};
    Vector3 start_offset{};
    float spawn_rate = 1.0f; // s/spawn
    float speed = 250.0f; // mm/s
    bool pause = false;

    float time_since_last_spawn = spawn_rate;

    void update(float dt);
    void remove_item();

    [[nodiscard]] float get_surface_height() const
    {
        return conveyor->position.z + 100;
    }

    void set_leg_color(Color color) const {change_mesh_color(leg_mesh, color);}
    void set_body_color(Color color) const {change_mesh_color(body_mesh, color);}
    void set_belt_color(Color color) const {change_mesh_color(belt_mesh, color);}
    void set_position(Vector3 position_)
    {
        conveyor->position = position_;
        position = position_;
    }
    void rotate(float degrees) const {conveyor->rotateZ(math::degToRad(degrees));}
    void add_item();
    void upgrade_spawn_rate(float rate) {spawn_rate /= rate;}
    void upgrade_speed(float rate) {speed *= rate;}

private:
    float leg_height = 200.0f;
    unsigned int item_count = items.length();

};


#endif //ROBOTCONTROLLER_CONVEYORBELT_H
