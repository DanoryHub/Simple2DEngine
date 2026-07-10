//
// Created by IvanMiatselski on 08.07.2026.
//

#include "../../include/Engine/S2DPlaceable.hpp"
#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DTexture.hpp"

#include "SDL3/SDL.h"

S2DPlaceable::S2DPlaceable() {
    texture = nullptr;
}
S2DPlaceable::S2DPlaceable(S2DTexture *newTexture):
    texture(newTexture)
{}

S2DPlaceable::S2DPlaceable(SDL_Renderer* newRenderer, const std::string& texturePath) {
    texture = new S2DTexture(newRenderer, texturePath);
}

void S2DPlaceable::Iterate(float deltaTime) {
    if (texture != nullptr) {
        texture->Draw(position.x, position.y);
    }
}
