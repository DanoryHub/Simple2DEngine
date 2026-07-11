#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DGameSettings.hpp"


S2DGameSettings* gameSettings;
MainApp *mainApp;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    gameSettings = CreateGameSettings();

    mainApp = MainApp::GetInstance(
        gameSettings->GetName(), gameSettings->GetVersion(),
        gameSettings->GetIdentifier(), gameSettings->GetTitle(),
        gameSettings->GetInitialSceneName()
    );

    if (!mainApp) {
        SDL_Log("mainApp is not valid");
        return SDL_APP_FAILURE;
    }

    SDL_AppResult res = mainApp->Init(appstate, argc, argv);

    mainApp->SetScenes(gameSettings->GetAllScenes());

    return res;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (!mainApp) {
        SDL_Log("mainApp is not valid");
        return SDL_APP_FAILURE;
    }

    return mainApp->ProcessEvent(appstate, event);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    if (!mainApp) {
        SDL_Log("mainApp is not valid");
        return SDL_APP_FAILURE;
    }

    return mainApp->Iterate(appstate);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (!mainApp) {
        SDL_Log("mainApp is not valid");
        return;
    }

    mainApp->Quit(appstate, result);
}