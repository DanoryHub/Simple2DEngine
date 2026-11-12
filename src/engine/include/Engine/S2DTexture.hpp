//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ENGINE_S2DTEXTURE_HPP
#define ENGINE_S2DTEXTURE_HPP

#include "Engine/S2DHelpers.hpp"

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

S2DENGINE_NAMESPACE_BEGIN

class Texture {
protected:
    SDL_Texture *texture;
    std::string texturePath;

    int textureWidth;
    int textureHeight;

public:
    Texture(SDL_Renderer* renderer, const std::string& tPath);
    ~Texture();

    void Draw(SDL_Renderer* renderer, float x, float y,
        float scaleX = 1, float scaleY = 1,
        float rotation = 0) const;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DTEXTURE_HPP
