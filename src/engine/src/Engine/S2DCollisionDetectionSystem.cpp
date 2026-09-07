//
// Created by ivan_miatselski on 2026-09-04.
//
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"

#include <thread>
#include <iostream>

ScreenSegment::ScreenSegment(const S2DVector2<float> &pos, const S2DVector2<float> &size) {
    setBBPos(pos);
    setBBSize(size);
}

void ScreenSegment::drawScreenSpace(SDL_Renderer* renderer) {
    SDL_FRect rect{ boundingBox.pos.x, boundingBox.pos.y, boundingBox.size.x, boundingBox.size.y };

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
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
                segmentSize.x * posInLine,
                segmentSize.y * line
        };
        screenSegments.push_back(std::make_shared<ScreenSegment>(newSectorPos, segmentSize));
    }
}

unsigned int S2DCollisionDetectionSystem::getSegmentsHardwareNum() const {
    unsigned int segmentsNum = std::thread::hardware_concurrency();
    if (segmentsNum > maxSegmentsNum){
        segmentsNum = maxSegmentsNum;
    }
    if (segmentsNum % 2 != 0){
        segmentsNum -= 1;
    }

    return segmentsNum;
}

void S2DCollisionDetectionSystem::registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj) {
    collidableObjs.push_back(collidableObj);
}

void S2DCollisionDetectionSystem::clearCollidables() {
    collidableObjs.clear();
}

void S2DCollisionDetectionSystem::checkAllCollisions(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale) {
    for(auto screenSegment: screenSegments) {
        if (isDebug && renderer != nullptr){
            screenSegment->drawScreenSpace(renderer);
        }
    }
    for(auto collidable: collidableObjs){
        if (auto placeable = std::dynamic_pointer_cast<S2DPlaceable>(collidable)){
            collidable->setBBPos(placeable->GetPosition());
        }
        if (isDebug && renderer != nullptr){
            collidable->drawDebugBox(renderer, cameraPos, cameraScale);
        }
    }
}