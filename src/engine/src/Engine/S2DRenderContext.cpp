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

S2DENGINE_NAMESPACE_BEGIN

RenderContext::RenderContext() {
    renderer = nullptr;
}

RenderContext::~RenderContext() {
    clearTextureCache();
}

void RenderContext::registerRenderer(SDL_Renderer* newRenderer) {
    renderer = newRenderer;
    clearTextureCache();
}

void RenderContext::registerCamera(const std::shared_ptr<S2D::Camera>& newCamera) {
    currCamera = newCamera;
}

void RenderContext::registerAudioSpec(SDL_AudioSpec *newAudioSpec) {
    audioSpec = newAudioSpec;
}

void RenderContext::setLogicalSize(int width, int height) {
    logicalWidth = width;
    logicalHeight = height;
}

S2D::Vector2<float> RenderContext::logicalToWindow(const S2D::Vector2<float>& logicalPos) const {
    int outputW = 0;
    int outputH = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &outputW, &outputH);
    return S2D::Vector2<float>(
        logicalPos.x * static_cast<float>(outputW) / static_cast<float>(logicalWidth),
        logicalPos.y * static_cast<float>(outputH) / static_cast<float>(logicalHeight)
    );
}

void RenderContext::clearTextureCache() {
    textureCache.clear();
}

S2D::Texture* RenderContext::getTexture(const std::string &tPath) {
    if (!textureCache.contains(tPath)) {
        textureCache[tPath] = std::move(std::make_unique<S2D::Texture>(renderer, tPath));
    }

    return textureCache[tPath].get();
}

SDL_Renderer* RenderContext::getRenderer() {
    return renderer;
}

S2D::Vector2<float> RenderContext::getCameraPosition() {
    auto cam = currCamera.lock();
    if (!cam) return S2D::Vector2<float>(0.f, 0.f);
    return cam->getPosition();
}

S2D::Vector2<float> RenderContext::getCameraScale() {
    auto cam = currCamera.lock();
    if (!cam) return S2D::Vector2<float>(1.f, 1.f);
    return cam->getScale();
}

int RenderContext::getLogicalWidth() const {
    return logicalWidth;
}

int RenderContext::getLogicalHeight() const {
    return logicalHeight;
}

void RenderContext::drawTexture(const std::string &tPath,  const S2D::Vector2<float> &position, const S2D::Vector2<float> &scale, float rotation) {
    if (renderer == nullptr) {
        std::cerr << "No renderer set in renderContext" << std::endl;
        return;
    }

    auto cam = currCamera.lock();
    if (!cam) {
        std::cerr << "No camera registered/available in renderContext" << std::endl;
        return;
    }

    S2D::Vector2<float> camPos = cam->getPosition();
    S2D::Vector2<float> camScale = cam->getScale();
    float camRot = cam->getRotation();

    int windowWidth = 0;
    int windowHeight = 0;

    SDL_GetCurrentRenderOutputSize(renderer, &windowWidth, &windowHeight);
    auto screenWidth = static_cast<float>(windowWidth);
    auto screenHeight = static_cast<float>(windowHeight);

    auto T_screen= S2D::Matrix<float>::Translation(screenWidth / 2.0f, screenHeight / 2.0f);
    auto S_zoom = S2D::Matrix<float>::Scaling(camScale.x, camScale.y);
    auto R_rot= S2D::Matrix<float>::Rotation(camRot);
    auto T_world= S2D::Matrix<float>::Translation(-camPos.x, -camPos.y);

    S2D::Matrix<float> cameraMatrix = T_screen * S_zoom * R_rot * T_world;

    S2D::Vector2<float> screenPosition = cameraMatrix * position;
    S2D::Vector2<float> screenScale(scale.x * camScale.x, scale.y * camScale.y);

    float screenRotation = rotation + camRot;

    getTexture(tPath)->Draw(renderer, screenPosition.x, screenPosition.y, screenScale.x, screenScale.y, screenRotation);
}

S2DENGINE_NAMESPACE_END
