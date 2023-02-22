//
// Created by peter on 2/21/2023.
//
#include "App.h"

void run(const int* A, const int* B, const int* C) {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 5000);
    camera->position.set(0,-600, 600);
    camera->lookAt(0,0,0);

    OrbitControls controls{camera, canvas};

    auto grid = GridHelper::create(800, 16, Color::yellowgreen);
    grid->rotation.set(math::PI*0.5f,0,0);
    scene->add(grid);

    auto robot = AR2::Robot::create();

    scene->add(robot->j0->mesh);

    {
        auto light = DirectionalLight::create(0xffffff, 0.6f);
        light->position.set(10,10,10);
        scene->add(light);
    }
    {
        auto light = DirectionalLight::create(0xffffff, 0.6f);
        light->position.set(-10,10,-10);
        scene->add(light);
    }

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });


    canvas.animate([&](float dt) {

        // Serial data position
        //robot->go_to_steps(*A, *B, *C);
        renderer.render(scene, camera);
    });
}