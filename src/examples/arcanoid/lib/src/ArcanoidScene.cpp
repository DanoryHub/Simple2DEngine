//
// Created by IvanMiatselski on 02.07.2026.
//

#include "../include/Arcanoid/ArcanoidScene.hpp"
#include <iostream>

ArcanoidScene::ArcanoidScene() {}

void ArcanoidScene::Iterate(float deltaTime) {
    S2DGameScene::Iterate(deltaTime);

    std::cout << "ArcanoidScene Iterate" << std::endl;
}