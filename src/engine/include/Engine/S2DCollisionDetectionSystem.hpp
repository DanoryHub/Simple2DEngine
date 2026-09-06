//
// Created by ivan_miatselski on 2026-09-04.
//

#ifndef ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
#define ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP

#include "Engine/S2DVector2.hpp"

#include <vector>
#include <memory>

struct SDL_Renderer;
class S2DCollidable;

class S2DCollisionDetectionSystem {
public:
    S2DCollisionDetectionSystem(int windowHeight, int windowWidth);
    void registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj);
    void checkAllCollisions(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale);
    void clearCollidables();

protected:
    bool isDebug = true;
    S2DVector2<int> windowSize;
    std::vector<std::shared_ptr<S2DCollidable>> collidableObjs;

};


#endif //ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
