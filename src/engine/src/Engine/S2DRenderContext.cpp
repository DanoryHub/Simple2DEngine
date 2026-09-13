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

void S2DRenderContext::registerAudioSpec(SDL_AudioSpec *newAudioSpec) {
    audioSpec = newAudioSpec;
}

void S2DRenderContext::setLogicalSize(int width, int height) {
    logicalWidth = width;
    logicalHeight = height;
}

S2DVector2<float> S2DRenderContext::logicalToWindow(const S2DVector2<float>& logicalPos) const {
    int outputW = 0;
    int outputH = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &outputW, &outputH);
    return S2DVector2<float>(
        logicalPos.x * static_cast<float>(outputW) / static_cast<float>(logicalWidth),
        logicalPos.y * static_cast<float>(outputH) / static_cast<float>(logicalHeight)
    );
}

void S2DRenderContext::clearTextureCache() {
    textureCache.clear();
}

S2DTexture* S2DRenderContext::getTexture(const std::string &tPath) {
    if (!textureCache.contains(tPath)) {
        textureCache[tPath] = std::move(std::make_unique<S2DTexture>(renderer, tPath));
    }

    return textureCache[tPath].get();
}

SDL_Renderer* S2DRenderContext::getRenderer() {
    return renderer;
}

S2DVector2<float> S2DRenderContext::getCameraPosition() {
    auto cam = currCamera.lock();
    if (!cam) return S2DVector2<float>(0.f, 0.f);
    return cam->getPosition();
}

S2DVector2<float> S2DRenderContext::getCameraScale() {
    auto cam = currCamera.lock();
    if (!cam) return S2DVector2<float>(1.f, 1.f);
    return cam->getScale();
}

int S2DRenderContext::getLogicalWidth() const {
    return logicalWidth;
}

int S2DRenderContext::getLogicalHeight() const {
    return logicalHeight;
}

void S2DRenderContext::drawTexture(const std::string &tPath,  const S2DVector2<float> &position, const S2DVector2<float> &scale, float rotation) {
    if (renderer == nullptr) {
        std::cerr << "No renderer set in renderContext" << std::endl;
        return;
    }

    auto cam = currCamera.lock();
    if (!cam) {
        std::cerr << "No camera registered/available in renderContext" << std::endl;
        return;
    }

    S2DVector2<float> camPos = cam->getPosition();
    S2DVector2<float> camScale = cam->getScale();
    float camRot = cam->getRotation();

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
