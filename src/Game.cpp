#include "Game.hpp"

Game::Game() :
    canvas(Canvas::Parameters()
                   .size({1280, 720})
                   .antialiasing(16)
                   .title("Robot Palletizer Tycoon")),
    renderer(canvas),
    camera(std::make_shared<PerspectiveCamera>(70, canvas.getAspect(), 0.1f, 6000)),
    controls(camera, canvas),
    keyListener(t1),
    mouseListener(t2)
{
    renderer.enableTextRendering();
    renderer.shadowMap().enabled = true;
    renderer.shadowMap().type = PCFSoftShadowMap;
    renderer.setClearColor(Color::aliceblue);

    camera->position.set(700, -1000, 500);
    camera->up.set(0, 0, 1);
    camera->lookAt(0, 0, 0);
    controls.enableKeys = false;

    ui = std::make_unique<UpgradeUI>(canvas);
    AR2::Robot::money = &money;
    setupScene();
    setupListeners();
}

void Game::setupListeners() {

    canvas.addKeyListener(&keyListener);
    canvas.addMouseListener(&mouseListener);

    // Mouse Ray
    mouse = {-Infinity<float>, -Infinity<float>};

    l = std::make_unique<MouseMoveListener>([&](Vector2 pos) {
        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });

    canvas.addMouseListener(l.get());
}

void Game::setupScene() {
    scene = Scene::create();
    auto floor = BoxGeometry::create(5000, 5000, 100.0f);
    auto floor_material = MeshPhongMaterial::create();
    auto texture = loadTexture("bin/data/textures/concrete.png");
    texture->wrapT = RepeatWrapping;
    texture->wrapS = RepeatWrapping;
    texture->repeat = {5, 5};
    floor_material->map = texture;
    auto floor_mesh = Mesh::create(floor, floor_material);
    floor_mesh->position.z = -50.0f;
    floor_mesh->receiveShadow = true;
    scene->add(floor_mesh);

    auto spotLight = SpotLight::create(0xffffff, 0.7f);
    spotLight->distance = 10000;
    spotLight->position.set(1000, 1000, 4000);
    spotLight->castShadow = true;
    spotLight->shadow->mapSize.set(2048, 2048);
    scene->add(spotLight);
    scene->add(AmbientLight::create(0xffffff, 0.4f));

    raycaster = Raycaster{};
}

void Game::runGame() {

    auto &textHandle = renderer.textHandle("Money " + std::to_string((int) money));
    textHandle.setPosition(5, canvas.getSize().height - 25);
    textHandle.scale = 2;

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
        textHandle.setText("Money " + std::to_string((int) money));
        ui->render();
        controls.enabled = !ui->mouseHovered;

    });
}

void Game::createRobot(Vector3 pos) {

    auto newRobot = AR2::Robot::create();
    newRobot->scene = scene;
    newRobot->gripper->mesh->visible = false;
    newRobot->moveBaseTo(pos);
    scene->add(newRobot->getMesh());

    ui->upgradeRobotSpeedCost = &newRobot->uSpeedCost;

    robots.insertAtTail(newRobot);

}

void Game::createConveyor(Vector3 pos) {

    auto conveyor = std::make_shared<ConveyorBelt>(100.0f, Vector3{pos.x, pos.y, 20.0f});
    scene->add(conveyor->conveyor);
    conveyor->scene_ = scene;
    robots.getTailValue()->attachConveyor(conveyor);

    ui->upgradeBeltSpeedCost = &conveyor->uSpeedCost;
    ui->upgradeSpawnRateCost = &conveyor->uSpawnRateCost;
}

void Game::createPallet(Vector3 pos) {

    auto pallet = std::make_shared<EuroPallet>();
    pallet->setPosition(pos.x + 180.0f, pos.y, 0.0f);
    scene->add(pallet->mesh);
    robots.getTailValue()->attachPallet(pallet);

    ui->upgradePalletRewardCost = &pallet->uPalletRewardCost;
}

void Game::checkListenerActions(KListener *keyListener, MListener *mouseListener) {

    if (keyListener->current == keyListener->b_ && mouseListener->LEFTCLICK) {
        if (robots.length() == 0 || robots.getTailValue()->conveyor && robots.getTailValue()->pallet) {

            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                Vector3 worldPos = intersects.front().point;
                createRobot(worldPos);
                keyListener->current = 0;
            }
        }
    }

    if (keyListener->current == keyListener->n_ && mouseListener->LEFTCLICK) {
        if (robots.length() > 0 && !robots.getTailValue()->conveyor) {

            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                createConveyor(intersects.front().point);
                keyListener->current = 0;
            }

        }
    }
    if (keyListener->current == keyListener->m_ && mouseListener->LEFTCLICK) {
        if (robots.length() > 0 && !robots.getTailValue()->pallet) {

            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                createPallet(intersects.front().point);
                keyListener->current = 0;
            }
        }
    }
}

void Game::checkUpgrades() {

    if (robots.length() == 0 || robots.getTailValue()->pallet == nullptr || robots.getTailValue()->conveyor == nullptr) {
        return;
    }

    if (ui->upgradePalletReward) {
        if (money > robots.getTailValue()->pallet->uPalletRewardCost) {
            money -= robots.getTailValue()->pallet->uPalletRewardCost;
            robots.getTailValue()->pallet->upgradePalletReward(1.1);
        }
        ui->upgradePalletReward = false;
    }
    if (ui->upgradeSpawnRate) {
        if (money > robots.getTailValue()->conveyor->uSpawnRateCost) {
            money -= robots.getTailValue()->conveyor->uSpawnRateCost;
            robots.getTailValue()->conveyor->upgradeSpawnRate(1.1);
        }
        ui->upgradeSpawnRate = false;
    }
    if (ui->upgradeBeltSpeed) {
        if (money > robots.getTailValue()->conveyor->uSpeedCost) {
            money -= robots.getTailValue()->conveyor->uSpeedCost;
            robots.getTailValue()->conveyor->upgradeSpeed(1.1);
        }

        ui->upgradeBeltSpeed = false;
    }
    if (ui->upgradeRobotSpeed) {
        if (money > robots.getTailValue()->uSpeedCost) {
            money -= robots.getTailValue()->uSpeedCost;
            robots.getTailValue()->upgradeSpeed(1.1);
        }
        ui->upgradeRobotSpeed = false;
    }
}
