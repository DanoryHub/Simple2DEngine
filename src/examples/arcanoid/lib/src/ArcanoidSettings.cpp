//
// Created by IvanMiatselski on 30.06.2026.
//

#include "Arcanoid/ArcanoidSettings.hpp"

#include <memory>

std::shared_ptr<S2D::GameSettings> CreateGameSettings() {
    return std::make_shared<ArcanoidSettings>();
}

ArcanoidSettings::ArcanoidSettings() : S2D::GameSettings("assets/scenes.json") {}
