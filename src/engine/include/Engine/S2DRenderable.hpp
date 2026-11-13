//
// Created by ivan_miatselski on 2026-08-30.
//

#ifndef ENGINE_S2DRENDERABLE_HPP
#define ENGINE_S2DRENDERABLE_HPP

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DIRenderable.hpp"

#include <string>

namespace S2D {

class RenderContext;

class Renderable: public S2D::Placeable, public S2D::IRenderable {
protected:
    std::string texturePath;

public:
    Renderable(const std::string &newTexturePath);
    ~Renderable() override;

    void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) override;
};

} // namespace S2D

#endif //ENGINE_S2DRENDERABLE_HPP
