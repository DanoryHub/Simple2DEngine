//
// Tests for the Camera system.
//

#include "Engine/S2DCamera.hpp"

#include "gtest/gtest.h"

TEST(CameraTest, DefaultState) {
    S2D::Camera camera;

    EXPECT_EQ(camera.getPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(camera.getScale(), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_FLOAT_EQ(camera.getRotation(), 0.f);
}

TEST(CameraTest, SetPosition) {
    S2D::Camera camera;

    camera.setPosition(S2D::Vector2<float>(120.f, -45.f));

    EXPECT_EQ(camera.getPosition(), S2D::Vector2<float>(120.f, -45.f));
    EXPECT_EQ(camera.getScale(), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_FLOAT_EQ(camera.getRotation(), 0.f);
}

TEST(CameraTest, SetScale) {
    S2D::Camera camera;

    camera.setScale(S2D::Vector2<float>(2.5f, 0.5f));

    EXPECT_EQ(camera.getScale(), S2D::Vector2<float>(2.5f, 0.5f));
    EXPECT_EQ(camera.getPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_FLOAT_EQ(camera.getRotation(), 0.f);
}

TEST(CameraTest, SetRotation) {
    S2D::Camera camera;

    camera.setRotation(90.f);

    EXPECT_FLOAT_EQ(camera.getRotation(), 90.f);
    EXPECT_EQ(camera.getPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(camera.getScale(), S2D::Vector2<float>(1.f, 1.f));
}

TEST(CameraTest, SettersOverwritePreviousValues) {
    S2D::Camera camera;

    camera.setPosition(S2D::Vector2<float>(10.f, 20.f));
    camera.setScale(S2D::Vector2<float>(3.f, 4.f));
    camera.setRotation(15.f);

    camera.setPosition(S2D::Vector2<float>(-10.f, -20.f));
    camera.setScale(S2D::Vector2<float>(0.25f, 0.75f));
    camera.setRotation(-15.f);

    EXPECT_EQ(camera.getPosition(), S2D::Vector2<float>(-10.f, -20.f));
    EXPECT_EQ(camera.getScale(), S2D::Vector2<float>(0.25f, 0.75f));
    EXPECT_FLOAT_EQ(camera.getRotation(), -15.f);
}

TEST(CameraTest, InstancesAreIndependent) {
    S2D::Camera first;
    S2D::Camera second;

    first.setPosition(S2D::Vector2<float>(100.f, 200.f));
    first.setScale(S2D::Vector2<float>(2.f, 2.f));
    first.setRotation(45.f);

    EXPECT_EQ(second.getPosition(), S2D::Vector2<float>(0.f, 0.f));
    EXPECT_EQ(second.getScale(), S2D::Vector2<float>(1.f, 1.f));
    EXPECT_FLOAT_EQ(second.getRotation(), 0.f);
}
