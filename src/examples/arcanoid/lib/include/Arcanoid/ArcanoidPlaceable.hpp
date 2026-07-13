//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ARCANOID_ARCANOIDPLACEABLE_HPP
#define ARCANOID_ARCANOIDPLACEABLE_HPP
#include "Engine/S2DPlaceable.hpp"


class ArcanoidPlaceable: public S2DPlaceable {
protected:
    float speed = 90.f;

public:
    using S2DPlaceable::S2DPlaceable;

    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDPLACEABLE_HPP