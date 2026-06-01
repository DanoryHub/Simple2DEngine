#include <string>
#include "stdlib.h"

#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"

#include <random>

#include "render/texture.h"


constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

SDL_Window* window = nullptr;
SDL_Renderer *renderer = nullptr;

const SDL_FPoint *leaves = new SDL_FPoint[9]{
    { 100, 354 }, { 220, 230 }, { 140, 230 }, { 320, 100 }, { 500, 230 },
    { 420, 230 }, { 540, 354 }, { 400, 354 }, { 100, 354 }
};
SDL_FPoint *trunk = new SDL_FPoint[4];

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLines(renderer, leaves, 9);

    SDL_SetRenderDrawColor(renderer, 127, 49, 32, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(renderer, 240, 450, 400, 450);
    SDL_RenderLine(renderer, 240, 356, 400, 356);
    SDL_RenderLine(renderer, 240, 356, 240, 450);
    SDL_RenderLine(renderer, 400, 356, 400, 450);

    for (int i = 0; i < 360; i++) {
        const float size = 30.0f;
        const float x = 320.0f;
        const float y = 95.0f - (size / 2.0f);
        const float r = (float) i * (SDL_PI_F / 180.0f);
        SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, x, y, x + SDL_cosf(r) * size, y + SDL_sinf(r) * size);
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    // Do nofin
}