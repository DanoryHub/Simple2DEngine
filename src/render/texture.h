//
// Created by IvanMiatselski on 26.05.2026.
//

#ifndef SIMPLE2DENGINE_TEXTURE_H
#define SIMPLE2DENGINE_TEXTURE_H

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"
#include <string>


class S2DTexture {
public:
    S2DTexture();

    ~S2DTexture();

    bool loadFromFile(std::string texturePath);

    void destroy();

    void render(float x, float y);

    int getWidth();

    int getHeight();

    bool isLoaded();

private:
    SDL_Texture *texture;

    int tWidth;
    int tHeight;
};


#endif //SIMPLE2DENGINE_TEXTURE_H