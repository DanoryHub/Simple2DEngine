//
// Created by ivan_miatselski on 2026-09-04.
//
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DCollidable.hpp"

#include <iostream>

S2DCollisionDetectionSystem::S2DCollisionDetectionSystem(int windowHeight, int windowWidth) {
    windowSize = S2DVector2<int>(windowHeight, windowWidth);
}

void S2DCollisionDetectionSystem::registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj) {
    collidableObjs.push_back(collidableObj);
}

void S2DCollisionDetectionSystem::clearCollidables() {
    collidableObjs.clear();
}

void S2DCollisionDetectionSystem::checkAllCollisions() {
    std::cout << "Checking collisions" << std::endl;
    for(auto collidable: collidableObjs){
        collidable->testLog();
    }
}