//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"


S2DGameScene::S2DGameScene() {
    mainSceneCamera = std::make_shared<S2DCamera>();
}

void S2DGameScene::registerGameObject(const std::shared_ptr<S2DGameObject>& gameObject) {
    gameObjects.push_back(gameObject);
}

void S2DGameScene::setSceneCamera(const std::shared_ptr<S2DCamera>& newCamera) {
    mainSceneCamera = newCamera;
}

std::shared_ptr<S2DCamera> S2DGameScene::getSceneCamera() const {
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
        auto renderableObject = std::dynamic_pointer_cast<S2DIRenderable>(gameObject);
        if (renderableObject != nullptr) {
            renderableObject->Render(renderContext);
        }
    }
}

S2DGameScene::~S2DGameScene() {}