//
// Created by IvanMiatselski on 29.07.2026.
//

#include "Engine/S2DCamera.hpp"


S2DCamera::S2DCamera() {
    cameraPosition = S2DVector2<float>(0.f, 0.f);
}

S2DCamera::~S2DCamera() {}

S2DVector2<float> S2DCamera::getPosition() const {
    return cameraPosition;
}

void S2DCamera::setPosition(const S2DVector2<float>* value) {
    cameraPosition.x = value->x;
    cameraPosition.y = value->y;
}

S2DVector2<float> S2DCamera::getScale() const {
    return cameraScale;
}

void S2DCamera::setScale(const S2DVector2<float>* value) {
    cameraScale.x = value->x;
    cameraScale.y = value->y;
}

float S2DCamera::getRotation() const {
    return cameraRotation;
}

void S2DCamera::setRotation(float value) {
    cameraRotation = value;
}