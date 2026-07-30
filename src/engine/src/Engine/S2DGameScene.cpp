//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"


S2DGameScene::S2DGameScene() {
    mainSceneCamera = new S2DCamera();
}

void S2DGameScene::registerGameObject(S2DGameObject *gameObject) {
    gameObjects.push_back(gameObject);
}

void S2DGameScene::setSceneCamera(S2DCamera* newCamera) {
    delete mainSceneCamera;
    mainSceneCamera = newCamera;
}

S2DCamera* S2DGameScene::getSceneCamera() const {
    return mainSceneCamera;
}


void S2DGameScene::Iterate(float deltaTime) {
    for (auto gameObject: gameObjects) {
        gameObject->Iterate(deltaTime);
    }
}

void S2DGameScene::Render(S2DRenderContext* renderContext) {
    renderContext->registerCamera(mainSceneCamera);
    for (auto gameObject: gameObjects) {
        auto renderableObject = dynamic_cast<S2DIRenderable*>(gameObject);
        if (renderableObject != nullptr) {
            renderableObject->Render(renderContext);
        }
    }
}

S2DGameScene::~S2DGameScene() {
    for (auto gameObject : gameObjects) {
        delete gameObject;
    }
    delete mainSceneCamera;
}