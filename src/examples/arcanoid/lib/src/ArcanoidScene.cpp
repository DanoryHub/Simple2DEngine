//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DCamera.hpp"

#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

#include "SDL3/SDL.h"

ArcanoidScene::ArcanoidScene(): S2DGameScene() {
    testPlaceable = std::make_shared<ArcanoidPlaceable>("./assets/Bug.png");
    registerGameObject(testPlaceable);

    mainSceneCamera = std::make_shared<S2DCamera>();
}

void ArcanoidScene::Iterate(float deltaTime) {
    S2DGameScene::Iterate(deltaTime);

    // S2DVector2<float> direction =  mainSceneCamera->getPosition()- S2DVector2<float>(1920.f, 1080.f);
    // S2DVector2<float> position = mainSceneCamera->getPosition() + direction.Normalize() * 50 * deltaTime;
    // mainSceneCamera->setPosition(&position);
    //
    // S2DVector2<float> newScale = mainSceneCamera->getScale() + 0.1f * deltaTime;
    // mainSceneCamera->setScale(&newScale);
    //
    // float newRotation = mainSceneCamera->getRotation() + -15 * deltaTime;
    // mainSceneCamera->setRotation(newRotation);
}