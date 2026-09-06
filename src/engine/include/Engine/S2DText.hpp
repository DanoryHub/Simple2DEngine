//
// Created by ivan_miatselski on 2026-08-17.
//

#ifndef ENGINE_S2DTEXT_H
#define ENGINE_S2DTEXT_H

#include "S2DLabel.hpp"
#include "S2DVector2.hpp"
#include "S2DGameObject.hpp"
#include "S2DIRenderable.hpp"

#include "imgui.h"

class S2DText: virtual public S2DGameObject, public S2DIRenderable {
public:
    S2DText() = default;
    S2DText(const std::string& newLabel, const ImGuiWindowFlags& newFlags);
    S2DText(const std::string& newLabel, const S2DVector2<float>& newPos, float newSize);
    S2DText(const std::string& newLabel, const S2DVector2<float>& newPos, float newSize, const ImGuiWindowFlags& newFlags);
    ~S2DText() override = default;

    void Render(const std::shared_ptr<S2DRenderContext> &renderContext) override;

    void setTextColor(const S2DVector4<float>& newColor);
    void setTextFont(const std::string& fontPath, float fontSize);
protected:
    void loadFont();
    S2DLabel textLabel;
    S2DVector2<float> windowPos = S2DVector2<float>(0, 0);
    ImFont* loadedFont = nullptr;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoScrollbar;
};


#endif //ENGINE_S2DTEXT_H
