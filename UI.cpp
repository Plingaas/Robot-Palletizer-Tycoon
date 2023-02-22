//
// Created by peter on 2/20/2023.
//

#include "UI.h"
using namespace threepp;

#ifdef HAS_IMGUI
#include "threepp/extras/imgui/imgui_context.hpp"

#include "Kine.hpp"
#include "ik/CCDSolver.hpp"

using namespace kine;

struct MyUI : imgui_context {

    bool mouseHover = false;
    bool jointMode = true;
    bool posMode = false;
    bool enableController = false;

    Vector3 pos;
    std::vector<KineLimit> limits;
    std::vector<float> values;

    explicit MyUI(const Canvas &canvas, Kine &kine)
        : imgui_context(canvas.window_ptr()),
          limits(kine.limits()),
          values(kine.meanAngles()) {

        pos.setFromMatrixPosition(kine.calculateEndEffectorTransformation(values));
    }

    void onRender() override {

        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize({}, 0);
        ImGui::Begin("Crane3R");

        ImGui::Text("Target angles");
        ImGui::SliderFloat("j1", &values[0], *limits[0].min(), *limits[0].max());
        jointMode = jointMode || ImGui::IsItemEdited();
        ImGui::SliderFloat("j2", &values[1], *limits[1].min(), *limits[1].max());
        jointMode = jointMode || ImGui::IsItemEdited();
        ImGui::SliderFloat("j3", &values[2], *limits[2].min(), *limits[2].max());
        jointMode = jointMode || ImGui::IsItemEdited();

        posMode = !jointMode;

        ImGui::Text("Target pos");
        ImGui::SliderFloat("px", &pos.x, -10, 10);
        posMode = posMode || ImGui::IsItemEdited();
        ImGui::SliderFloat("py", &pos.y, 0, 10);
        posMode = posMode || ImGui::IsItemEdited();
        ImGui::SliderFloat("pz", &pos.z, 0, 10);
        posMode = posMode || ImGui::IsItemEdited();

        jointMode = !posMode;

        ImGui::Checkbox("controller", &enableController);

        mouseHover = ImGui::IsWindowHovered();
        ImGui::End();
    }
};
#endif