//
// Created by IvanMiatselski on 29.07.2026.
//

#include "Engine/S2DCamera.hpp"


S2DCamera::S2DCamera() {
    cameraPosition = new S2DVector2<float>(0.f, 0.f);
}

S2DCamera::~S2DCamera() {
    delete cameraPosition;
}

S2DVector2<float>* S2DCamera::getCameraPosition() const {
    return cameraPosition;
}

void S2DCamera::setCameraPosition(const S2DVector2<float>* value) {
    cameraPosition->x = value->x;
    cameraPosition->y = value->y;
}