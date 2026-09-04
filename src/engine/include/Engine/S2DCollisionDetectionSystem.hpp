//
// Created by ivan_miatselski on 2026-09-04.
//

#ifndef ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
#define ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP

#include "Engine/S2DVector2.hpp"

#include <vector>
#include <memory>

class S2DCollidable;

class S2DCollisionDetectionSystem {
public:
    S2DVector2<int> windowSize;
    std::vector<std::shared_ptr<S2DCollidable>> collidableObjs;
protected:
    S2DCollisionDetectionSystem(int windowHeight, int windowWidth);
    void registerCollidable(std::shared_ptr<S2DCollidable>& collidableObj);
    void checkAllCollisions();
};


#endif //ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
