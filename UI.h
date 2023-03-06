//
// Created by peter on 2/20/2023.
//

#ifndef THREEPP_VCPKG_TEST_UI_H
#define THREEPP_VCPKG_TEST_UI_H

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "serial_communication/Serial.h"

using namespace threepp;

struct UI : imgui_context {

public:
    explicit UI(const Canvas &canvas) : imgui_context(canvas.window_ptr()){};

    Vector3 pos;
    bool move_btn_clicked;

    bool mouseHovered = false;

    void onRender();
    std::vector<std::string> ports = {};
    char* current_port = nullptr;
};

#endif //THREEPP_VCPKG_TEST_UI_H
