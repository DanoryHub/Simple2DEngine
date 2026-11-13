//
// Created by IvanMiatselski on 09.08.2026.
//

#ifndef ENGINE_S2DBUTTON_HPP
#define ENGINE_S2DBUTTON_HPP

#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DVector4.hpp"
#include "Engine/S2DLabel.hpp"

#include "imgui.h"

#include <functional>
#include <string>

namespace S2D {

class RenderContext;

class Button: virtual public S2D::GameObject, public S2D::IRenderable{
public:
    Button() = default;
    Button(const std::string& newLabel, const ImGuiWindowFlags& newFlags);
    Button(const std::string& newLabel, const S2D::Vector2<float>& newPos, const S2D::Vector2<float>& newSize);
    Button(const std::string& newLabel, const S2D::Vector2<float>& newPos, const S2D::Vector2<float>& newSize, const ImGuiWindowFlags& newFlags);
    ~Button() override = default;

    void Render(const std::shared_ptr<S2D::RenderContext> &renderContext) override;
    void setOnClickCallback(const std::function<void()> &newCallback);

    void setButtonColorIdle(const S2D::Vector4<float>& newColor);
    void setButtonColorHovered(const S2D::Vector4<float>& newColor);
    void setButtonColorPressed(const S2D::Vector4<float>& newColor);

    void setButtonFont(const std::string& fontPath, float fontSize);

protected:
    S2D::Label buttonLabel;
    S2D::Vector2<float> windowPos = S2D::Vector2<float>(0, 0);
    S2D::Vector2<float> buttonSize = S2D::Vector2<float>(0, 0);
    S2D::Vector4<float> buttonColorIdle = S2D::Vector4<float>(0.2f, 0.6f, 0.4f, 1.f);
    S2D::Vector4<float> buttonColorHovered = S2D::Vector4<float>(0.3f, 0.7f, 0.5f, 1.0f);
    S2D::Vector4<float> buttonColorPressed = S2D::Vector4<float>(0.1f, 0.5f, 0.3f, 1.0f);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoScrollbar;
    std::function<void()> onClickCallback;
};

} // namespace S2D

#endif //ENGINE_S2DBUTTON_HPP
