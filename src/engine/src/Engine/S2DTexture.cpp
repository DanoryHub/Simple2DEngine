//
// Created by IvanMiatselski on 08.07.2026.
//

#include "../../include/Engine/S2DTexture.hpp"


S2DTexture::S2DTexture(SDL_Renderer* currRenderer, const std::string &tPath):
    texturePath(tPath),
    renderer(currRenderer)
{
    SDL_Surface* surface = SDL_LoadPNG(texturePath.c_str());

    if (surface == nullptr) {
        SDL_Log("Cant load png with path %s", texturePath.c_str());
        return;
    }

    textureWidth = surface->w;
    textureHeight = surface->h;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

S2DTexture::~S2DTexture() {
    SDL_DestroyTexture(texture);
}

void S2DTexture::Draw(const float x, const float y) const {
    SDL_FRect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = static_cast<float>(textureWidth);
    dstRect.h = static_cast<float>(textureHeight);

    SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}
