//
// Created by ivan_miatselski on 2026-09-04.
//
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DHelpers.hpp"

#include <iostream>

S2DENGINE_NAMESPACE_BEGIN

ScreenSegment::ScreenSegment(const S2D::Vector2<float>& pos, const S2D::Vector2<float>& size, std::mutex& globalMutex): dataLock(globalMutex) {
    setBBPos(pos);
    setBBSize(size);
    setName("Segment[" + std::to_string(static_cast<int>(pos.x)) + "," + std::to_string(static_cast<int>(pos.y)) + "]");
}

void ScreenSegment::drawScreenSpace(SDL_Renderer* renderer) {
    S2D::Vector4<float> world = boundingBox.getWorldPoints();
    SDL_FRect rect{ world.x, world.y, world.z - world.x, world.w - world.y };

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
}

std::thread ScreenSegment::spawnCollisionsCheckingThread(std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>>& processedPairs){
    return std::thread([this, &processedPairs] { this->checkCollisionsInSegment(processedPairs); } );
}

bool ScreenSegment::registerCollidable(const std::shared_ptr<S2D::Collidable>& collidable) {
    std::lock_guard<std::mutex> lock(dataLock);
    if (!checkCollidableAgainstThisBB(collidable)) {
        collidablesInSegment.erase(collidable);
        return false;
    }

    auto it = collidablesInSegment.find(collidable);
    if (it != collidablesInSegment.end() && it->second == collidable->getBBPos()) {
        return true;
    }

    collidablesInSegment[collidable] = collidable->getBBPos();
    return true;
}

bool ScreenSegment::containsCollidable(const std::shared_ptr<S2D::Collidable>& collidable) const {
    std::lock_guard<std::mutex> lock(dataLock);
    return collidablesInSegment.contains(collidable);
}

void ScreenSegment::addCollidableToSegment(const std::shared_ptr<S2D::Collidable>& collidable) {
    std::lock_guard<std::mutex> lock(dataLock);
    collidablesInSegment[collidable] = collidable->getBBPos();
}

void ScreenSegment::removeCollidableFromSegment(const std::shared_ptr<S2D::Collidable>& collidable) {
    std::lock_guard<std::mutex> lock(dataLock);
    collidablesInSegment.erase(collidable);
}

void ScreenSegment::clearCollidablesInSegment() {
    std::lock_guard<std::mutex> lock(dataLock);
    collidablesInSegment.clear();
}

void ScreenSegment::checkCollisionsInSegment(std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>>& processedPairs) {
    std::map<std::shared_ptr<S2D::Collidable>, S2D::Vector2<float>> collidablesSnapshot;
    {
        std::unique_lock<std::mutex> lock(dataLock);
        collidablesSnapshot = collidablesInSegment;
        lock.unlock();
    }

    for (auto it1 = collidablesSnapshot.begin(); it1 != collidablesSnapshot.end(); ++it1) {
        auto it2 = std::next(it1);
        for (; it2 != collidablesSnapshot.end(); ++it2) {
            if (!it1->first->checkCollidableAgainstThisBB(it2->first)) {
                continue;
            }

            const S2D::Collidable* key1 = it1->first.get();
            const S2D::Collidable* key2 = it2->first.get();
            auto pairKey = (key1 < key2) ? std::make_pair(key1, key2) : std::make_pair(key2, key1);
            {
                std::scoped_lock lock(dataLock);
                if (!processedPairs.insert(pairKey).second) {
                    continue;
                }
            }

            std::shared_ptr<S2D::GameObject> obj1 = it1->first;
            std::shared_ptr<S2D::GameObject> obj2 = it2->first;
            it1->first->executeCallback(CollisionCallbackType::ON_COLLISION_START, obj2);
            it2->first->executeCallback(CollisionCallbackType::ON_COLLISION_START, obj1);
        }
    }
}

CollisionDetectionSystem::CollisionDetectionSystem(int windowHeight, int windowWidth) {
    windowSize = S2D::Vector2<int>(windowHeight, windowWidth);
    initScreenSegments();
}

unsigned int CollisionDetectionSystem::getSegmentsInLine(unsigned const int segmentsNum) {
    unsigned int segmentsInLine = segmentsNum;
    if (segmentsNum > maxSegmentsInLine){
        segmentsInLine = segmentsNum / 2;
    }

    return segmentsInLine;
}

S2D::Vector2<float> CollisionDetectionSystem::calculateSegmentSize(unsigned const int segmentsInLine,
                                                                    unsigned const int segmentsNum) {
    S2D::Vector2<float> segmentSize;
    segmentSize.x = static_cast<float>(windowSize.y) / static_cast<float>(segmentsInLine);
    segmentSize.y = static_cast<float>(windowSize.x);
    if (segmentsInLine < segmentsNum) segmentSize.y = static_cast<float>(windowSize.x) / 2.f;
    return segmentSize;
}

void CollisionDetectionSystem::initScreenSegments() {
    auto segmentsNum = getSegmentsHardwareNum();
    auto segmentsInLine = getSegmentsInLine(segmentsNum);
    S2D::Vector2<float> segmentSize = calculateSegmentSize(segmentsInLine, segmentsNum);

    for (int i = 0; i < segmentsNum; i++){
        unsigned int posInLine = i;
        unsigned int line = 0;
        if (i > segmentsInLine - 1){
            line = 1;
            posInLine -= segmentsInLine;
        }

        S2D::Vector2<float> newSectorPos{
                segmentSize.x * posInLine + segmentSize.x / 2.f,
                segmentSize.y * line + segmentSize.y / 2.f
        };
        screenSegments.push_back(std::make_shared<ScreenSegment>(newSectorPos, segmentSize, globalCollisionMutex));
    }
}

unsigned int CollisionDetectionSystem::getSegmentsHardwareNum() const {
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

void CollisionDetectionSystem::registerCollidable(std::shared_ptr<S2D::Collidable> &collidableObj) {
    std::lock_guard<std::mutex> lock(collidablesMutex);
    collidableObjs.push_back(collidableObj);
}

void CollisionDetectionSystem::clearCollidables() {
    {
        std::lock_guard<std::mutex> lock(collidablesMutex);
        collidableObjs.clear();
    }
    for (const auto& segment: screenSegments){
        segment->clearCollidablesInSegment();
    }
}

void CollisionDetectionSystem::checkAllCollisions(SDL_Renderer* renderer, const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale) {
    // Snapshot under the lock so register/clear cannot invalidate the vector
    // while this frame is being processed.
    std::vector<std::shared_ptr<S2D::Collidable>> collidables;
    {
        std::scoped_lock lock(collidablesMutex);
        collidables = collidableObjs;
    }

    for(const auto& collidable: collidables){
        if (auto placeable = std::dynamic_pointer_cast<S2D::Placeable>(collidable)){
            collidable->setBBPos(placeable->GetPosition());
        }
        collidable->transformBBToScreenSpace(cameraPos, cameraScale, static_cast<float>(windowSize.y), static_cast<float>(windowSize.x));
        if (isDebug && renderer != nullptr){
            collidable->drawDebugBox(renderer);
        }
    }

    std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>> processedPairs;
    std::vector<std::thread> threads;
    for(const auto& screenSegment: screenSegments) {
        if (isDebug && renderer != nullptr){
            screenSegment->drawScreenSpace(renderer);
        }

        for (const auto& collidable: collidables){
            screenSegment->registerCollidable(collidable);
        }
        threads.push_back(screenSegment->spawnCollisionsCheckingThread(processedPairs));
    }

    for(auto &thread: threads){
        thread.join();
    }
}

S2DENGINE_NAMESPACE_END
