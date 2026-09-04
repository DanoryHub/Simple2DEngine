//
// Created by ivan_miatselski on 2026-09-04.
//

#include "Engine/S2DCollisionDetectionSystem.hpp"

S2DCollisionDetectionSystem::S2DCollisionDetectionSystem(int windowHeight, int windowWidth) {
    windowSize = S2DVector2<int>(windowHeight, windowWidth);
}

void S2DCollisionDetectionSystem::registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj) {
    collidableObjs.push_back(collidableObj);
}

void S2DCollisionDetectionSystem::checkAllCollisions() {
    // TODO: Collision algo here
}