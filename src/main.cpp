#include <string>
#include "stdlib.h"

#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"

#include "render/texture.h"


constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

SDL_Window* window = nullptr;
SDL_Renderer *renderer = nullptr;

S2DTexture *pngTexture;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Simple 2D Engine", "0.0.1", "simple.2d.engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL: Cant initialize video subsystem with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Simple 2D Engine", screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("SDL: Cant create window or renderer with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, screenWidth, screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    // Do things here

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    // Do nofin
}