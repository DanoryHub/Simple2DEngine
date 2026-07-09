//
// Created by IvanMiatselski on 30.06.2026.
//

#include "../include/Arcanoid/ArcanoidSettings.hpp"
#include "../include/Arcanoid/ArcanoidObject.hpp"
#include "../include/Arcanoid/ArcanoidScene.hpp"
#include "Engine/S2DGameScene.hpp"

S2DGameSettings* CreateGameSettings() {
    return new ArcanoidSettings();
}

std::unordered_map<std::string, S2DGameScene*> ArcanoidSettings::GetAllScenes() {
    std::unordered_map<std::string, S2DGameScene*> scenes;
    scenes["MainScene"] = new ArcanoidScene();

    ArcanoidObject *obj1 = new ArcanoidObject();

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
