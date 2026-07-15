//
// Created by IvanMiatselski on 08.07.2026.
//

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DTexture.hpp"

#include "SDL3/SDL.h"

S2DPlaceable::S2DPlaceable() {
    texture = nullptr;
}

S2DPlaceable::S2DPlaceable(S2DTexture *newTexture):
    texture(newTexture)
{}

S2DVector2<float> S2DPlaceable::GetPosition() const {
    return position;
}

void S2DPlaceable::SetPosition(const S2DVector2<float> &newPosition) {
    position = newPosition;
}

S2DVector2<float> S2DPlaceable::GetScale() const {
    return scale;
}

void S2DPlaceable::SetScale(const S2DVector2<float> &newScale) {
    scale = newScale;
}

float S2DPlaceable::GetRotation() const {
    return rotation;
}

void S2DPlaceable::SetRotation(const float newRotation) {
    rotation = newRotation;
}

S2DPlaceable::S2DPlaceable(const std::string& texturePath) {
    texture = new S2DTexture(texturePath);
}

void S2DPlaceable::Iterate(float deltaTime) {
    if (texture != nullptr) {
        texture->Draw(position.x, position.y, scale.x, scale.y, rotation);
    }
}


