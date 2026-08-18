//
// Created by ivan_miatselski on 2026-08-17.
//

#include "Engine/S2DText.hpp"
#include "Engine/S2DRenderContext.hpp"

#include <string>
#include <cstdint>

S2DText::S2DText(const std::string& newLabel, const S2DVector2<float> &newPos, float newSize):
    windowPos(newPos) {
    textLabel.text = newLabel;
    textLabel.textSize = newSize;
}

S2DText::S2DText(const std::string& newLabel, const ImGuiWindowFlags &newFlags):
    windowFlags(newFlags) {
    textLabel.text = newLabel;
}

S2DText::S2DText(const std::string& newLabel, const S2DVector2<float> &newPos, float newSize, const ImGuiWindowFlags &newFlags):
    windowPos(newPos),
    windowFlags(newFlags) {
    textLabel.text = newLabel;
    textLabel.textSize = newSize;
}

void S2DText::setTextColor(const S2DVector4<float> &newColor) {
    textLabel.textColor = newColor;
}

void S2DText::setTextFont(const std::string& fontPath, float fontSize) {
    textLabel.textSize = fontSize;
    textLabel.fontSource = fontPath;
    loadFont();
}

void S2DText::loadFont() {
    if (loadedFont != nullptr || textLabel.fontSource.empty()) {
        return;
    }
    loadedFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(textLabel.fontSource.c_str(), textLabel.textSize);
}

void S2DText::Render(const std::shared_ptr<S2DRenderContext>& renderContext) {
    std::string windowName = "S2DText_" + std::to_string(reinterpret_cast<uintptr_t>(this));

    auto convertedPos = renderContext->logicalToWindow(windowPos);

    ImGui::SetNextWindowPos(ImVec2(convertedPos.x, convertedPos.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    if (loadedFont != nullptr) {
        ImGui::PushFont(loadedFont);
        loadedFont->Scale = renderContext->logicalToWindow(S2DVector2<float>(0, 1)).y;
    }

    ImGui::Begin(windowName.c_str(), nullptr, windowFlags);

    ImGui::TextColored(
        ImVec4(textLabel.textColor.x, textLabel.textColor.y, textLabel.textColor.z, textLabel.textColor.w),
        textLabel.text.c_str()
    );

    ImGui::End();
    if (loadedFont != nullptr) {
        ImGui::PopFont();
    }
    ImGui::PopStyleVar();
}