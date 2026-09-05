//
// Created by ivan_miatselski on 2026-08-31.
//

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DHelpers.hpp"

#include <iostream>

S2DVector4<float> BoundingBox::getPoints() {
    return S2DVector4<float>(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
}

S2DCollidable::S2DCollidable():boundingBox(BoundingBox()) {}

S2DVector4<float> S2DCollidable::getBoundingBoxDimensions() {
    return boundingBox.getPoints();
}

void S2DCollidable::setCallback(const CollisionCallbackType callbackType,
                                std::function<void(std::shared_ptr<S2DGameObject>& )> callback) {
    callbacks[callbackType] = std::move(callback);
}

void S2DCollidable::executeCallback(CollisionCallbackType callbackType, std::shared_ptr<S2DGameObject>& otherObject) {
    callbacks[callbackType](otherObject);
}

void S2DCollidable::testLog() {
    std::cout << "One Collidable check" << std::endl;
}