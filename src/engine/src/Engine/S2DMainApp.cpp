//
// Created by IvanMiatselski on 02.06.2026.
//
#include <iostream>
#include <utility>


#include "SDL3/SDL.h"
#include "../../include/Engine/S2DMainApp.hpp"

#include "Engine/S2DGameScene.hpp"


MainApp::MainApp(
    std::string name, std::string version,
    std::string identifier, std::string title, std::string mainSceeneName,
    std::unordered_map<std::string, S2DGameScene*> newScenes,
    int screenWidth, int screenHeight):
    appScreenWidth(screenWidth),
    appScreenHeight(screenHeight),
    startSceneName(std::move(mainSceeneName)),
    scenes(std::move(newScenes)),
    appVersion(std::move(version)),
    appName(std::move(name)),
    appIdentifier(std::move(identifier)),
    windowTitle(std::move(title)) {

    currSceneName = startSceneName;
    UpdateCurrScene(currSceneName);
}

void MainApp::UpdateCurrScene(const std::string &nextSceneName) {
    currScene = scenes[nextSceneName];
}

SDL_AppResult MainApp::Init(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata(appName.c_str(), appVersion.c_str(), appIdentifier.c_str());

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL: Cant initialize video subsystem with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(windowTitle.c_str(), appScreenWidth, appScreenHeight, SDL_WINDOW_RESIZABLE, &mainWindow, &renderer)) {
        SDL_Log("SDL: Cant create window or renderer with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, appScreenWidth, appScreenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    currentTime = std::chrono::high_resolution_clock::now();

    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::ProcessEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::Iterate(void *appstate) {
    auto newTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deltaTime = newTime - currentTime;
    currentTime = newTime;

    currScene->Iterate(deltaTime.count());

    return SDL_APP_CONTINUE;
}

void MainApp::Quit(void *appstate, SDL_AppResult result) {
    for (auto& [name, scene]: scenes) {
        delete scene;
    }
}
