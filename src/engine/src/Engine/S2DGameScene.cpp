//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DCamera.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DSound.hpp"

namespace S2D {

GameScene::GameScene() {
    mainSceneCamera = std::make_shared<S2D::Camera>();
}

void GameScene::registerGameObject(const std::shared_ptr<S2D::GameObject>& gameObject) {
    gameObjects.push_back(gameObject);
}

void GameScene::setSceneCamera(const std::shared_ptr<S2D::Camera>& newCamera) {
    mainSceneCamera = newCamera;
}

void GameScene::passDeviceAudioMixer(MIX_Mixer *newMixer) {
    for (auto gameObject: gameObjects) {
        auto audioObject = std::dynamic_pointer_cast<S2D::Sound>(gameObject);
        if (audioObject != nullptr) {
            audioObject->registerSoundDeviceMixer(newMixer);
        }
    }
}

std::shared_ptr<S2D::Camera> GameScene::getSceneCamera() const {
    return mainSceneCamera;
}


void GameScene::Iterate(float deltaTime) {
    for (auto gameObject: gameObjects) {
        gameObject->Iterate(deltaTime);
    }
}

void GameScene::Render(const std::shared_ptr<S2D::RenderContext>& renderContext) {
    for (auto gameObject: gameObjects) {
        auto renderableObject = std::dynamic_pointer_cast<S2D::IRenderable>(gameObject);
        if (renderableObject != nullptr) {
            renderableObject->Render(renderContext);
        }
    }
}

void GameScene::receiveInput(const SDL_Event *event) {
    for (auto gameObject: gameObjects) {
        auto inputReceiver = std::dynamic_pointer_cast<S2D::IInputReceiver>(gameObject);
        if (inputReceiver != nullptr) {
            inputReceiver->receiveInput(event);
        }
    }
}

std::vector<std::shared_ptr<S2D::Collidable>> GameScene::getAllCollidables() {
    std::vector<std::shared_ptr<S2D::Collidable>> res;

    for (auto gameObject: gameObjects) {
        auto collidableObject = std::dynamic_pointer_cast<S2D::Collidable>(gameObject);
        if (collidableObject != nullptr) {
            res.push_back(collidableObject);
        }
    }

    return res;
}

GameScene::~GameScene() {}

} // namespace S2D
