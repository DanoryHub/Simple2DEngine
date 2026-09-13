//
// Created by IvanMiatselski on 2026-09-13.
//

#include "Engine/S2DCollidable.hpp"

#include "gtest/gtest.h"

TEST(BoundingBoxTest, WorldPointsCenteredBox) {
    BoundingBox box;
    box.pos = S2DVector2<float>(100.f, 200.f);
    box.size = S2DVector2<float>(40.f, 60.f);

    S2DVector4<float> points = box.getWorldPoints();
    EXPECT_FLOAT_EQ(points.x, 80.f);
    EXPECT_FLOAT_EQ(points.y, 170.f);
    EXPECT_FLOAT_EQ(points.z, 120.f);
    EXPECT_FLOAT_EQ(points.w, 230.f);
}

TEST(BoundingBoxTest, ScreenPointsWithIdentityCamera) {
    BoundingBox box;
    box.pos = S2DVector2<float>(0.f, 0.f);
    box.size = S2DVector2<float>(100.f, 100.f);

    S2DVector4<float> screen = box.getPoints(S2DVector2<float>(0.f, 0.f), S2DVector2<float>(1.f, 1.f), 1920.f, 1080.f);
    EXPECT_FLOAT_EQ(screen.x, 910.f);
    EXPECT_FLOAT_EQ(screen.y, 490.f);
    EXPECT_FLOAT_EQ(screen.z, 1010.f);
    EXPECT_FLOAT_EQ(screen.w, 590.f);
}

TEST(BoundingBoxTest, ScreenPointsWithOffsetAndScaledCamera) {
    BoundingBox box;
    box.pos = S2DVector2<float>(0.f, 0.f);
    box.size = S2DVector2<float>(100.f, 100.f);

    S2DVector4<float> screen = box.getPoints(S2DVector2<float>(10.f, 20.f), S2DVector2<float>(2.f, 2.f), 1920.f, 1080.f);
    EXPECT_FLOAT_EQ(screen.x, 840.f);
    EXPECT_FLOAT_EQ(screen.y, 400.f);
    EXPECT_FLOAT_EQ(screen.z, 1040.f);
    EXPECT_FLOAT_EQ(screen.w, 600.f);
}