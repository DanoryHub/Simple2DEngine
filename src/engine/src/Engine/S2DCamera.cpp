//
// Created by IvanMiatselski on 29.07.2026.
//

#include "Engine/S2DCamera.hpp"

namespace S2D {

Camera::Camera() {
    cameraPosition = S2D::Vector2<float>(0.f, 0.f);
}

Camera::~Camera() {}

S2D::Vector2<float> Camera::getPosition() const {
    return cameraPosition;
}

void Camera::setPosition(const S2D::Vector2<float>& value) {
    cameraPosition.x = value.x;
    cameraPosition.y = value.y;
}

S2D::Vector2<float> Camera::getScale() const {
    return cameraScale;
}

void Camera::setScale(const S2D::Vector2<float>& value) {
    cameraScale.x = value.x;
    cameraScale.y = value.y;
}

float Camera::getRotation() const {
    return cameraRotation;
}

void Camera::setRotation(float value) {
    cameraRotation = value;
}

} // namespace S2D
