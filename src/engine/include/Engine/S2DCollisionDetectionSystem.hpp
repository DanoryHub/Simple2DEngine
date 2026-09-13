//
// Created by ivan_miatselski on 2026-09-04.
//

#ifndef ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
#define ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DVector2.hpp"

#include <map>
#include <vector>
#include <memory>
#include <set>

struct SDL_Renderer;

class ScreenSegment: public S2DPlaceable, public S2DCollidable{
private:
    std::map<std::shared_ptr<S2DCollidable>, S2DVector2<float>> collidablesInSegment;
public:
    ScreenSegment(const S2DVector2<float>& pos, const S2DVector2<float>& size);
    void drawScreenSpace(SDL_Renderer* renderer);
    bool registerCollidable(const std::shared_ptr<S2DCollidable>& collidable);
    bool containsCollidable(const std::shared_ptr<S2DCollidable>& collidable) const;
    void addCollidableToSegment(const std::shared_ptr<S2DCollidable>& collidable);
    void removeCollidableFromSegment(const std::shared_ptr<S2DCollidable>& collidable);
    void clearCollidablesInSegment();
    void checkCollisionsInSegment(std::set<std::pair<const S2DCollidable*, const S2DCollidable*>>& processedPairs);
};

class S2DCollisionDetectionSystem {
public:
    S2DCollisionDetectionSystem(int windowHeight, int windowWidth);
    void registerCollidable(std::shared_ptr<S2DCollidable> &collidableObj);
    void checkAllCollisions(SDL_Renderer* renderer, const S2DVector2<float>& cameraPos, const S2DVector2<float>& cameraScale);
    void initScreenSegments();
    unsigned int getSegmentsInLine(unsigned int segmentsNum);
    S2DVector2<float> calculateSegmentSize(unsigned int segmentsInLine, unsigned int segmentsNum);
    unsigned int getSegmentsHardwareNum() const;
    void clearCollidables();
protected:
    const bool isDebug = true;
    unsigned const int maxSegmentsNum = 8;
    unsigned const int maxSegmentsInLine = 3;
    unsigned const int leftHardwareCores = 2;
    S2DVector2<int> windowSize;
    std::vector<std::shared_ptr<S2DCollidable>> collidableObjs;
    std::vector<std::shared_ptr<ScreenSegment>> screenSegments;
};


#endif //ENGINE_S2DCOLLISIONDETECTIONSYSTEM_HPP
