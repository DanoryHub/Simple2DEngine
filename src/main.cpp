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

constexpr int NUM_POINTS = 500;
SDL_FPoint *points = new SDL_FPoint[NUM_POINTS];
const SDL_FRect *fillRect;
const SDL_FRect *hollowRect;

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

    fillRect = new SDL_FRect{screenWidth * 0.15, screenHeight * 0.15, screenWidth * 0.7, screenHeight * 0.7};
    hollowRect = new SDL_FRect{screenWidth * 0.2, screenHeight * 0.2, screenWidth * 0.6, screenHeight * 0.6};
    for (int i = 0; i < 500; i++) {
        points[i].x = (SDL_randf() * fillRect->w) + fillRect->x;
        points[i].y = (SDL_randf() * fillRect->h) + fillRect->y;
    }

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

    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render blue filled rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, fillRect);

    // Render random dots in this rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(renderer, points, NUM_POINTS);

    // Render green hollow rectangle
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, hollowRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(renderer, 0, 0, screenWidth, screenHeight);
    SDL_RenderLine(renderer, screenWidth, 0, 0, screenHeight);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    // Do nofin
}