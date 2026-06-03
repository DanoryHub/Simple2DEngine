//
// Created by IvanMiatselski on 02.06.2026.
//
#include <string>
#include <iostream>

#include "../../include/Engine/main_app.h"


MainApp::MainApp(
    const char *name, const char *version,
    const char *identifier, const char *title,
    int screenWidth, int screenHeight):
    appName(name),
    appVersion(version),
    appIdentifier(identifier),
    windowTitle(title),
    appScreenWidth(screenWidth),
    appScreenHeight(screenHeight)
{}

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

    return SDL_APP_CONTINUE;
}

void MainApp::Quit(void *appstate, SDL_AppResult result) {}
