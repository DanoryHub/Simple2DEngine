//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DSound.hpp"

S2DGameScene::S2DGameScene() {
    mainSceneCamera = std::make_shared<S2DCamera>();
}

void S2DGameScene::registerGameObject(const std::shared_ptr<S2DGameObject>& gameObject) {
    gameObjects.push_back(gameObject);
}

void S2DGameScene::setSceneCamera(const std::shared_ptr<S2DCamera>& newCamera) {
    mainSceneCamera = newCamera;
}

void S2DGameScene::passDeviceAudioMixer(MIX_Mixer *newMixer) {
    for (auto gameObject: gameObjects) {
        auto audioObject = std::dynamic_pointer_cast<S2DSound>(gameObject);
        if (audioObject != nullptr) {
            audioObject->registerSoundDeviceMixer(newMixer);
        }
    }
}

std::shared_ptr<S2DCamera> S2DGameScene::getSceneCamera() const {
    return mainSceneCamera;
}


void S2DGameScene::Iterate(float deltaTime) {
    for (auto gameObject: gameObjects) {
        gameObject->Iterate(deltaTime);
    }
}

void S2DGameScene::Render(const std::shared_ptr<S2DRenderContext>& renderContext) {
    for (auto gameObject: gameObjects) {
        auto renderableObject = std::dynamic_pointer_cast<S2DIRenderable>(gameObject);
        if (renderableObject != nullptr) {
            renderableObject->Render(renderContext);
        }
    }
}

void S2DGameScene::receiveInput(const SDL_Event *event) {
    for (auto gameObject: gameObjects) {
        auto inputReceiver = std::dynamic_pointer_cast<S2DIInputReceiver>(gameObject);
        if (inputReceiver != nullptr) {
            inputReceiver->receiveInput(event);
        }
    }
}

std::vector<std::shared_ptr<S2DCollidable>> S2DGameScene::getAllCollidables() {
    std::vector<std::shared_ptr<S2DCollidable>> res;

    for (auto gameObject: gameObjects) {
        auto collidableObject = std::dynamic_pointer_cast<S2DCollidable>(gameObject);
        if (collidableObject != nullptr) {
            res.push_back(collidableObject);
        }
    }

    return res;
}

S2DGameScene::~S2DGameScene() {}