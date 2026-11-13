//
// Created by ivan_miatselski on 2026-08-30.
//

#include "Engine/S2DRenderable.hpp"
#include "Engine/S2DRenderContext.hpp"

namespace S2D {

Renderable::~Renderable() = default;

Renderable::Renderable(const std::string& newTexturePath) {
    texturePath = newTexturePath;
}

void Renderable::Render(const std::shared_ptr<S2D::RenderContext>& renderContext) {
    renderContext->drawTexture(texturePath, position, scale, rotation);
}

} // namespace S2D
