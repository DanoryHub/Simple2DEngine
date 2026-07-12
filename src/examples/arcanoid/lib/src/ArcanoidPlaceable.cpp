//
// Created by IvanMiatselski on 09.07.2026.
//

#include "../include/Arcanoid/ArcanoidPlaceable.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <ostream>

#include "Engine/S2DVector2.hpp"

void ArcanoidPlaceable::Iterate(float deltaTime) {
    S2DPlaceable::Iterate(deltaTime);

    position += speed * deltaTime;

    constexpr float PI = 3.14;
    using namespace std::chrono;
    auto now = high_resolution_clock::now().time_since_epoch();
    float timeInSeconds = duration_cast<duration<float>>(now).count();

    float sinX = std::sin(2.f * PI * 1.f * timeInSeconds);
    float scaleFactor = sinX * .5f + 1.f;
    scale = baseScale * scaleFactor;
    rotation = 360.f * scaleFactor;
    std::cout << scaleFactor << " " << deltaTime << std::endl;
}
