//
// Created by IvanMiatselski on 2026-09-13.
//

#include "Engine/S2DCollidable.hpp"
#include "Engine/S2DHelpers.hpp"

#include "gtest/gtest.h"

std::shared_ptr<S2D::Collidable> makeCollidable(const S2D::Vector2<float>& pos, const S2D::Vector2<float>& size) {
    auto collidable = std::make_shared<S2D::Collidable>();
    collidable->setBBPos(pos);
    collidable->setBBSize(size);
    return collidable;
}

TEST(CollidableTest, DefaultBoundingBox) {
    S2D::Collidable collidable;
    EXPECT_EQ(collidable.getBBPos(), S2D::Vector2<float>(0.f, 0.f));

    S2D::Vector4<float> dims = collidable.getBoundingBoxDimensions();
    EXPECT_FLOAT_EQ(dims.x, -50.f);
    EXPECT_FLOAT_EQ(dims.y, -50.f);
    EXPECT_FLOAT_EQ(dims.z, 50.f);
    EXPECT_FLOAT_EQ(dims.w, 50.f);
}

TEST(CollidableTest, SetAndGetBoundingBoxProperties) {
    S2D::Collidable collidable;
    collidable.setBBPos(S2D::Vector2<float>(10.f, 20.f));
    collidable.setBBSize(S2D::Vector2<float>(200.f, 100.f));

    EXPECT_EQ(collidable.getBBPos(), S2D::Vector2<float>(10.f, 20.f));

    S2D::Vector4<float> dims = collidable.getBoundingBoxDimensions();
    EXPECT_FLOAT_EQ(dims.x, -90.f);
    EXPECT_FLOAT_EQ(dims.y, -30.f);
    EXPECT_FLOAT_EQ(dims.z, 110.f);
    EXPECT_FLOAT_EQ(dims.w, 70.f);
}

TEST(CollidableTest, AabbFullOverlap) {
    auto a = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto b = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    EXPECT_TRUE(a->checkCollidableAgainstThisBB(b));
}

TEST(CollidableTest, AabbNoOverlap) {
    auto a = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto far = makeCollidable(S2D::Vector2<float>(1000.f, 1000.f), S2D::Vector2<float>(100.f, 100.f));
    EXPECT_FALSE(a->checkCollidableAgainstThisBB(far));
}

TEST(CollidableTest, AabbEdgeTouchingCountsAsCollision) {
    auto a = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto horizontalTouch = makeCollidable(S2D::Vector2<float>(100.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto verticalTouch = makeCollidable(S2D::Vector2<float>(0.f, 100.f), S2D::Vector2<float>(100.f, 100.f));
    EXPECT_TRUE(a->checkCollidableAgainstThisBB(horizontalTouch));
    EXPECT_TRUE(a->checkCollidableAgainstThisBB(verticalTouch));
}

TEST(CollidableTest, AabbJustOutsideOnEachAxis) {
    auto a = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto offX = makeCollidable(S2D::Vector2<float>(101.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto offY = makeCollidable(S2D::Vector2<float>(0.f, 101.f), S2D::Vector2<float>(100.f, 100.f));
    EXPECT_FALSE(a->checkCollidableAgainstThisBB(offX));
    EXPECT_FALSE(a->checkCollidableAgainstThisBB(offY));
}

TEST(CollidableTest, AabbPartialOverlap) {
    auto a = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    auto partial = makeCollidable(S2D::Vector2<float>(75.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    EXPECT_TRUE(a->checkCollidableAgainstThisBB(partial));
}

TEST(CollidableTest, TransformToScreenSpace) {
    auto collidable = makeCollidable(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(100.f, 100.f));
    collidable->transformBBToScreenSpace(S2D::Vector2<float>(0.f, 0.f), S2D::Vector2<float>(1.f, 1.f), 1920.f, 1080.f);

    EXPECT_FLOAT_EQ(collidable->getBBPos().x, 960.f);
    EXPECT_FLOAT_EQ(collidable->getBBPos().y, 540.f);

    S2D::Vector4<float> dims = collidable->getBoundingBoxDimensions();
    EXPECT_FLOAT_EQ(dims.x, 910.f);
    EXPECT_FLOAT_EQ(dims.y, 490.f);
    EXPECT_FLOAT_EQ(dims.z, 1010.f);
    EXPECT_FLOAT_EQ(dims.w, 590.f);
}

TEST(CollidableTest, ExecuteCallbackIncreasesTarget) {
    auto a = std::make_shared<S2D::Collidable>();
    auto b = std::make_shared<S2D::Collidable>();

    int aCalls = 0;
    int bCalls = 0;
    std::shared_ptr<S2D::GameObject> seenByA;

    a->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>& other) {
        aCalls++;
        seenByA = other;
    });
    b->setCallback(CollisionCallbackType::ON_COLLISION_START, [&](std::shared_ptr<S2D::GameObject>& other) {
        bCalls++;
    });

    std::shared_ptr<S2D::GameObject> objA = a;
    std::shared_ptr<S2D::GameObject> objB = b;
    a->executeCallback(CollisionCallbackType::ON_COLLISION_START, objB);
    b->executeCallback(CollisionCallbackType::ON_COLLISION_START, objA);

    EXPECT_EQ(aCalls, 1);
    EXPECT_EQ(bCalls, 1);
    EXPECT_EQ(seenByA, objB);
}

TEST(CollidableTest, ExecuteCallbackWithoutRegisteredCallbackDoesNotCrash) {
    auto a = std::make_shared<S2D::Collidable>();
    auto b = std::make_shared<S2D::Collidable>();
    std::shared_ptr<S2D::GameObject> objB = b;
    a->executeCallback(CollisionCallbackType::ON_COLLISION_START, objB);
    EXPECT_TRUE(true);
}