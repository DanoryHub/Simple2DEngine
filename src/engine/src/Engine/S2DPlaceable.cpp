//
// Created by IvanMiatselski on 08.07.2026.
//

#include "../../include/Engine/S2DPlaceable.hpp"

#include "../include/Engine/S2DTexture.hpp"


S2DPlaceable::S2DPlaceable(S2DTexture *newTexture):
    texture(newTexture)
{}

S2DPlaceable::S2DPlaceable(SDL_Renderer *currRenderer, const std::string& texturePath) {
    texture = new S2DTexture(currRenderer, texturePath);
}

void S2DPlaceable::Iterate(float deltaTime) {

}
