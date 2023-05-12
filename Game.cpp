//
// Created by peter on 2/21/2023.
//
#include "Game.hpp"


void Game::setupScene() {

    scene = Scene::create();
    camera->position.set(700, -1000, 500);
    camera->up.set(0, 0, 1);
    camera->lookAt(0, 0, 0);

    auto floor = BoxGeometry::create(5000, 5000, 0.1);
    auto floor_material = MeshBasicMaterial::create();
    floor_material->color = 0x111111;
    auto floor_mesh = Mesh::create(floor, floor_material);
    scene->add(floor_mesh);

    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(1000, 1000, 1000);
        scene->add(light);
    }
    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(-1000, -1000, 1000);
        scene->add(light);
    }
    {
        auto light = AmbientLight::create(0xffffff, 0.6f);
        scene->add(light);
    }

    raycaster = Raycaster{};
}

void Game::runGame() {

    Canvas canvas(Canvas::Parameters().size({1280, 720}).antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    camera = PerspectiveCamera::create(90, canvas.getAspect(), 0.1f, 5000);
    OrbitControls controls{camera, canvas};
    controls.enableKeys = false;

    setupScene();

    // ------------------------ Code from threepp examples
    // Key Listener
    KListener keyListener(t1);
    canvas.addKeyListener(&keyListener);

    // Mouse Listener
    MListener mouseListener(t2);
    canvas.addMouseListener(&mouseListener);

    // Mouse Ray
    mouse = {-Infinity<float>, -Infinity<float>};

    MouseMoveListener l([&](Vector2 pos) {

        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });

    canvas.addMouseListener(&l);

    // ------------------------------------------------------------------

    double MONEY = 200.0f;
    AR2::Robot::money = &MONEY;

    renderer.enableTextRendering();
    auto &textHandle = renderer.textHandle("Money " + std::to_string((int) MONEY));
    textHandle.setPosition(0, canvas.getSize().height - 30);
    textHandle.scale = 2;

    ui = std::make_unique<UpgradeUI>(canvas);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, canvas.getSize().height - 30);
    });

    canvas.animate([&](float dt) {

        checkListenerActions(&keyListener, &mouseListener);
        checkUpgrades();

        // Update all robots
        auto node = robots.getHead();
        while (node != nullptr) {
            node->value->update(dt);
            node = node->next;
        }

        renderer.render(scene, camera);
        textHandle.setText("Money " + std::to_string((int) MONEY));

        ui->render();
        controls.enabled = !ui->mouseHovered;

    });
}

void Game::addRobot(Vector3 pos) {

    robots.insertAtTail(AR2::Robot::create());
    robots.getTailValue()->moveBaseTo(pos);
    scene->add(robots.getTailValue()->getMesh());
    robots.getTailValue()->gripper->mesh->visible = false;
    robots.getTailValue()->scene = scene;
}


std::shared_ptr<ConveyorBelt> Game::createConveyor() {
    raycaster.setFromCamera(mouse, camera);
    auto intersects = raycaster.intersectObjects(scene->children);
    if (!intersects.empty()) {
        Vector3 world_pos = intersects.front().point;
        auto conveyor = std::make_shared<ConveyorBelt>(100.0f, Vector3{world_pos.x, world_pos.y, 20.0f});
        scene->add(conveyor->conveyor);
        conveyor->scene_ = scene;
        return conveyor;
    }
}

std::shared_ptr<EuroPallet> Game::createPallet() {
    raycaster.setFromCamera(mouse, camera);
    auto intersects = raycaster.intersectObjects(scene->children);
    if (!intersects.empty()) {

        Vector3 world_pos = intersects.front().point;
        auto pallet = std::make_shared<EuroPallet>();
        pallet->setPosition(world_pos.x + 180.0f, world_pos.y, 0.0f);
        scene->add(pallet->mesh);

        return pallet;
    }
}

void Game::checkListenerActions(KListener *keyListener, MListener *mouseListener) {

    if (keyListener->current == keyListener->b_ && mouseListener->LEFTCLICK) {
        if (robots.length() == 0 || robots.getTailValue()->conveyor && robots.getTailValue()->pallet) {

            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                Vector3 worldPos = intersects.front().point;
                addRobot(worldPos);
                keyListener->current = 0;
            }
        }
    }

    if (keyListener->current == keyListener->n_ && mouseListener->LEFTCLICK) {
        if (robots.length() > 0 && !robots.getTailValue()->conveyor) {
            robots.getTailValue()->attachConveyor(createConveyor());
            keyListener->current = 0;
        }
    }
    if (keyListener->current == keyListener->m_ && mouseListener->LEFTCLICK) {
        if (robots.length() > 0 && !robots.getTailValue()->pallet) {
            robots.getTailValue()->attachPallet(createPallet());
            keyListener->current = 0;
        }

    }
}

void Game::checkUpgrades() {
    if (robots.length() == 0 || robots.getHeadValue()->pallet == nullptr || robots.getHeadValue()->conveyor == nullptr)
        return;
    if (ui->upgradePalletReward) {
        robots.getHeadValue()->pallet->upgradeDeliverValue(1.1);
        ui->upgradePalletReward = false;
    }
    if (ui->upgradeSpawnRate) {
        robots.getHeadValue()->conveyor->upgradeSpawnRate(1.1);
        ui->upgradeSpawnRate = false;
    }
    if (ui->upgradeBeltSpeed) {
        robots.getHeadValue()->conveyor->upgradeSpeed(1.1);
        ui->upgradeBeltSpeed = false;
    }
    if (ui->upgradeRobotSpeed) {
        robots.getHeadValue()->upgradeSpeed(1.1);
        ui->upgradeRobotSpeed = false;
    }
}
