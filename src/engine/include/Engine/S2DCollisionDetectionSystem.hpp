//
// Created by ivan_miatselski on 2026-09-04.
//

#ifndef ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
#define ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DVector2.hpp"

#include <map>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <set>

struct SDL_Renderer;

S2DENGINE_NAMESPACE_BEGIN

class ScreenSegment: public S2D::Placeable, public S2D::Collidable{
private:
    std::map<std::shared_ptr<S2D::Collidable>, S2D::Vector2<float>> collidablesInSegment;
    std::mutex& dataLock;
public:
    ScreenSegment(const S2D::Vector2<float>& pos, const S2D::Vector2<float>& size, std::mutex& globalMutex);
    void drawScreenSpace(SDL_Renderer* renderer);
    bool registerCollidable(const std::shared_ptr<S2D::Collidable>& collidable);
    bool containsCollidable(const std::shared_ptr<S2D::Collidable>& collidable) const;
    void addCollidableToSegment(const std::shared_ptr<S2D::Collidable>& collidable);
    void removeCollidableFromSegment(const std::shared_ptr<S2D::Collidable>& collidable);
    void clearCollidablesInSegment();
    std::thread spawnCollisionsCheckingThread(std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>>& processedPairs);
    void checkCollisionsInSegment(std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>>& processedPairs);
};

class CollisionDetectionSystem {
public:
    CollisionDetectionSystem(int windowHeight, int windowWidth);
    void registerCollidable(std::shared_ptr<S2D::Collidable> &collidableObj);
    void checkAllCollisions(SDL_Renderer* renderer, const S2D::Vector2<float>& cameraPos, const S2D::Vector2<float>& cameraScale);
    void initScreenSegments();
    unsigned int getSegmentsInLine(unsigned int segmentsNum);
    S2D::Vector2<float> calculateSegmentSize(unsigned int segmentsInLine, unsigned int segmentsNum);
    unsigned int getSegmentsHardwareNum() const;
    void clearCollidables();
protected:
    const bool isDebug = true;
    unsigned const int maxSegmentsNum = 8;
    unsigned const int maxSegmentsInLine = 3;
    unsigned const int leftHardwareCores = 2;
    S2D::Vector2<int> windowSize;
    mutable std::mutex collidablesMutex;
    std::vector<std::shared_ptr<S2D::Collidable>> collidableObjs;
    std::vector<std::shared_ptr<ScreenSegment>> screenSegments;
    std::mutex globalCollisionMutex;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
