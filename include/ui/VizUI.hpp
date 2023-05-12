#ifndef THREEPP_VCPKG_TEST_UI_H
#define THREEPP_VCPKG_TEST_UI_H

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "serial_communication/Serial.hpp"

using namespace threepp;

struct VizUI : imgui_context {

public:

    /**
     * @brief Constructor for the VizUI.
     *
     * @param canvas The canvas the VizUI will exist on.
     *
     * @return void.
     */
    explicit VizUI(const Canvas &canvas) : imgui_context(canvas.window_ptr()) {};

    Vector3 pos;
    bool moveButtonClicked;

    bool mouseHovered = false;

    /**
     * @brief The update loop.
     *
     * This is where the VizUI is constructed and events are looked for.
     *
     * @return void.
     */
    void onRender();

    // Contains al the ports available for serial connection.
    std::vector<std::string> ports = {};
    char *currentPort = nullptr;
};

#endif //THREEPP_VCPKG_TEST_UI_H
