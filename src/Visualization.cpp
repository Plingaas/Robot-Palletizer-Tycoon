//
// Created by peter on 5/12/2023.
//

#include "Visualization.hpp"

void Visualization::setupScene() {

    scene = Scene::create();
    // Floor
    auto floor1 = CylinderGeometry::create(750, 750, 1, 100, 1);
    auto floorMaterial1 = MeshBasicMaterial::create();
    floorMaterial1->color = 0x333333;
    auto floorMesh1 = Mesh::create(floor1, floorMaterial1);
    floorMesh1->rotateX(math::PI*0.5f);

    // Floor
    auto floor2 = CylinderGeometry::create(750, 750, 1, 100, 1);
    auto floorMaterial2 = MeshBasicMaterial::create();
    floorMaterial2->color = 0x333333;
    auto floorMesh2 = Mesh::create(floor2, floorMaterial2);
    floorMesh2->rotateX(math::PI*0.5f);
    floorMesh2->position.set(0.0f, 2000.0f, 0.0f);

    scene->add(floorMesh1);
    scene->add(floorMesh2);

    // Lighting
    auto light1 = DirectionalLight::create(0xffffff, 0.4f);
    light1->position.set(1000, 1000, 1000);
    scene->add(light1);
    auto light2 = AmbientLight::create(0xffffff, 0.6f);
    scene->add(light2);

    // Add text above robots
    auto textViz = meshFromSTL("bin/data/models/visualize_text.stl", Color::yellow);
    textViz->position.set(0.0f, -240.0f, 500.0f);
    textViz->rotateZ(math::PI*0.5f);

    auto textControl = meshFromSTL("bin/data/models/control_text.stl", Color::yellow);
    textControl->position.set(0.0f, 1760.0f, 500.0f);
    textControl->rotateZ(math::PI*0.5f);

    scene->add(textViz);
    scene->add(textControl);
}

void Visualization::runVisualization(const std::array<int, 3> &serialData, char **port) {

    // Setup canvas and renderer
    Canvas canvas(Canvas::Parameters().size({1280, 720}).antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::black);

    // Setup camera
    camera = PerspectiveCamera::create(90, canvas.getAspect(), 0.1f, 5000);
    camera->position.set(700, -1000, 500);
    camera->up.set(0, 0, 1);
    camera->lookAt(0, 0, 0);
    OrbitControls controls{camera, canvas};
    controls.enableKeys = false;

    setupScene();

    // Add the robots
    auto robotViz = AR2::Robot::create();
    scene->add(robotViz->getMesh());

    auto robotControl = AR2::Robot::create();
    robotControl->moveBaseTo({0.0f, 2000.0f, 0.0f});
    robotControl->setPIDParameters(0.01f, 0.001f, 0.0f);
    scene->add(robotControl->getMesh());

    // Create the target for the control robot
    auto targetGeo = SphereGeometry::create(10.0f, 32, 24);
    auto targetMat = MeshBasicMaterial::create();
    targetMat->color = Color::red;
    auto target = Mesh::create(targetGeo, targetMat);
    scene->add(target);

    // Set the ui
    ui = std::make_unique<VizUI>(canvas);
    ui->pos = Vector3{500.0f, 2000.0f, 500.0f};

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        renderer.render(scene, camera);

        ui->render();
        controls.enabled = !ui->mouseHovered;
        target->position = ui->pos;

        if (ui->moveButtonClicked) {
            robotControl->setTarget(target->position.add(Vector3{0.0f, 0.0f, 52.66f})); // Add gripper length, no time for better fix.
            ui->moveButtonClicked = false;
        }


        *port = ui->currentPort;
        robotViz->goToSteps(serialData);
        robotControl->moveWithPID(dt);
    });
}