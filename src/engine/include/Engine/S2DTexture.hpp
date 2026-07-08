//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ARCANOID_S2DTEXTURE_HPP
#define ARCANOID_S2DTEXTURE_HPP

#include "SDL3/SDL.h"
#include "string"

class S2DTexture {
protected:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    std::string texturePath;

    int textureWidth;
    int textureHeight;

public:
    S2DTexture(SDL_Renderer* currRenderer, const std::string& tPath);
    ~S2DTexture();

    void Draw(const float x, const float y) const;
};


#endif //ARCANOID_S2DTEXTURE_HPP