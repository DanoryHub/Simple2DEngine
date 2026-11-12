//
// Created by IvanMiatselski on 19.07.2026.
//

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DVector2.hpp"

#include "gtest/gtest.h"

TEST(PlaceableTest, TestDefaultConstructor) {
    S2D::Placeable *testObj = new S2D::Placeable();

    EXPECT_EQ(testObj->GetPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(testObj->GetScale(), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_EQ(testObj->GetRotation(), 0.f);
    delete testObj;
}