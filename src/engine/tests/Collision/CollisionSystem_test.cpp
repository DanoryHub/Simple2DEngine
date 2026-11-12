//
// Additional coverage for the collision system: segmentation, pair handling and
// placeable-driven bounding boxes.
//

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DPlaceable.hpp"

#include "gtest/gtest.h"

#include <memory>
#include <mutex>
#include <set>

namespace {

std::shared_ptr<S2D::Collidable> makeCollidable(
    const S2D::Vector2<float>& pos,
    const S2D::Vector2<float>& size) {
    auto collidable = std::make_shared<S2D::Collidable>();
    collidable->setBBPos(pos);
    collidable->setBBSize(size);
    return collidable;
}

class PlaceableCollidable : public S2D::Placeable, public S2D::Collidable {
public:
    PlaceableCollidable() = default;
};

} // namespace

TEST(CollisionSystemTest, HardwareSegmentCountIsBounded) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    const unsigned int segments = system.getSegmentsHardwareNum();

    EXPECT_GE(segments, 1u);
    EXPECT_LE(segments, 8u);
    EXPECT_TRUE(segments == 1u || segments % 2u == 0u);
}

TEST(CollisionSystemTest, CalculateSegmentSizeForFourByEight) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    const S2D::Vector2<float> size = system.calculateSegmentSize(4, 8);

    EXPECT_FLOAT_EQ(size.x, 480.f);
    EXPECT_FLOAT_EQ(size.y, 540.f);
}

TEST(CollisionSystemTest, ScreenSegmentAddAndRemoveCollidable) {
    std::mutex mutex;
    S2D::ScreenSegment segment(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(960.f, 540.f),
        mutex);
    auto collidable = makeCollidable(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(100.f, 100.f));

    EXPECT_FALSE(segment.containsCollidable(collidable));

    segment.addCollidableToSegment(collidable);
    EXPECT_TRUE(segment.containsCollidable(collidable));

    segment.removeCollidableFromSegment(collidable);
    EXPECT_FALSE(segment.containsCollidable(collidable));
}

TEST(CollisionSystemTest, ScreenSegmentAddDoesNotRequireOverlap) {
    std::mutex mutex;
    S2D::ScreenSegment segment(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(960.f, 540.f),
        mutex);
    auto outside = makeCollidable(
        S2D::Vector2<float>(5000.f, 5000.f),
        S2D::Vector2<float>(100.f, 100.f));

    segment.addCollidableToSegment(outside);

    EXPECT_TRUE(segment.containsCollidable(outside));
}

TEST(CollisionSystemTest, ScreenSegmentKeepsCollidableMovingInsideSegment) {
    std::mutex mutex;
    S2D::ScreenSegment segment(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(960.f, 540.f),
        mutex);
    auto collidable = makeCollidable(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(100.f, 100.f));

    EXPECT_TRUE(segment.registerCollidable(collidable));

    collidable->setBBPos(S2D::Vector2<float>(500.f, 300.f));
    EXPECT_TRUE(segment.registerCollidable(collidable));
    EXPECT_TRUE(segment.containsCollidable(collidable));
}

TEST(CollisionSystemTest, ThreeOverlappingCollidablesFireEachPairOnce) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    auto a = makeCollidable(S2D::Vector2<float>(100.f, 100.f), S2D::Vector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2D::Vector2<float>(100.f, 100.f), S2D::Vector2<float>(100.f, 100.f));
    auto c = makeCollidable(S2D::Vector2<float>(100.f, 100.f), S2D::Vector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    int cCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++aCalls; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++bCalls; });
    c->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++cCalls; });

    std::shared_ptr<S2D::Collidable> aBase = a;
    std::shared_ptr<S2D::Collidable> bBase = b;
    std::shared_ptr<S2D::Collidable> cBase = c;
    system.registerCollidable(aBase);
    system.registerCollidable(bBase);
    system.registerCollidable(cBase);

    system.checkAllCollisions(nullptr, S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f));

    // Three pairs: a-b, a-c, b-c. Each object participates in two pairs.
    EXPECT_EQ(aCalls, 2);
    EXPECT_EQ(bCalls, 2);
    EXPECT_EQ(cCalls, 2);
}

TEST(CollisionSystemTest, NonOverlappingCollidablesDoNotFire) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    auto a = makeCollidable(S2D::Vector2<float>(100.f, 100.f), S2D::Vector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2D::Vector2<float>(500.f, 500.f), S2D::Vector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++aCalls; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++bCalls; });

    std::shared_ptr<S2D::Collidable> aBase = a;
    std::shared_ptr<S2D::Collidable> bBase = b;
    system.registerCollidable(aBase);
    system.registerCollidable(bBase);

    system.checkAllCollisions(nullptr, S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f));

    EXPECT_EQ(aCalls, 0);
    EXPECT_EQ(bCalls, 0);
}

TEST(CollisionSystemTest, CollisionsFireAgainOnSubsequentFrames) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    auto a = makeCollidable(S2D::Vector2<float>(100.f, 100.f), S2D::Vector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2D::Vector2<float>(130.f, 100.f), S2D::Vector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++aCalls; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++bCalls; });

    std::shared_ptr<S2D::Collidable> aBase = a;
    std::shared_ptr<S2D::Collidable> bBase = b;
    system.registerCollidable(aBase);
    system.registerCollidable(bBase);

    system.checkAllCollisions(nullptr, S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);

    // checkAllCollisions transforms the bounding boxes into screen space, so the
    // world-space positions are re-established before the next frame, as a
    // Placeable does every frame.
    a->setBBPos(S2D::Vector2<float>(100.f, 100.f));
    b->setBBPos(S2D::Vector2<float>(130.f, 100.f));

    system.checkAllCollisions(nullptr, S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_EQ(aCalls, 2);
    EXPECT_EQ(bCalls, 2);
}

TEST(CollisionSystemTest, PlaceablePositionUpdatesBoundingBoxDuringCheck) {
    S2D::CollisionDetectionSystem system(1080, 1920);

    auto placeable = std::make_shared<PlaceableCollidable>();
    placeable->SetPosition(S2D::Vector2<float>(100.f, 100.f));
    placeable->setBBSize(S2D::Vector2<float>(100.f, 100.f));

    std::shared_ptr<S2D::Collidable> base = placeable;
    system.registerCollidable(base);

    system.checkAllCollisions(nullptr, S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f));

    // World center (100, 100) is mapped to screen center (960, 540) with an
    // identity camera, then transformed into the 100x100 bounding box.
    EXPECT_FLOAT_EQ(placeable->getBBPos().x, 1060.f);
    EXPECT_FLOAT_EQ(placeable->getBBPos().y, 640.f);
}

TEST(CollisionSystemTest, SegmentPairCheckFiresCallbackForEachPair) {
    std::mutex mutex;
    S2D::ScreenSegment segment(
        S2D::Vector2<float>(480.f, 270.f),
        S2D::Vector2<float>(960.f, 540.f),
        mutex);

    auto a = makeCollidable(S2D::Vector2<float>(480.f, 270.f), S2D::Vector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2D::Vector2<float>(490.f, 270.f), S2D::Vector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++aCalls; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>&) { ++bCalls; });

    segment.addCollidableToSegment(a);
    segment.addCollidableToSegment(b);

    std::set<std::pair<const S2D::Collidable*, const S2D::Collidable*>> processed;
    segment.checkCollisionsInSegment(processed);

    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);
    EXPECT_EQ(processed.size(), 1u);
}
