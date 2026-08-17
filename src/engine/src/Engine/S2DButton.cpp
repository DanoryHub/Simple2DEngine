//
// Created by IvanMiatselski on 09.08.2026.
//

#include "Engine/S2DButton.hpp"
#include "Engine/S2DRenderContext.hpp"

#include "SDL3/SDL.h"

#include <iostream>


S2DButton::S2DButton(const std::string& newLabel, const S2DVector2<float> &newPos, const S2DVector2<float>& newSize):
    buttonSize(newSize),
    windowPos(newPos) {
    buttonLabel.text = newLabel;
}

S2DButton::S2DButton(const std::string& newLabel, const ImGuiWindowFlags &newFlags):
    windowFlags(newFlags) {
    buttonLabel.text = newLabel;
}

S2DButton::S2DButton(const std::string& newLabel, const S2DVector2<float> &newPos, const S2DVector2<float>& newSize, const ImGuiWindowFlags &newFlags):
    windowPos(newPos),
    buttonSize(newSize),
    windowFlags(newFlags) {
    buttonLabel.text = newLabel;
}

void S2DButton::setButtonColorIdle(const S2DVector4<float> &newColor) {
    buttonColorIdle = newColor;
}

void S2DButton::setButtonColorHovered(const S2DVector4<float> &newColor) {
    buttonColorHovered = newColor;
}

void S2DButton::setButtonColorPressed(const S2DVector4<float> &newColor) {
    buttonColorPressed = newColor;
}

void S2DButton::setButtonFont(const std::string& fontPath, float fontSize) {
    buttonLabel.fontSource = fontPath;
    buttonLabel.textSize = fontSize;
}

void S2DButton::Render(const std::shared_ptr<S2DRenderContext>& renderContext) {
    auto convertedPos = renderContext->logicalToWindow(windowPos);
    auto convertedSize = renderContext->logicalToWindow(buttonSize);
    float convertedFontSize = renderContext->logicalToWindow(S2DVector2<float>(0, buttonLabel.textSize)).y;

    ImGui::SetNextWindowPos(ImVec2(convertedPos.x, convertedPos.y));
    ImGui::SetNextWindowSize(ImVec2(convertedSize.x, convertedSize.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(buttonColorIdle.x, buttonColorIdle.y, buttonColorIdle.z, buttonColorIdle.w));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonColorHovered.x, buttonColorHovered.y, buttonColorHovered.z, buttonColorHovered.w));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonColorPressed.x, buttonColorPressed.y, buttonColorPressed.z, buttonColorPressed.w));

    ImFont* buttonFont = nullptr;
    if (!buttonLabel.fontSource.empty() && convertedFontSize != 0) {
        buttonFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(buttonLabel.fontSource.c_str(), convertedFontSize);
        ImGui::PushFont(buttonFont);
    }

    ImGui::Begin(buttonLabel.fontSource.c_str(), nullptr, windowFlags);

    if (ImGui::Button(buttonLabel.text.c_str(), ImVec2(convertedSize.x, convertedSize.y)) && onClickCallback) {
        onClickCallback();
    }

    ImGui::End();
    if (buttonFont != nullptr) {
        ImGui::PopFont();
    }
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
}

void S2DButton::setOnClickCallback(const std::function<void()> &newCallback) {
    onClickCallback = newCallback;
}