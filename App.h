//
// Created by peter on 2/21/2023.
//

#ifndef THREEPP_VCPKG_TEST_APP_H
#define THREEPP_VCPKG_TEST_APP_H
#include "threepp/extras/imgui/imgui_context.hpp"

#include <threepp/threepp.hpp>
#include "robot_arm/Robot.h"
#include "UI.h"
#include "Listener.h"
#include "serial_communication/Serial.h"

using namespace threepp;

void run(int* A, const int* B, const int *C, char** port);

#endif //THREEPP_VCPKG_TEST_APP_H
