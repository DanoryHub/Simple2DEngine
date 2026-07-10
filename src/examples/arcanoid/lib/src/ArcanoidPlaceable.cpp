//
// Created by IvanMiatselski on 09.07.2026.
//

#include "../include/Arcanoid/ArcanoidPlaceable.hpp"

#include "Engine/S2DVector2.hpp"

void ArcanoidPlaceable::Iterate(float deltaTime) {
    S2DPlaceable::Iterate(deltaTime);

    position += speed * deltaTime;
}
