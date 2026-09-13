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

class S2DRenderContext;
class S2DGameObject;
class S2DCollidable;
class S2DCamera;
struct MIX_Mixer;

class S2DGameScene: public S2DIInputReceiver, public S2DIRenderable, public S2DIIterable{
protected:
    std::weak_ptr<MainApp> mainApp;
    std::shared_ptr<S2DCamera> mainSceneCamera;
    std::vector<std::shared_ptr<S2DGameObject>> gameObjects;

public:
    S2DGameScene();
    ~S2DGameScene() override;
    void registerGameObject(const std::shared_ptr<S2DGameObject>& gameObject);
    void passDeviceAudioMixer(MIX_Mixer* newMixer);

    void Render(const std::shared_ptr<S2DRenderContext>& renderContext) override;
    void Iterate(float deltaTime) override;

    std::shared_ptr<S2DCamera> getSceneCamera() const;
    void setSceneCamera(const std::shared_ptr<S2DCamera>& newCamera);

    void receiveInput(const SDL_Event *event) override;
    std::vector<std::shared_ptr<S2DCollidable>> getAllCollidables();
};


#endif //ENGINE_S2DGAMESCENE_HPP