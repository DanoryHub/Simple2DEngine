//
// Created by IvanMiatselski on 2026-09-13.
//

#include "Engine/S2DCollisionDetectionSystem.hpp"
#include "Engine/S2DHelpers.hpp"

#include "gtest/gtest.h"

#include <set>

namespace {
std::shared_ptr<S2DCollidable> makeCollidable(const S2DVector2<float>& pos, const S2DVector2<float>& size) {
    auto collidable = std::make_shared<S2DCollidable>();
    collidable->setBBPos(pos);
    collidable->setBBSize(size);
    return collidable;
}
}

TEST(ScreenSegmentTest, ConstructorSetsNameAndBox) {
    ScreenSegment segment(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    EXPECT_EQ(segment.getBBPos(), S2DVector2<float>(480.f, 270.f));
    EXPECT_NE(segment.getName().find("Segment["), std::string::npos);

    S2DVector4<float> dims = segment.getBoundingBoxDimensions();
    EXPECT_FLOAT_EQ(dims.x, 0.f);
    EXPECT_FLOAT_EQ(dims.y, 0.f);
    EXPECT_FLOAT_EQ(dims.z, 960.f);
    EXPECT_FLOAT_EQ(dims.w, 540.f);
}

TEST(ScreenSegmentTest, RegisterCollidableOnlyWhenOverlapping) {
    ScreenSegment segment(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));

    auto inside = makeCollidable(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(100.f, 100.f));
    auto outside = makeCollidable(S2DVector2<float>(5000.f, 5000.f), S2DVector2<float>(100.f, 100.f));

    EXPECT_TRUE(segment.registerCollidable(inside));
    EXPECT_TRUE(segment.containsCollidable(inside));

    EXPECT_FALSE(segment.registerCollidable(outside));
    EXPECT_FALSE(segment.containsCollidable(outside));
}

TEST(ScreenSegmentTest, RegisterIsIdempotentWhenStationary) {
    ScreenSegment segment(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    auto collidable = makeCollidable(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(100.f, 100.f));

    EXPECT_TRUE(segment.registerCollidable(collidable));
    EXPECT_TRUE(segment.registerCollidable(collidable));
}

TEST(ScreenSegmentTest, MovingOutOfSegmentRemovesCollidable) {
    ScreenSegment segment(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    auto collidable = makeCollidable(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(100.f, 100.f));

    EXPECT_TRUE(segment.registerCollidable(collidable));
    EXPECT_TRUE(segment.containsCollidable(collidable));

    collidable->setBBPos(S2DVector2<float>(5000.f, 5000.f));
    EXPECT_FALSE(segment.registerCollidable(collidable));
    EXPECT_FALSE(segment.containsCollidable(collidable));
}

TEST(ScreenSegmentTest, CollidableSpanningBoundaryRegistersInBoth) {
    ScreenSegment left(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    ScreenSegment right(S2DVector2<float>(1440.f, 270.f), S2DVector2<float>(960.f, 540.f));

    auto collidable = makeCollidable(S2DVector2<float>(960.f, 270.f), S2DVector2<float>(100.f, 100.f));

    EXPECT_TRUE(left.registerCollidable(collidable));
    EXPECT_TRUE(right.registerCollidable(collidable));
    EXPECT_TRUE(left.containsCollidable(collidable));
    EXPECT_TRUE(right.containsCollidable(collidable));
}

TEST(ScreenSegmentTest, CallbackFiresOncePerPairAcrossSegments) {
    ScreenSegment left(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    ScreenSegment right(S2DVector2<float>(1440.f, 270.f), S2DVector2<float>(960.f, 540.f));

    auto a = makeCollidable(S2DVector2<float>(960.f, 270.f), S2DVector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2DVector2<float>(970.f, 270.f), S2DVector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2DGameObject>&) { aCalls++; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2DGameObject>&) { bCalls++; });

    left.registerCollidable(a);
    left.registerCollidable(b);
    right.registerCollidable(a);
    right.registerCollidable(b);

    std::set<std::pair<const S2DCollidable*, const S2DCollidable*>> processed;
    left.checkCollisionsInSegment(processed);
    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);

    right.checkCollisionsInSegment(processed);
    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);
}

TEST(ScreenSegmentTest, ClearRemovesAllCollidables) {
    ScreenSegment segment(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(960.f, 540.f));
    auto collidable = makeCollidable(S2DVector2<float>(480.f, 270.f), S2DVector2<float>(100.f, 100.f));

    segment.registerCollidable(collidable);
    EXPECT_TRUE(segment.containsCollidable(collidable));

    segment.clearCollidablesInSegment();
    EXPECT_FALSE(segment.containsCollidable(collidable));
}

TEST(CollisionDetectionSystemTest, SegmentsInLineForVariousCounts) {
    S2DCollisionDetectionSystem system(1080, 1920);
    EXPECT_EQ(system.getSegmentsInLine(2), 2u);
    EXPECT_EQ(system.getSegmentsInLine(4), 2u);
    EXPECT_EQ(system.getSegmentsInLine(5), 2u);
    EXPECT_EQ(system.getSegmentsInLine(6), 3u);
    EXPECT_EQ(system.getSegmentsInLine(8), 4u);
}

TEST(CollisionDetectionSystemTest, CalculateSegmentSizeForTwoByTwo) {
    S2DCollisionDetectionSystem system(1080, 1920);

    S2DVector2<float> size2x2 = system.calculateSegmentSize(2, 4);
    EXPECT_FLOAT_EQ(size2x2.x, 960.f);
    EXPECT_FLOAT_EQ(size2x2.y, 540.f);
}

TEST(CollisionDetectionSystemTest, CalculateSegmentSizeForSingleRow) {
    S2DCollisionDetectionSystem system(1080, 1920);

    S2DVector2<float> size3 = system.calculateSegmentSize(3, 3);
    EXPECT_FLOAT_EQ(size3.x, 640.f);
    EXPECT_FLOAT_EQ(size3.y, 1080.f);
}

TEST(CollisionDetectionSystemTest, FullPipelineFiresCollisionOncePerPair) {
    S2DCollisionDetectionSystem system(1080, 1920);

    auto a = makeCollidable(S2DVector2<float>(100.f, 100.f), S2DVector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2DVector2<float>(130.f, 100.f), S2DVector2<float>(100.f, 100.f));

    int aCalls = 0;
    int bCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2DGameObject>&) { aCalls++; });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2DGameObject>&) { bCalls++; });

    std::shared_ptr<S2DCollidable> aShared = a;
    std::shared_ptr<S2DCollidable> bShared = b;
    system.registerCollidable(aShared);
    system.registerCollidable(bShared);

    system.checkAllCollisions(nullptr, S2DVector2<float>(0.f, 0.f), S2DVector2<float>(1.f, 1.f));

    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);
}

TEST(CollisionDetectionSystemTest, ClearCollidablesPreventsFurtherCollisions) {
    S2DCollisionDetectionSystem system(1080, 1920);

    auto a = makeCollidable(S2DVector2<float>(100.f, 100.f), S2DVector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2DVector2<float>(130.f, 100.f), S2DVector2<float>(100.f, 100.f));

    int aCalls = 0;
    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2DGameObject>&) { aCalls++; });

    std::shared_ptr<S2DCollidable> aShared = a;
    std::shared_ptr<S2DCollidable> bShared = b;
    system.registerCollidable(aShared);
    system.registerCollidable(bShared);

    system.checkAllCollisions(nullptr, S2DVector2<float>(0.f, 0.f), S2DVector2<float>(1.f, 1.f));
    EXPECT_EQ(aCalls, 1);

    system.clearCollidables();
    system.checkAllCollisions(nullptr, S2DVector2<float>(0.f, 0.f), S2DVector2<float>(1.f, 1.f));
    EXPECT_EQ(aCalls, 1);
}