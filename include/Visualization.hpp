//
// Created by peter on 5/12/2023.
//

#ifndef ROBOTCONTROLLER_VISUALIZATION_H
#define ROBOTCONTROLLER_VISUALIZATION_H
#include "threepp/threepp.hpp"
#include "serial_communication/Serial.hpp"
#include "ui/VizUI.hpp"
#include "robot_arm/Robot.hpp"
#include "threepp/helpers/SpotLightHelper.hpp"
#include "threepp/lights/LightShadow.hpp"

using namespace threepp;

class Visualization {

private:
    std::shared_ptr<PerspectiveCamera> camera;
    std::shared_ptr<Scene> scene;
    std::unique_ptr<VizUI> ui;

public:

    Visualization(){};

    /**
     * @brief Sets up the scene
     *
     * Sets up the floor, lighting and text in the scene.
     *
     * @return void.
     */
    void setupScene();

    /**
     * @brief Starts the visualization tool
     *
     * This is the function that starts the visualization tool.
     * Once this function is called the tool is ran until
     * the window is closed.
     *
     * @param serialData The serial data from the real robot..
     * @param port The port to connect to.
     *
     * @return void.
     */
    void runVisualization(const std::array<int, 3> &serialData, char **port);

};


#endif //ROBOTCONTROLLER_VISUALIZATION_H
