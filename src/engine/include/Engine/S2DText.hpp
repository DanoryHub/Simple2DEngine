//
// Created by ivan_miatselski on 2026-08-17.
//

#ifndef ENGINE_S2DTEXT_H
#define ENGINE_S2DTEXT_H

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DLabel.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DVector4.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DIRenderable.hpp"

#include "imgui.h"

S2DENGINE_NAMESPACE_BEGIN

class RenderContext;

class Text: virtual public S2D::GameObject, public S2D::IRenderable {
public:
    Text() = default;
    Text(const std::string& newLabel, const ImGuiWindowFlags& newFlags);
    Text(const std::string& newLabel, const S2D::Vector2<float>& newPos, float newSize);
    Text(const std::string& newLabel, const S2D::Vector2<float>& newPos, float newSize, const ImGuiWindowFlags& newFlags);
    ~Text() override = default;

    void Render(const std::shared_ptr<S2D::RenderContext> &renderContext) override;

    void setTextColor(const S2D::Vector4<float>& newColor);
    void setTextFont(const std::string& fontPath, float fontSize);
protected:
    void loadFont();
    S2D::Label textLabel;
    S2D::Vector2<float> windowPos = S2D::Vector2<float>(0, 0);
    ImFont* loadedFont = nullptr;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoScrollbar;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DTEXT_H
