//
// Created by IvanMiatselski on 09.07.2026.
//

#include "Arcanoid/ArcanoidPlaceable.hpp"

#include <chrono>
#include <cmath>

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DMatrix.hpp"

void ArcanoidPlaceable::Iterate(float deltaTime) {
    S2DPlaceable::Iterate(deltaTime);

    //position = S2DVector2<float>(1920.f/2, 1080.f/2);
    // S2DVector2<float> direction = S2DVector2<float>(1920.f, 1080.f) - position;
    //
    // position +=  direction.Normalize() * speed * deltaTime;
    //
    // constexpr float PI = 3.14;
    // auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    // float timeInSeconds = duration_cast<std::chrono::duration<float>>(now).count();
    //
    // float sinX = std::sin(2.f * PI * 1.f * timeInSeconds);
    // float scaleFactor = sinX * .5f + 1.f;
    // scale = baseScale * scaleFactor;
    // rotation = 360.f * scaleFactor;
}
