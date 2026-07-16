//
// Created by IvanMiatselski on 08.07.2026.
//

#include "Engine/S2DTexture.hpp"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

#include <iostream>


S2DTexture::S2DTexture(SDL_Renderer* newRenderer, const std::string &tPath):
    texturePath(tPath)
{
    renderer = newRenderer;

    if (renderer == nullptr) {
        std::cout << "Renderer is not valid" << std::endl;
    }

    SDL_Surface* surface = IMG_Load(texturePath.c_str());

    if (surface == nullptr) {
        SDL_Log("Cant load png with path %s", texturePath.c_str());
        textureWidth = 0;
        textureHeight = 0;
        texture = nullptr;
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

void S2DTexture::SetRenderer(SDL_Renderer *newRenderer) {
    renderer = newRenderer;
    SDL_SetRenderTarget(renderer, texture);
}


void S2DTexture::Draw(const float x, const float y,
    const float scaleX, const float scaleY,
    const float rotation) const {

    const float newWidth = static_cast<float>(textureWidth) * scaleX;
    const float newHeight = static_cast<float>(textureHeight) * scaleY;
    SDL_FRect dstRect;
    dstRect.x = x - newWidth / 2.f;
    dstRect.y = y - newHeight / 2.f;
    dstRect.w = newWidth;
    dstRect.h = newHeight;

    SDL_FPoint center{dstRect.w / 2.f, dstRect.h / 2.f};
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, rotation, &center, SDL_FLIP_NONE);
}
