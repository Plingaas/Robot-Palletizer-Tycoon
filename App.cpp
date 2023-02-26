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

    auto grid = GridHelper::create(2000, 10, Color::red);
    grid->rotation.set(math::PI*0.5f,0,0);
    grid->position.set(0, 0, -200);
    scene->add(grid);


    auto floor = BoxGeometry::create(2000, 2000, 0.1);
    auto floor_material = MeshBasicMaterial::create();
    floor_material->color = 0x111111;
    auto floor_mesh = Mesh::create(floor, floor_material);
    floor_mesh->position.setZ(-0.5f-200.0f);
    scene->add(floor_mesh);

    renderer.render(scene, camera);

    auto robot = AR2::Robot::create();
    scene->add(robot->j0->mesh);

    auto robot2 = AR2::Robot::create();
    robot2->move_base_to({500, 500, -200});
    scene->add(robot2->j0->mesh);


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

    Vector3 target {628.0, 0, 169.77};
    float t = 0;
    //Listener l{t, &target};
    //canvas.addKeyListener(&l);

    UI ui(canvas);

    float total = t;
    bool a = false;
    bool b = true;

    canvas.animate([&](float dt) {
        // Serial data position
        robot->go_to_steps(*A, *B, *C);

        target.x = ui.px;
        target.y = ui.py;
        target.z = ui.pz;

        controls.enableRotate = !ui.mouseHovered;

        robot2->go_to_xyz(ui.px, ui.py, ui.pz);
        renderer.render(scene, camera);

        ui.render();
        *port = ui.current_port;
    });
}