//
// Created by ivan_miatselski on 2026-09-04.
//
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DHelpers.hpp"

#include <thread>
#include <iostream>

ScreenSegment::ScreenSegment(const S2DVector2<float> &pos, const S2DVector2<float> &size) {
    setBBPos(pos);
    setBBSize(size);
    setName("Segment[" + std::to_string(static_cast<int>(pos.x)) + "," + std::to_string(static_cast<int>(pos.y)) + "]");
}

void ScreenSegment::drawScreenSpace(SDL_Renderer* renderer) {
    S2DVector4<float> world = boundingBox.getWorldPoints();
    SDL_FRect rect{ world.x, world.y, world.z - world.x, world.w - world.y };

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
}

bool ScreenSegment::registerCollidable(const std::shared_ptr<S2DCollidable>& collidable) {
    if (!checkCollidableAgainstThisBB(collidable)) {
        if (collidablesInSegment.contains(collidable)) {
            removeCollidableFromSegment(collidable);
        }
        return false;
    }

    if (collidablesInSegment.contains(collidable) &&
        collidablesInSegment[collidable] == collidable->getBBPos()) {
        return true;
    }

    addCollidableToSegment(collidable);
    return true;
}

bool ScreenSegment::containsCollidable(const std::shared_ptr<S2DCollidable>& collidable) const {
    return collidablesInSegment.contains(collidable);
}

void ScreenSegment::addCollidableToSegment(const std::shared_ptr<S2DCollidable>& collidable) {
    collidablesInSegment[collidable] = collidable->getBBPos();
}

void ScreenSegment::removeCollidableFromSegment(const std::shared_ptr<S2DCollidable>& collidable) {
    collidablesInSegment.erase(collidable);
}

void ScreenSegment::clearCollidablesInSegment() {
    collidablesInSegment.clear();
}

void ScreenSegment::checkCollisionsInSegment(std::set<std::pair<const S2DCollidable*, const S2DCollidable*>>& processedPairs) {
    for (auto it1 = collidablesInSegment.begin(); it1 != collidablesInSegment.end(); ++it1) {
        auto it2 = std::next(it1);
        for (; it2 != collidablesInSegment.end(); ++it2) {
            if (!it1->first->checkCollidableAgainstThisBB(it2->first)) {
                continue;
            }

            const S2DCollidable* key1 = it1->first.get();
            const S2DCollidable* key2 = it2->first.get();
            auto pairKey = (key1 < key2) ? std::make_pair(key1, key2) : std::make_pair(key2, key1);
            if (!processedPairs.insert(pairKey).second) {
                continue;
            }

            std::shared_ptr<S2DGameObject> obj1 = it1->first;
            std::shared_ptr<S2DGameObject> obj2 = it2->first;
            it1->first->executeCallback(CollisionCallbackType::ON_COLLISION_START, obj2);
            it2->first->executeCallback(CollisionCallbackType::ON_COLLISION_START, obj1);
        }
    }
}

S2DCollisionDetectionSystem::S2DCollisionDetectionSystem(int windowHeight, int windowWidth) {
    windowSize = S2DVector2<int>(windowHeight, windowWidth);
    initScreenSegments();
}

unsigned int S2DCollisionDetectionSystem::getSegmentsInLine(unsigned const int segmentsNum) {
    unsigned int segmentsInLine = segmentsNum;
    if (segmentsNum > maxSegmentsInLine){
        segmentsInLine = segmentsNum / 2;
    }

    return segmentsInLine;
}

S2DVector2<float> S2DCollisionDetectionSystem::calculateSegmentSize(unsigned const int segmentsInLine,
                                                                    unsigned const int segmentsNum) {
    S2DVector2<float> segmentSize;
    segmentSize.x = static_cast<float>(windowSize.y) / static_cast<float>(segmentsInLine);
    segmentSize.y = static_cast<float>(windowSize.x);
    if (segmentsInLine < segmentsNum) segmentSize.y = static_cast<float>(windowSize.x) / 2.f;
    return segmentSize;
}

void S2DCollisionDetectionSystem::initScreenSegments() {
    auto segmentsNum = getSegmentsHardwareNum();
    auto segmentsInLine = getSegmentsInLine(segmentsNum);
    S2DVector2<float> segmentSize = calculateSegmentSize(segmentsInLine, segmentsNum);

    for (int i = 0; i < segmentsNum; i++){
        unsigned int posInLine = i;
        unsigned int line = 0;
        if (i > segmentsInLine - 1){
            line = 1;
            posInLine -= segmentsInLine;
        }

        S2DVector2<float> newSectorPos{
                segmentSize.x * posInLine + segmentSize.x / 2.f,
                segmentSize.y * line + segmentSize.y / 2.f
        };
        screenSegments.push_back(std::make_shared<ScreenSegment>(newSectorPos, segmentSize));
    }
}

unsigned int S2DCollisionDetectionSystem::getSegmentsHardwareNum() const {
    unsigned int segmentsNum = std::thread::hardware_concurrency() - leftHardwareCores;
    if (segmentsNum > maxSegmentsNum){
        segmentsNum = maxSegmentsNum;
    }
    if (segmentsNum % 2 != 0){
        segmentsNum -= 1;
    }
    if (segmentsNum < 1){
        segmentsNum = 1;
    }

    return segmentsNum;
}

void S2DCollisionDetectionSystem::registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj) {
    collidableObjs.push_back(collidableObj);
}

void S2DCollisionDetectionSystem::clearCollidables() {
    collidableObjs.clear();
    for (const auto& segment: screenSegments){
        segment->clearCollidablesInSegment();
    }
}

void S2DCollisionDetectionSystem::checkAllCollisions(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale) {
    for(const auto& collidable: collidableObjs){
        if (auto placeable = std::dynamic_pointer_cast<S2DPlaceable>(collidable)){
            collidable->setBBPos(placeable->GetPosition());
        }
        collidable->transformBBToScreenSpace(cameraPos, cameraScale, static_cast<float>(windowSize.y), static_cast<float>(windowSize.x));
        if (isDebug && renderer != nullptr){
            collidable->drawDebugBox(renderer);
        }
    }

    std::set<std::pair<const S2DCollidable*, const S2DCollidable*>> processedPairs;
    for(const auto& screenSegment: screenSegments) {
        if (isDebug && renderer != nullptr){
            screenSegment->drawScreenSpace(renderer);
        }

        for (const auto& collidable: collidableObjs){
            // ScreenSegment caches and checks if it has collidables itself, dont need to optimize here
            // so just register (maybe only cut off additional jumps and checks, but not for now)
            screenSegment->registerCollidable(collidable);
        }
        screenSegment->checkCollisionsInSegment(processedPairs);
    }
}