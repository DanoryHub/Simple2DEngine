//
// Created by IvanMiatselski on 08.07.2026.
//

#include "Engine/S2DPlaceable.hpp"

#include <iostream>

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DTexture.hpp"

#include "SDL3/SDL.h"

namespace S2D {

Placeable::Placeable() = default;

S2D::Vector2<float> Placeable::GetPosition() const {
    return position;
}

void Placeable::SetPosition(const S2D::Vector2<float> &newPosition) {
    position = newPosition;
}

S2D::Vector2<float> Placeable::GetScale() const {
    return scale;
}

void Placeable::SetScale(const S2D::Vector2<float> &newScale) {
    scale = newScale;
}

float Placeable::GetRotation() const {
    return rotation;
}

void Placeable::SetRotation(const float newRotation) {
    rotation = newRotation;
}

} // namespace S2D
