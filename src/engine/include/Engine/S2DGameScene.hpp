//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_S2DGAMESCENE_HPP
#define ARCANOID_S2DGAMESCENE_HPP
#include <vector>

class S2DGameObject;

class S2DGameScene {
protected:
    std::vector<S2DGameObject*> gameObjects;
public:
    ~S2DGameScene();
    void registerGameObject(S2DGameObject* gameObject);
    void Iterate(float deltaTime);
};


#endif //ARCANOID_S2DGAMESCENE_HPP