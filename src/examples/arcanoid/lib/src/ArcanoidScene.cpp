//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

#include "SDL3/SDL.h"

ArcanoidScene::ArcanoidScene(): S2DGameScene() {
    testPlaceable = new ArcanoidPlaceable("./assets/Bug.png");
    registerGameObject(testPlaceable);
}

void ArcanoidScene::Iterate(float deltaTime) {
    S2DGameScene::Iterate(deltaTime);
}