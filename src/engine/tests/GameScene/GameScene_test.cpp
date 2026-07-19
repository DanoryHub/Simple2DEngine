//
// Created by IvanMiatselski on 19.07.2026.
//

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DGameObject.hpp"

#include "gtest/gtest.h"

class IterateTracker : public S2DGameObject {
public:
    int iterateCount = 0;

    void Iterate(float deltaTime) override {
        iterateCount++;
    }
};

class GameSceneTest : public testing::Test {
protected:
    S2DGameScene* scene = nullptr;

    void SetUp() override {
        scene = new S2DGameScene();
    }

    void TearDown() override {
        delete scene;
    }
};

TEST_F(GameSceneTest, DefaultConstruction) {
    EXPECT_NE(scene, nullptr);
}

TEST_F(GameSceneTest, ConstructorWithNullptrRenderer) {
    S2DGameScene* nullRendererScene = new S2DGameScene(nullptr);
    EXPECT_NE(nullRendererScene, nullptr);
    delete nullRendererScene;
}

TEST_F(GameSceneTest, RegisterSingleObject) {
    auto* obj = new IterateTracker();
    scene->registerGameObject(obj);

    scene->Iterate(0.f);
    EXPECT_EQ(obj->iterateCount, 1);
}

TEST_F(GameSceneTest, RegisterMultipleObjects) {
    auto* obj1 = new IterateTracker();
    auto* obj2 = new IterateTracker();
    auto* obj3 = new IterateTracker();

    scene->registerGameObject(obj1);
    scene->registerGameObject(obj2);
    scene->registerGameObject(obj3);

    scene->Iterate(1.f);
    EXPECT_EQ(obj1->iterateCount, 1);
    EXPECT_EQ(obj2->iterateCount, 1);
    EXPECT_EQ(obj3->iterateCount, 1);

    scene->Iterate(2.f);
    EXPECT_EQ(obj1->iterateCount, 2);
    EXPECT_EQ(obj2->iterateCount, 2);
    EXPECT_EQ(obj3->iterateCount, 2);
}

TEST_F(GameSceneTest, IterateEmptyScene) {
    scene->Iterate(1.f);
    EXPECT_TRUE(true);
}
