#define CATCH_CONFIG_MAIN

#include "objects/ConveyorBelt.hpp"
#include "threepp/threepp.hpp"

#include <catch2/catch.hpp>

// This wont work because the STL files cant be found
// as they are located in the build folder. The same goes for
// Robots,
TEST_CASE("Conveyor Test") {

    ConveyorBelt::legSTLPath = "../bin/data/models/conveyor_legs.stl";
    ConveyorBelt::bodySTLPath = "../bin/data/models/conveyor_main.stl";
    ConveyorBelt::beltSTLPath = "../bin/data/models/conveyor_belt.stl";

    auto conveyor = ConveyorBelt(100.0f);
    conveyor.scene_ = Scene::create();

    conveyor.addItem();
    CHECK(conveyor.items.length() == 1);

    conveyor.removeItem();
    CHECK(conveyor.items.length() == 0);

    float oldSpeed = conveyor.speed;
    conveyor.upgradeSpeed(2.0f);
    CHECK(conveyor.speed == oldSpeed*2.0f);

    float oldSpawnRate = conveyor.spawnRate;
    conveyor.upgradeSpawnRate(2.0f);
    CHECK(conveyor.spawnRate == oldSpawnRate * (1/2.0f) ); // upgradeSpawnRate(float) divides by the multiplier

}
