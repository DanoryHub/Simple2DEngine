//
// Created by IvanMiatselski on 19.07.2026.
//

#include "Engine/S2DVector2.hpp"

#include "gtest/gtest.h"


TEST(VectorTest, VectorAddition) {
    S2DVector2<int> Vector1{1, 1}, Vector2{2, 2};
    const S2DVector2<int> VectorExp{3, 3};
    S2DVector2<int> VectorTemp = Vector1 + Vector2;
    Vector1 += Vector2;

    EXPECT_EQ(VectorExp, VectorTemp);
    EXPECT_EQ(VectorExp, Vector1);

    VectorTemp = Vector2 + 1;
    Vector2 += 1;

    EXPECT_EQ(VectorExp, VectorTemp);
    EXPECT_EQ(VectorExp, Vector2);
}