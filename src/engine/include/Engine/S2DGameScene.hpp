//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMESCENE_HPP
#define ENGINE_S2DGAMESCENE_HPP

#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DIIterable.hpp"
#include "Engine/S2DMainApp.hpp"

#include <vector>
#include <memory>

class S2DRenderContext;
class S2DGameObject;
class S2DCamera;

class S2DGameScene: public S2DIRenderable, public S2DIIterable{
protected:
    std::shared_ptr<MainApp> mainApp = nullptr;
    std::shared_ptr<S2DCamera> mainSceneCamera;
    std::vector<std::shared_ptr<S2DGameObject>> gameObjects;

public:
    S2DGameScene();
    ~S2DGameScene() override;
    void registerMainApp(const std::shared_ptr<MainApp>& app);
    void registerGameObject(const std::shared_ptr<S2DGameObject>& gameObject);

    void Render(std::shared_ptr<S2DRenderContext> renderContext) override;
    void Iterate(float deltaTime) override;

    std::shared_ptr<S2DCamera> getSceneCamera() const;
    void setSceneCamera(const std::shared_ptr<S2DCamera>& newCamera);
};


#endif //ENGINE_S2DGAMESCENE_HPP