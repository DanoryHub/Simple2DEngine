//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"

#include "SDL3/SDL_render.h"

S2DGameScene::S2DGameScene() {
    renderer = nullptr;
}

S2DGameScene::S2DGameScene(SDL_Renderer *newRenderer) {
    renderer = newRenderer;
}

void S2DGameScene::registerGameObject(S2DGameObject *gameObject) {
    gameObjects.push_back(gameObject);
}

void S2DGameScene::Iterate(float deltaTime) {
    for (auto gameObject: gameObjects) {
        gameObject->Iterate(deltaTime);
    }
}

S2DGameScene::~S2DGameScene() {
    for (auto gameObject : gameObjects) {
        delete gameObject;
    }
}