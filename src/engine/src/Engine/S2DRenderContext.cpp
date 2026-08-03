//
// Created by IvanMiatselski on 30.07.2026.
//
#include "Engine/S2DRenderContext.hpp"

#include <iostream>
#include <ostream>

#include "Engine/S2DTexture.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DMatrix.hpp"
#include "Engine/S2DCamera.hpp"

#include "SDL3/SDL.h"


S2DRenderContext::S2DRenderContext() {
    renderer = nullptr;
    currCamera = std::shared_ptr<S2DCamera>();
}

S2DRenderContext::~S2DRenderContext() {
    clearTextureCache();
}

void S2DRenderContext::registerRenderer(SDL_Renderer* newRenderer) {
    renderer = newRenderer;
    clearTextureCache();
}

void S2DRenderContext::registerCamera(const std::shared_ptr<S2DCamera>& newCamera) {
    currCamera = newCamera;
}

void S2DRenderContext::clearTextureCache() {
    for (const auto& pair: textureCache) {
        delete pair.second;
    }
    textureCache.clear();
}

S2DTexture* S2DRenderContext::getTexture(const std::string &tPath) {
    if (textureCache.find(tPath) != textureCache.end()) {
        return textureCache[tPath];
    }

    auto *texture = new S2DTexture(renderer, tPath);
    textureCache[tPath] = texture;
    return texture;
}

void S2DRenderContext::drawTexture(const std::string &tPath,  const S2DVector2<float> &position, const S2DVector2<float> &scale, float rotation) {
    if (renderer == nullptr) {
        std::cerr << "No renderer set in renderContext" << std::endl;
        return;
    }

    if (currCamera == nullptr) {
        std::cerr << "No camera registered in renderContext" << std::endl;
        return;
    }

    S2DVector2<float> camPos = currCamera->getPosition();
    S2DVector2<float> camScale = currCamera->getScale();
    float camRot = currCamera->getRotation();

    int windowWidth = 0;
    int windowHeight = 0;

    SDL_GetCurrentRenderOutputSize(renderer, &windowWidth, &windowHeight);
    auto screenWidth = static_cast<float>(windowWidth);
    auto screenHeight = static_cast<float>(windowHeight);

    auto T_screen= S2DMatrix<float>::Translation(screenWidth / 2.0f, screenHeight / 2.0f);
    auto S_zoom = S2DMatrix<float>::Scaling(camScale.x, camScale.y);
    auto R_rot= S2DMatrix<float>::Rotation(camRot);
    auto T_world= S2DMatrix<float>::Translation(-camPos.x, -camPos.y);

    S2DMatrix<float> cameraMatrix = T_screen * S_zoom * R_rot * T_world;

    S2DVector2<float> screenPosition = cameraMatrix * position;
    S2DVector2<float> screenScale(scale.x * camScale.x, scale.y * camScale.y);

    float screenRotation = rotation + camRot;

    getTexture(tPath)->Draw(renderer, screenPosition.x, screenPosition.y, screenScale.x, screenScale.y, screenRotation);
}
