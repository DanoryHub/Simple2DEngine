//
// Created by IvanMiatselski on 08.07.2026.
//

#include "../../include/Engine/S2DTexture.hpp"
#include "SDL3_image/SDL_image.h"


S2DTexture::S2DTexture(SDL_Renderer* currRenderer, const std::string &tPath):
    renderer(currRenderer),
    texturePath(tPath)
{
    SDL_Surface* surface = IMG_Load(texturePath.c_str());

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

void S2DTexture::Draw(const float x, const float y,
    const float scaleX, const float scaleY,
    const float rotation) const {
    float newWidth = (float)textureWidth * scaleY;
    float newHeight = (float)textureHeight * scaleX;
    SDL_FRect dstRect;
    dstRect.x = x - newWidth / 2.f;
    dstRect.y = y - newHeight / 2.f;
    dstRect.w = newWidth;
    dstRect.h = newHeight;

    SDL_FPoint center{dstRect.w / 2.f, dstRect.h / 2.f};
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, rotation, &center, SDL_FLIP_NONE);
}
