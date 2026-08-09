//
// Created by IvanMiatselski on 09.08.2026.
//

#ifndef ENGINE_S2DBUTTON_HPP
#define ENGINE_S2DBUTTON_HPP

#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DVector2.hpp"

#include "imgui.h"

#include <string>

class S2DButton: public S2DGameObject, public S2DIRenderable{
public:
    S2DButton() = default;
    S2DButton(const std::string& newLabel, const ImGuiWindowFlags& newFlags);
    S2DButton(const std::string& newLabel, const S2DVector2<float>& newPos);
    S2DButton(const std::string& newLabel, const S2DVector2<float>& newPos, const ImGuiWindowFlags& newFlags);
    ~S2DButton() override = default;

    void Render(const std::shared_ptr<S2DRenderContext> &renderContext) override;

protected:
    std::string buttonLabel;
    S2DVector2<float> windowPos = S2DVector2<float>(0, 0);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoScrollbar;
};


#endif //ENGINE_S2DBUTTON_HPP