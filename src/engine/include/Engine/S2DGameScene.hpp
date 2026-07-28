//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMESCENE_HPP
#define ENGINE_S2DGAMESCENE_HPP
#include <vector>

struct SDL_Renderer;
struct S2DRenderContext;
class S2DGameObject;

class S2DGameScene {
protected:
    SDL_Renderer *renderer;
    std::vector<S2DGameObject*> gameObjects;

public:
    S2DGameScene();
    S2DGameScene(SDL_Renderer* newRenderer);
    virtual ~S2DGameScene();
    void registerGameObject(S2DGameObject* gameObject);

    virtual void Render(S2DRenderContext* renderContext);
    virtual void Iterate(float deltaTime);
};


#endif //ENGINE_S2DGAMESCENE_HPP