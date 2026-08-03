//
// Created by IvanMiatselski on 02.06.2026.
//

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DRenderContext.hpp"

#include <iostream>
#include <utility>

#include "SDL3/SDL.h"


MainApp* MainApp::mainApp = nullptr;

MainApp* MainApp::GetInstance(
            const std::string &name, const std::string &version,
            const std::string &identifier, const std::string &title, const std::string &mainSceneName,
            const int screenWidth, const int screenHeight) {
    if (mainApp == nullptr) {
        mainApp = new MainApp(name, version, identifier, title, mainSceneName,screenWidth, screenHeight);
    }
    return mainApp;
}

MainApp* MainApp::GetInstance() {
    return mainApp;
}

void MainApp::SetScenes(const std::unordered_map<std::string, std::shared_ptr<S2DGameScene>> &newScenes) {
    scenes = newScenes;
    UpdateCurrScene(currSceneName);
}

MainApp::MainApp(
    std::string name, std::string version,
    std::string identifier, std::string title, std::string mainSceneName,
    int screenWidth, int screenHeight):
    appScreenWidth(screenWidth),
    appScreenHeight(screenHeight),
    startSceneName(std::move(mainSceneName)),
    appVersion(std::move(version)),
    appName(std::move(name)),
    appIdentifier(std::move(identifier)),
    windowTitle(std::move(title)) {
    currSceneName = startSceneName;
    UpdateCurrScene(currSceneName);
}

void MainApp::UpdateCurrScene(const std::string &nextSceneName) {
    if (!scenes.empty()) {
        currScene = scenes[nextSceneName];
    }
}

MainApp::~MainApp() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (mainWindow != nullptr) {
        SDL_DestroyWindow(mainWindow);
    }
    SDL_Quit();
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

    currentContext = new S2DRenderContext();
    currentContext->registerRenderer(renderer);

    SDL_SetRenderLogicalPresentation(renderer, appScreenWidth, appScreenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    currentTime = std::chrono::high_resolution_clock::now();

    SetScenes(InitializeScenes());

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
    SDL_RenderClear(renderer);

    currScene->Iterate(deltaTime.count());
    currScene->Render(currentContext);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void MainApp::Quit(void *appstate, SDL_AppResult result) {
    delete currentContext;
}
