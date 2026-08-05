#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DGameSettings.hpp"

struct AppState {
    std::shared_ptr<S2DGameSettings> gameSettings;
    std::shared_ptr<MainApp> mainApp;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    auto *state = new AppState();
    state->gameSettings = CreateGameSettings();

    state->mainApp = std::make_shared<MainApp>(
        state->gameSettings->GetName(), state->gameSettings->GetVersion(),
        state->gameSettings->GetIdentifier(), state->gameSettings->GetTitle(),
        state->gameSettings->GetInitialSceneName()
    );

    SDL_AppResult res = state->mainApp->Init(appstate, argc, argv);

    *appstate = state;
    return res;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    auto *state = static_cast<AppState*>(appstate);

    if (!state->mainApp) {
        SDL_Log("mainApp is not valid");
        return SDL_APP_FAILURE;
    }

    return state->mainApp->ProcessEvent(appstate, event);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    auto *state = static_cast<AppState*>(appstate);
    if (!state->mainApp) {
        SDL_Log("mainApp is not valid");
        return SDL_APP_FAILURE;
    }

    return state->mainApp->Iterate(appstate);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    auto *state = static_cast<AppState*>(appstate);
    if (!state->mainApp) {
        SDL_Log("mainApp is not valid");
        return;
    }

    state->mainApp->Quit(appstate, result);
    delete state;
}