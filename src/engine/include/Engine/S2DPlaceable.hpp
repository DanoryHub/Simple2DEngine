//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ARCANOID_S2DPLACEABLE_HPP
#define ARCANOID_S2DPLACEABLE_HPP

#include <string>

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DGameObject.hpp"

class SDL_Renderer;

class S2DTexture;

class S2DPlaceable: public S2DGameObject{
protected:
    S2DTexture* texture;
    S2DVector2<float> position = S2DVector2<float>(0.f, 0.f);
public:
    S2DPlaceable();
    S2DPlaceable(SDL_Renderer* newRenderer, const std::string& texturePath);
    S2DPlaceable(S2DTexture* newTexture);

    void Iterate(float deltaTime) override;

};


#endif //ARCANOID_S2DPLACEABLE_HPP