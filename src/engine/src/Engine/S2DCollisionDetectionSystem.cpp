//
// Created by ivan_miatselski on 2026-09-04.
//
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"

#include "SDL3/SDL.h"

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

void S2DCollisionDetectionSystem::checkAllCollisions(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale) {
    for(auto collidable: collidableObjs){
        if (auto placeable = std::dynamic_pointer_cast<S2DPlaceable>(collidable)){
            collidable->updateBBPos(placeable->GetPosition());
        }
        if (isDebug && renderer != nullptr){
            collidable->drawDebugBox(renderer, cameraPos, cameraScale);
        }
    }
}