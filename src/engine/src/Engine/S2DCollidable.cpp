//
// Created by ivan_miatselski on 2026-08-31.
//

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DHelpers.hpp"

#include "SDL3/SDL.h"

#include <iostream>

namespace S2D {

S2D::Vector4<float> BoundingBox::getWorldPoints() const {
    return S2D::Vector4<float>(pos.x - size.x / 2 , pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2);
}

S2D::Vector4<float> BoundingBox::getPoints(const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale, float screenWidth, float screenHeight) const {
    S2D::Vector4<float> world = getWorldPoints();
    return S2D::Vector4<float>(
        (world.x - cameraPos.x) * cameraScale.x + screenWidth / 2.0f,
        (world.y - cameraPos.y) * cameraScale.y + screenHeight / 2.0f,
        (world.z - cameraPos.x) * cameraScale.x + screenWidth / 2.0f,
        (world.w - cameraPos.y) * cameraScale.y + screenHeight / 2.0f
    );
}

Collidable::Collidable():boundingBox(BoundingBox()) {}

S2D::Vector4<float> Collidable::getBoundingBoxDimensions() {
    return boundingBox.getWorldPoints();
}

void Collidable::setCallback(const CollisionCallbackType callbackType,
                                std::function<void(std::shared_ptr<S2D::GameObject>& )> callback) {
    callbacks[callbackType] = std::move(callback);
}

void Collidable::executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2D::GameObject>& otherObject) {
    auto it = callbacks.find(callbackType);
    if (it != callbacks.end() && it->second) {
        it->second(otherObject);
    }
}

void Collidable::setBBPos(const S2D::Vector2<float>& newPos) {
    boundingBox.pos = newPos;
}

S2D::Vector2<float> Collidable::getBBPos() {
    return boundingBox.pos;
}

bool Collidable::checkCollidableAgainstThisBB(const std::shared_ptr<Collidable> &collidable) {
    S2D::Vector4<float> a = boundingBox.getWorldPoints();
    S2D::Vector4<float> b = collidable->boundingBox.getWorldPoints();

    return a.x <= b.z && a.z >= b.x &&
           a.y <= b.w && a.w >= b.y;
}

void Collidable::setBBSize(const S2D::Vector2<float> &newSize) {
    boundingBox.size = newSize;
}

void Collidable::transformBBToScreenSpace(const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale, float screenWidth, float screenHeight) {
    S2D::Vector4<float> screen = boundingBox.getPoints(cameraPos, cameraScale, screenWidth, screenHeight);
    boundingBox.pos = S2D::Vector2<float>((screen.x + screen.z) / 2.f, (screen.y + screen.w) / 2.f);
    boundingBox.size = S2D::Vector2<float>(screen.z - screen.x, screen.w - screen.y);
}

void Collidable::drawDebugBox(SDL_Renderer* renderer) {
    S2D::Vector4<float> screen = boundingBox.getWorldPoints();
    SDL_FRect redRect{ screen.x, screen.y, screen.z - screen.x, screen.w - screen.y };

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &redRect);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);

}

} // namespace S2D
