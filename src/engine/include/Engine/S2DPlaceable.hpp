//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ARCANOID_S2DPLACEABLE_HPP
#define ARCANOID_S2DPLACEABLE_HPP

#include <string>

#include "SDL3/SDL.h"

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DGameObject.hpp"

class S2DTexture;

class S2DPlaceable: public S2DGameObject{
protected:
    S2DTexture* texture;
    S2DVector2<int>* position = new S2DVector2<int>(0, 0);
public:
    S2DPlaceable(SDL_Renderer* currRenderer, const std::string& texturePath);
    S2DPlaceable(S2DTexture* newTexture);

    void Iterate(float deltaTime) override;

};


#endif //ARCANOID_S2DPLACEABLE_HPP