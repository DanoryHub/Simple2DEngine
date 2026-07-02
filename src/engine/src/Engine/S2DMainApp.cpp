//
// Created by IvanMiatselski on 02.06.2026.
//
#include <string>
#include <iostream>
#include <utility>

#include "../../include/Engine/S2DMainApp.hpp"

#include "Engine/S2DGameScene.hpp"


MainApp::MainApp(
    const char *name, const char *version,
    const char *identifier, const char *title, std::string mainSceeneName,
    std::unordered_map<std::string, S2DGameScene*> newScenes,
    int screenWidth, int screenHeight):
    appName(name),
    appVersion(version),
    appIdentifier(identifier),
    windowTitle(title),
    startSceneName(std::move(mainSceeneName)),
    scenes(std::move(newScenes)),
    appScreenWidth(screenWidth),
    appScreenHeight(screenHeight) {

    currSceneName = startSceneName;
}

MainApp::~MainApp() = default;

SDL_AppResult MainApp::Init(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata(appName, appVersion, appIdentifier);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL: Cant initialize video subsystem with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(windowTitle, appScreenWidth, appScreenHeight, SDL_WINDOW_RESIZABLE, &mainWindow, &renderer)) {
        SDL_Log("SDL: Cant create window or renderer with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, appScreenWidth, appScreenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::ProcessEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::Iterate(void *appstate) {

    S2DGameScene *scene = scenes[currSceneName];

    scene->Iterate(0.1);

    return SDL_APP_CONTINUE;
}

void MainApp::Quit(void *appstate, SDL_AppResult result) {
    for (auto& [name, scene]: scenes) {
        delete scene;
    }
}
