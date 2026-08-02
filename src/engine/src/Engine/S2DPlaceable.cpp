//
// Created by IvanMiatselski on 08.07.2026.
//

#include "Engine/S2DPlaceable.hpp"

#include <iostream>

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DTexture.hpp"

#include "SDL3/SDL.h"

S2DPlaceable::S2DPlaceable() = default;
S2DPlaceable::~S2DPlaceable() = default;

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

S2DPlaceable::S2DPlaceable(const std::string& newTexturePath) {
    texturePath = newTexturePath;
}

void S2DPlaceable::Render(S2DRenderContext* renderContext) {
    renderContext->drawTexture(texturePath, position, scale, rotation);
}

