//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DMainApp.hpp"

#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

ArcanoidScene::ArcanoidScene() {
    testPlaceable = new ArcanoidPlaceable("./assets/Bug.png");
    registerGameObject(testPlaceable);
}

void ArcanoidScene::Iterate(float deltaTime) {
    S2DGameScene::Iterate(deltaTime);
}