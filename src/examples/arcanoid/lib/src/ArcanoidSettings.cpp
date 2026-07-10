//
// Created by IvanMiatselski on 30.06.2026.
//

#include "Arcanoid/ArcanoidSettings.hpp"
#include "Arcanoid/ArcanoidScene.hpp"
#include "Arcanoid/ArcanoidPlaceable.hpp"

#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DMainApp.hpp"

#include <iostream>
#include <string>

S2DGameSettings* CreateGameSettings() {
    return new ArcanoidSettings();
}

std::unordered_map<std::string, S2DGameScene*> ArcanoidSettings::GetAllScenes() {

    std::unordered_map<std::string, S2DGameScene*> scenes;
    scenes["MainScene"] = new ArcanoidScene();

    ArcanoidPlaceable *obj1 = new ArcanoidPlaceable(
        MainApp::GetInstance()->GetRenderer(),
        std::string("./assets/bug.png")
        );

    obj1->setName("obj1");

    scenes["MainScene"]->registerGameObject(obj1);

    return scenes;
}

std::string ArcanoidSettings::GetName() const {
    return "Arcanoid";
}

std::string ArcanoidSettings::GetTitle() const {
    return "Arcanoid Game";
}

std::string ArcanoidSettings::GetVersion() const {
    return "0.0.1";
}

std::string ArcanoidSettings::GetIdentifier() const {
    return "arcanoid";
}

int ArcanoidSettings::GetWindowWidth() const {
    return 1920;
}

int ArcanoidSettings::GetWindowHeight() const {
    return 1080;
}

std::string ArcanoidSettings::GetInitialSceneName() const {
    return "MainScene";
}
