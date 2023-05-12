//
// Created by peter on 2/20/2023.
//

#include "UI/UI.hpp"

using namespace threepp;

void UI::onRender() {
    ImGui::Begin("Settings");

    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##x", &pos.x);

    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##y", &pos.y);
    ImGui::SameLine();
    if (ImGui::Button("Move")) {
        moveButtonClicked = true;
    }

    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##z", &pos.z);

    ImGui::NewLine();

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(
            ImVec2(ImGui::GetWindowPos().x + 5, ImGui::GetWindowPos().y + 111),
            ImVec2(ImGui::GetWindowPos().x + 90, ImGui::GetWindowPos().y + 130),
            IM_COL32(200, 200, 200, 100)
    );
    ImGui::Text("Serial Port");
    ImGui::SameLine();

    // Code inspiration from https://github.com/ocornut/imgui/issues/1658
    if (ImGui::BeginCombo("##combo", currentPort)) {
        ports = Serial::availablePorts();
        for (const std::string &_port: ports) {
            char *port = const_cast<char *>(_port.c_str());
            bool is_selected = (currentPort == port);

            if (ImGui::Selectable(port, is_selected))
                currentPort = port;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    mouseHovered = ImGui::IsWindowHovered();
    ImGui::End();
}
