//
// Created by IvanMiatselski on 09.08.2026.
//

#ifndef ENGINE_S2DBUTTON_HPP
#define ENGINE_S2DBUTTON_HPP

#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DVector4.hpp"

#include "imgui.h"

#include <functional>
#include <string>

#define methodCallback(methodName) ([this]() { this->methodName(); })


class S2DButton: public S2DGameObject, public S2DIRenderable{
public:
    S2DButton() = default;
    S2DButton(const std::string& newLabel, const ImGuiWindowFlags& newFlags);
    S2DButton(const std::string& newLabel, const S2DVector2<float>& newPos, const S2DVector2<float>& newSize);
    S2DButton(const std::string& newLabel, const S2DVector2<float>& newPos, const S2DVector2<float>& newSize, const ImGuiWindowFlags& newFlags);
    ~S2DButton() override = default;

    void Render(const std::shared_ptr<S2DRenderContext> &renderContext) override;
    void setOnClickCallback(const std::function<void()> &newCallback);

    void setButtonColorIdle(const S2DVector4<float>& newColor);
    void setButtonColorHovered(const S2DVector4<float>& newColor);
    void setButtonColorPressed(const S2DVector4<float>& newColor);

    void setButtonFont(const std::string& fontPath, float fontSize);

protected:
    std::string buttonLabel;
    std::string buttonFontPath;
    float buttonFontSize;
    S2DVector2<float> windowPos = S2DVector2<float>(0, 0);
    S2DVector2<float> buttonSize = S2DVector2<float>(0, 0);
    S2DVector4<float> buttonColorIdle = S2DVector4<float>(0.2f, 0.6f, 0.4f, 1.f);
    S2DVector4<float> buttonColorHovered = S2DVector4<float>(0.3f, 0.7f, 0.5f, 1.0f);
    S2DVector4<float> buttonColorPressed = S2DVector4<float>(0.1f, 0.5f, 0.3f, 1.0f);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoScrollbar;
    std::function<void()> onClickCallback;
};


#endif //ENGINE_S2DBUTTON_HPP