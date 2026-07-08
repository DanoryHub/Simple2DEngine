//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ARCANOID_S2DPLACEABLE_HPP
#define ARCANOID_S2DPLACEABLE_HPP

#include <string>

#include "SDL3/SDL.h"

#include "S2DGameObject.hpp"

class S2DTexture;

class S2DPlaceable: public S2DGameObject{
protected:
    S2DTexture* texture;
public:
    S2DPlaceable(SDL_Renderer* currRenderer, const std::string& texturePath);
    S2DPlaceable(S2DTexture* newTexture);

    virtual void Iterate(float deltaTime) override;

};


#endif //ARCANOID_S2DPLACEABLE_HPP