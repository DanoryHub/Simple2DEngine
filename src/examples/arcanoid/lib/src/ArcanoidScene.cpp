//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DButton.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DVector4.hpp"

#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

#include <iostream>


void ArcanoidScene::buttonCallback() {
    std::cout << "Callback working" << std::endl;
}

ArcanoidScene::ArcanoidScene(): S2DGameScene() {
    testPlaceable = std::make_shared<ArcanoidPlaceable>("./assets/Bug.png");
    testButton = std::make_shared<S2DButton>("Quit", S2DVector2<float>(1920/4, 1080/4), S2DVector2<float>(100, 100));
    testButton->setButtonColorIdle(S2DVector4<float>(1, 0, 0, 1));
    testButton->setButtonColorHovered(S2DVector4<float>(0, 1, 0, 1));
    testButton->setButtonColorHovered(S2DVector4<float>(0, 0, 1, 1));
    testButton->setOnClickCallback(methodCallback(buttonCallback));
    registerGameObject(testPlaceable);
    registerGameObject(testButton);

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