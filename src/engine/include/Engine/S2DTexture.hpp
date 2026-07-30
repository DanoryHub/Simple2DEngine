//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ENGINE_S2DTEXTURE_HPP
#define ENGINE_S2DTEXTURE_HPP

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class S2DTexture {
protected:
    SDL_Texture *texture;
    std::string texturePath;

    int textureWidth;
    int textureHeight;

public:
    S2DTexture(SDL_Renderer* renderer, const std::string& tPath);
    ~S2DTexture();

    void Draw(SDL_Renderer* renderer, float x, float y,
        float scaleX = 1, float scaleY = 1,
        float rotation = 0) const;
};


#endif //ENGINE_S2DTEXTURE_HPP