//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DText.hpp"
#include "Engine/S2DButton.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DMacros.hpp"
#include "Engine/S2DVector4.hpp"
#include "Engine/S2DSound.hpp"

#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

#include <iostream>


void ArcanoidScene::buttonCallback() {
    std::cout << "Callback working" << std::endl;
}

ArcanoidScene::ArcanoidScene(): S2D::GameScene() {
    testPlaceable = std::make_shared<ArcanoidPlaceable>("./assets/Bug.png");

    testButton = std::make_shared<S2D::Button>("Quit", S2D::Vector2<float>(1920/4, 1080/4), S2D::Vector2<float>(100, 100));
    testButton->setButtonColorIdle(S2D::Vector4<float>(1, 0, 0, 1));
    testButton->setButtonColorHovered(S2D::Vector4<float>(0, 1, 0, 1));
    testButton->setButtonColorHovered(S2D::Vector4<float>(0, 0, 1, 1));
    testButton->setButtonFont("./assets/chintzy.ttf", 24.f);
    testButton->setOnClickCallback(methodCallback(buttonCallback));

    testText = std::make_shared<S2D::Text>("Test text", S2D::Vector2<float>(1920/2, 1080/4), 100);
    testText->setTextFont("./assets/chintzy.ttf", 100);
    testText->setTextColor(S2D::Vector4<float>(1, 1, 1, 1));

    testSound = std::make_shared<S2D::Sound>("./assets/test.wav");

    registerGameObject(testPlaceable);
    registerGameObject(testButton);
    registerGameObject(testText);
    registerGameObject(testSound);

    mainSceneCamera = std::make_shared<S2D::Camera>();
}

void ArcanoidScene::Iterate(float deltaTime) {
    deltaSoundTime += deltaTime;
    if (deltaSoundTime >= 10.f){
        testSound->playSound();
        deltaSoundTime = 0.f;
    }
    S2D::GameScene::Iterate(deltaTime);
}