//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMESCENE_HPP
#define ENGINE_S2DGAMESCENE_HPP
#include "Engine/S2DIRenderable.hpp"
#include "Engine/S2DIIterable.hpp"

#include <vector>

class S2DRenderContext;
class S2DGameObject;
class S2DCamera;

class S2DGameScene: public S2DIRenderable, public S2DIIterable{
protected:
    S2DCamera *mainSceneCamera;
    std::vector<S2DGameObject*> gameObjects;

public:
    S2DGameScene();
    ~S2DGameScene() override;
    void registerGameObject(S2DGameObject* gameObject);

    void Render(S2DRenderContext* renderContext) override;
    void Iterate(float deltaTime) override;

    S2DCamera* getSceneCamera() const;
    void setSceneCamera(S2DCamera* sceneCamera);
};


#endif //ENGINE_S2DGAMESCENE_HPP