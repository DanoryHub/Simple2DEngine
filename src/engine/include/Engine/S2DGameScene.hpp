//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMESCENE_HPP
#define ENGINE_S2DGAMESCENE_HPP

#include "Engine/S2DIInputReceiver.hpp"
#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DIIterable.hpp"
#include "Engine/S2DMainApp.hpp"

#include <vector>
#include <memory>

struct MIX_Mixer;

namespace S2D {

class RenderContext;
class GameObject;
class Collidable;
class Camera;

class GameScene: public S2D::IInputReceiver, public S2D::IRenderable, public S2D::IIterable{
protected:
    std::weak_ptr<MainApp> mainApp;
    std::shared_ptr<S2D::Camera> mainSceneCamera;
    std::vector<std::shared_ptr<S2D::GameObject>> gameObjects;

public:
    GameScene();
    ~GameScene() override;
    void registerGameObject(const std::shared_ptr<S2D::GameObject>& gameObject);
    void passDeviceAudioMixer(MIX_Mixer* newMixer);

    void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) override;
    void Iterate(float deltaTime) override;

    std::shared_ptr<S2D::Camera> getSceneCamera() const;
    void setSceneCamera(const std::shared_ptr<S2D::Camera>& newCamera);

    void receiveInput(const SDL_Event *event) override;
    std::vector<std::shared_ptr<S2D::Collidable>> getAllCollidables();
};

} // namespace S2D

#endif //ENGINE_S2DGAMESCENE_HPP
