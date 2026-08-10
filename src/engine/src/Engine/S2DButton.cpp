//
// Created by IvanMiatselski on 09.08.2026.
//

#include "Engine/S2DButton.hpp"

#include "SDL3/SDL.h"

#include <iostream>


S2DButton::S2DButton(const std::string& newLabel, const S2DVector2<float> &newPos):
    buttonLabel(newLabel),
    windowPos(newPos)
{}

S2DButton::S2DButton(const std::string& newLabel, const ImGuiWindowFlags &newFlags):
    buttonLabel(newLabel),
    windowFlags(newFlags)
{}

S2DButton::S2DButton(const std::string& newLabel, const S2DVector2<float> &newPos, const ImGuiWindowFlags &newFlags):
    buttonLabel(newLabel),
    windowPos(newPos),
    windowFlags(newFlags)
{}

void S2DButton::Render(const std::shared_ptr<S2DRenderContext>& renderContext) {
    ImGui::SetNextWindowPos(ImVec2(windowPos.x, windowPos.y));
    ImGui::Begin(buttonLabel.c_str(), nullptr, windowFlags);

    if (ImGui::Button(buttonLabel.c_str()) && onClickCallback) {
        onClickCallback();
    }

    ImGui::End();
}

void S2DButton::setOnClickCallback(const std::function<void()> &newCallback) {
    onClickCallback = newCallback;
}