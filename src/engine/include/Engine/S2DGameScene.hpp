//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ENGINE_S2DGAMESCENE_HPP
#define ENGINE_S2DGAMESCENE_HPP
#include <vector>

class S2DGameObject;

class S2DGameScene {
protected:
    std::vector<S2DGameObject*> gameObjects;
public:
    virtual ~S2DGameScene();
    void registerGameObject(S2DGameObject* gameObject);
    virtual void Iterate(float deltaTime);
};


#endif //ENGINE_S2DGAMESCENE_HPP