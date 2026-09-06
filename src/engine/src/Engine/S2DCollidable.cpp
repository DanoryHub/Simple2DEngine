//
// Created by ivan_miatselski on 2026-08-31.
//

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DHelpers.hpp"

#include "SDL3/SDL.h"

#include <iostream>

S2DVector4<float> BoundingBox::getWorldPoints() const {
    return S2DVector4<float>(pos.x - size.x / 2 , pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2);
}

S2DVector4<float> BoundingBox::getPoints(const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale, float screenWidth, float screenHeight) const {
    S2DVector4<float> world = getWorldPoints();
    return S2DVector4<float>(
        (world.x - cameraPos.x) * cameraScale.x + screenWidth / 2.0f,
        (world.y - cameraPos.y) * cameraScale.y + screenHeight / 2.0f,
        (world.z - cameraPos.x) * cameraScale.x + screenWidth / 2.0f,
        (world.w - cameraPos.y) * cameraScale.y + screenHeight / 2.0f
    );
}

S2DCollidable::S2DCollidable():boundingBox(BoundingBox()) {}

S2DVector4<float> S2DCollidable::getBoundingBoxDimensions() {
    return boundingBox.getWorldPoints();
}

void S2DCollidable::setCallback(const CollisionCallbackType callbackType,
                                std::function<void(std::shared_ptr<S2DGameObject>& )> callback) {
    callbacks[callbackType] = std::move(callback);
}

void S2DCollidable::executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2DGameObject>& otherObject) {
    callbacks[callbackType](otherObject);
}

void S2DCollidable::updateBBPos(const S2DVector2<float>& newPos) {
    boundingBox.pos = newPos;
}

void S2DCollidable::drawDebugBox(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale) {
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &windowWidth, &windowHeight);

    S2DVector4<float> screen = boundingBox.getPoints(cameraPos, cameraScale, static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    SDL_FRect redRect{ screen.x, screen.y, screen.z - screen.x, screen.w - screen.y };

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &redRect);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);

}