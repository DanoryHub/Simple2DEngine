//
// Created by IvanMiatselski on 19.07.2026.
//

#include "Engine/S2DGameObject.hpp"
#include "gtest/gtest.h"

TEST(GameObjectTest, NameGetterSetter) {
    S2DGameObject* pGameObject = new S2DGameObject();
    EXPECT_EQ(pGameObject->getName(), "");

    pGameObject->setName("TestName");
    EXPECT_EQ(pGameObject->getName(), "TestName");
    delete pGameObject;
}

TEST(GameObjectTest, IterateCallTest) {
    S2DGameObject* pGameObject = new S2DGameObject();
    // Just check Iterate dont crash
    pGameObject->Iterate(0.f);
    EXPECT_TRUE(true);
    delete pGameObject;
}