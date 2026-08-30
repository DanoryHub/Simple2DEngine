//
// Created by ivan_miatselski on 2026-08-30.
//

#include "Engine/S2DRenderable.hpp"
#include "Engine/S2DRenderContext.hpp"

S2DRenderable::~S2DRenderable() = default;

S2DRenderable::S2DRenderable(const std::string& newTexturePath) {
    texturePath = newTexturePath;
}

void S2DRenderable::Render(const std::shared_ptr<S2DRenderContext>& renderContext) {
    renderContext->drawTexture(texturePath, position, scale, rotation);
}