#include "Arkanoid/ArkanoidSettings.hpp"

#include <memory>

std::shared_ptr<S2D::GameSettings> CreateGameSettings() {
    return std::make_shared<ArkanoidSettings>();
}

ArkanoidSettings::ArkanoidSettings() : S2D::GameSettings("assets/scenes.json") {}
