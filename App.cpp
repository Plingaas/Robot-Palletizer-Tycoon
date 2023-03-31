//
// Created by peter on 2/21/2023.
//
#include "App.h"

void run(int *A, const int *B, const int *C, char** port) {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::black);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(90, canvas.getAspect(), 0.1f, 5000);
    camera->position.set(700,-1000, 500);
    camera->up.set(0,0,1);
    camera->lookAt(0,0,0);

    OrbitControls controls{camera, canvas};
    controls.enableKeys = false;

    auto floor = BoxGeometry::create(5000, 5000, 0.1);
    auto floor_material = MeshBasicMaterial::create();
    floor_material->color = 0x111111;
    auto floor_mesh = Mesh::create(floor, floor_material);
    floor_mesh->position.setZ(-0.5f-200.0f);
    scene->add(floor_mesh);

    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(1000,1000,1000);
        scene->add(light);
    }
    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(-1000,-1000,1000);
        scene->add(light);
    }

    {
        auto light = AmbientLight::create(0xffffff, 0.6f);
        scene->add(light);
    }

    UI ui(canvas);

    auto target_geo = SphereGeometry::create(5);
    auto target_mat = MeshPhongMaterial::create();
    target_mat->color = Color::red;
    auto target_mesh = Mesh::create(target_geo, target_mat);
    target_mesh->position.set(0, 0, 0);
    scene->add(target_mesh);

    // Key Listener
    float t = 0;
    Listener listener{t};
    canvas.addKeyListener(&listener);

    // Mouse Listener
    float t2 = 0;
    MListener mlistener{t2};
    canvas.addMouseListener(&mlistener);

    // Mouse Ray
    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](Vector2 pos) {
        // calculate mouse position in normalized device coordinates
        // (-1 to +1) for both components

        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });
    canvas.addMouseListener(&l);
    Raycaster raycaster;

    List<std::shared_ptr<AR2::Robot>> robots;

    robots.insertAtTail(AR2::Robot::create());
    robots.getTailValue()->move_base_to({0.0f, 0.0f, -100.0f});
    scene->add(robots.getTailValue()->get_mesh());
    robots.getTailValue()->gripper->mesh->visible = false;
    robots.getTailValue()->scene = scene;

    ConveyorBelt conveyor_belt(100.0f);
    conveyor_belt.set_position({300.0f, 0.0f, -100.0f});
    scene->add(conveyor_belt.conveyor);
    conveyor_belt.scene_ = scene;
    robots.getTailValue()->attach_conveyor(&conveyor_belt);

    EuroPallet pallet;
    pallet.set_position(0.0f, -400.0f, -200.0f);
    scene->add(pallet.mesh);
    robots.getTailValue()->attach_pallet(&pallet);

    //////////////////
    robots.insertAtTail(AR2::Robot::create());
    robots.getTailValue()->move_base_to({1000.0f, 0.0f, -200.0f});
    scene->add(robots.getTailValue()->get_mesh());
    robots.getTailValue()->gripper->mesh->visible = false;
    robots.getTailValue()->scene = scene;

    ConveyorBelt conveyor_belt2(100.0f);
    conveyor_belt2.set_position({700.0f, 0.0f, -100.0f});
    scene->add(conveyor_belt2.conveyor);
    conveyor_belt2.scene_ = scene;
    robots.getTailValue()->attach_conveyor(&conveyor_belt2);

    EuroPallet pallet2;
    pallet2.set_position(1360.0f, -400.0f, -200.0f);
    scene->add(pallet2.mesh);
    robots.getTailValue()->attach_pallet(&pallet2);

    ////////////////

    float MONEY = 0.0f;
    AR2::Robot::money = &MONEY;

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("Money");
    textHandle.setPosition(0, canvas.getSize().height - 30);
    textHandle.scale = 2;

    auto& textHandle2 = renderer.textHandle();
    textHandle2.setPosition(150, canvas.getSize().height - 30);
    textHandle2.scale = 2;

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, canvas.getSize().height - 30);
        textHandle2.setPosition(150, canvas.getSize().height - 30);
    });

    canvas.animate([&](float dt) {
        controls.enabled = !ui.mouseHovered;

        auto node = robots.getHead();

        if (listener.current == listener.t_)
        {
            robots.getHeadValue()->upgrade_speed(1.1f);
            listener.current = 0;
        }
        if (listener.current == listener.y_)
        {
            robots.getHeadValue()->conveyor->upgrade_speed(1.1f);
            listener.current = 0;
        }
        if (listener.current == listener.u_)
        {
            robots.getHeadValue()->conveyor->upgrade_spawn_rate(1.1f);
            listener.current = 0;
        }

        bool create_robot = listener.current == listener.b_ && mlistener.LEFTCLICK;
        if (create_robot) {
            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                listener.current = 0;

                Vector3 world_pos = intersects.front().point;

                robots.insertAtTail(AR2::Robot::create());
                robots.getTailValue()->move_base_to(world_pos);
                scene->add(robots.getTailValue()->get_mesh());
                robots.getTailValue()->gripper->mesh->visible = false;
                robots.getTailValue()->scene = scene;
            }
        }

        bool create_conveyor = listener.current == listener.n_ && mlistener.LEFTCLICK;
        if (create_conveyor) {
            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                listener.current = 0;

                Vector3 world_pos = intersects.front().point;

                auto conveyor_belt3 = new ConveyorBelt(100.0f, {world_pos.x, world_pos.y, -100.0f});
                scene->add(conveyor_belt3->conveyor);
                conveyor_belt3->scene_ = scene;
                robots.getTailValue()->attach_conveyor(conveyor_belt3);
            }
        }

        bool create_pallet = listener.current == listener.m_ && mlistener.LEFTCLICK;
        if (create_pallet) {
            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                listener.current = 0;

                Vector3 world_pos = intersects.front().point;
                auto pallet3 = new EuroPallet();
                pallet3->set_position(world_pos.x, world_pos.y, -200.0f);
                scene->add(pallet3->mesh);
                robots.getTailValue()->attach_pallet(pallet3);
            }
        }

        while (node != nullptr)
        {
            node->value->update(dt);
            node = node->next;
        }

        renderer.render(scene, camera);
        ui.render();
        textHandle2.setText(std::to_string((int) MONEY));
        *port = ui.current_port;
    });
}

// Serial data position
//robots.getHead()->value->go_to_steps(*A, *B, *C);

// Spawns a robot at mouse position in 3d space by pressing n then left clicking
/*
        bool createRobot = listener.current == listener.n_ && mlistener.LEFTCLICK;
        if (createRobot) {
            raycaster.setFromCamera(mouse, camera);
            auto intersects = raycaster.intersectObjects(scene->children);
            if (!intersects.empty()) {
                listener.current = 0;
                robots.insertAtTail(AR2::Robot::create());
                robots.getTailValue()->move_base_to(intersects.front().point);
                scene->add(robots.getTailValue()->get_mesh());
            }
        }
*/