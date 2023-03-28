//
// Created by peter on 2/21/2023.
//
#include "App.h"

void run(int *A, const int *B, const int *C, char** port) {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::black);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(90, canvas.getAspect(), 0.1f, 50000);
    camera->position.set(300,300, 500);
    camera->up.set(0,0,1);
    camera->lookAt(300, 300, 0);

    OrbitControls controls{camera, canvas};
    controls.enableKeys = false;

    auto floor = BoxGeometry::create(2000, 2000, 0.1);
    auto floor_material = MeshBasicMaterial::create();
    floor_material->color = 0x111111;
    auto floor_mesh = Mesh::create(floor, floor_material);
    floor_mesh->position.setZ(-0.5f-200.0f);
    scene->add(floor_mesh);

    renderer.render(scene, camera);

    List<std::shared_ptr<AR2::Robot>> robots;

    robots.insertAtTail(AR2::Robot::create());
    scene->add(robots.getHeadValue()->get_mesh());

    robots.insertAtTail(AR2::Robot::create());
    robots.getTailValue()->move_base_to({500, 500, -200});
    scene->add(robots.getTailValue()->get_mesh());


    auto geo_base = CylinderGeometry::create(75, 100, 200, 50);
    auto mat_base = MeshPhongMaterial::create();
    mat_base->color = Color::aliceblue;
    auto mesh_base = Mesh::create(geo_base, mat_base);
    mesh_base->rotation.set(math::PI*0.5f, 0, 0);
    mesh_base->position.set(0, 0, -100);
    scene->add(mesh_base);

    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(100,100,100);
        scene->add(light);
    }
    {
        auto light = DirectionalLight::create(0xffffff, 0.4f);
        light->position.set(-100,-100,100);
        scene->add(light);
    }

    {
        auto light = AmbientLight::create(0xffffff, 0.6f);
        scene->add(light);
    }

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

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

    canvas.animate([&](float dt) {
        // Serial data position
        robots.getHead()->value->go_to_steps(*A, *B, *C);

        // Create robot when conditions met
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

        controls.enabled = !ui.mouseHovered;

        target_mesh->position = ui.pos;
        if (ui.move_btn_clicked)
        {
            robots.getTail()->value->set_target(ui.pos);
            ui.move_btn_clicked = false;
        }
        robots.getTail()->value->update(dt);


        renderer.render(scene, camera);

        ui.render();
        *port = ui.current_port;
    });
}