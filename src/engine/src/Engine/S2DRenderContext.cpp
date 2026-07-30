//
// Created by IvanMiatselski on 30.07.2026.
//
#include "Engine/S2DRenderContext.hpp"

#include <iostream>
#include <ostream>

#include "Engine/S2DTexture.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DCamera.hpp"

#include "SDL3/SDL.h"


S2DRenderContext::S2DRenderContext() {
    renderer = nullptr;
    currCamera = new S2DCamera();
}

S2DRenderContext::~S2DRenderContext() {
    delete renderer;
    delete currCamera;
    clearTextureCache();
}

void S2DRenderContext::registerRenderer(SDL_Renderer* newRenderer) {
    delete renderer;
    renderer = newRenderer;
    clearTextureCache();
}

void S2DRenderContext::registerCamera(S2DCamera* newCamera) {
    delete currCamera;
    currCamera = newCamera;
}

void S2DRenderContext::clearTextureCache() {
    for (auto pair: textureCache) {
        delete pair.second;
    }
    textureCache.clear();
}

S2DTexture* S2DRenderContext::getTexture(const std::string &tPath) {
    if (textureCache.find(tPath) != textureCache.end()) {
        return textureCache[tPath];
    }

    S2DTexture *texture = new S2DTexture(renderer, tPath);
    textureCache[tPath] = texture;
    return texture;
}

void S2DRenderContext::drawTexture(const std::string &tPath,  const S2DVector2<float> &position, const S2DVector2<float> &scale, float rotation) {
    if (renderer == nullptr) {
        std::cerr << "No renderer set in renderContext" << std::endl;
    }
    getTexture(tPath)->Draw(renderer, position.x, position.y, scale.x, scale.y, rotation);
}
