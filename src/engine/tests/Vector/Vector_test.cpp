//
// Created by IvanMiatselski on 19.07.2026.
//

#include "Engine/S2DVector2.hpp"
#include "gtest/gtest.h"

class VectorTest: public testing::Test {
protected:
    VectorTest() {}

    S2DVector2<int> Vec1{1, 1};
    S2DVector2<int> Vec2{2, 2};
    S2DVector2<int> Vec3{3, 3};
    S2DVector2<int> Vec4{4, 4};
    S2DVector2<int> Vec6{6, 6};
};

TEST_F(VectorTest, VectorAddition) {
    S2DVector2<int> VecTemp = Vec1 + Vec2;
    EXPECT_EQ(Vec3, VecTemp);

    VecTemp = Vec2 + 1;
    EXPECT_EQ(Vec3, VecTemp);

    Vec1 += Vec2;
    Vec2 += 1;
    EXPECT_EQ(Vec3, Vec1);
    EXPECT_EQ(Vec3, Vec2);
}

TEST_F(VectorTest, VectorSubtraction) {
    S2DVector2<int> VecTemp = Vec3 - Vec1;
    EXPECT_EQ(Vec2, VecTemp);

    VecTemp = Vec3 - 1;
    EXPECT_EQ(Vec2, VecTemp);

    Vec3 -= Vec2;
    Vec2 -= 1;
    EXPECT_EQ(Vec3, Vec1);
    EXPECT_EQ(Vec2, Vec1);
}

TEST_F(VectorTest, VectorMultiplication) {
    S2DVector2<int> VecExp = S2DVector2<int>(6, 6);

    S2DVector2<int> VecTemp = Vec3 * Vec2;
    EXPECT_EQ(VecExp, VecTemp);

    VecTemp = Vec3 * 2;
    EXPECT_EQ(VecExp, VecTemp);

    Vec3 *= Vec2;
    Vec2 *= 3;
    EXPECT_EQ(VecExp, Vec3);
    EXPECT_EQ(VecExp, Vec2);
}

TEST_F(VectorTest, VectorDivision) {
    S2DVector2<int> VecTemp = Vec6 / Vec3;
    EXPECT_EQ(VecTemp, Vec2);

    VecTemp = Vec6 / 3;
    EXPECT_EQ(VecTemp, Vec2);

    Vec6 /= Vec3;
    Vec4 /= Vec2;
    EXPECT_EQ(Vec6, Vec2);
    EXPECT_EQ(Vec4, Vec2);
}

TEST_F(VectorTest, VectorComparison) {
    ASSERT_TRUE(Vec2 == Vec4 / 2);
}