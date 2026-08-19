//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ARCANOID_ARCANOIDPLACEABLE_HPP
#define ARCANOID_ARCANOIDPLACEABLE_HPP

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DMovable.hpp"


class ArcanoidPlaceable: public S2DMovable{
protected:
    float speed = 90.f;

public:
    ArcanoidPlaceable(const std::string& newTexturePath);

    void Iterate(float deltaTime) override;
    void moveForward();
};


#endif //ARCANOID_ARCANOIDPLACEABLE_HPP