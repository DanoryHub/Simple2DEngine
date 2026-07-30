//
// Created by IvanMiatselski on 24.07.2026.
//

#ifndef ARCANOID_S2DRENDERCONTEXT_HPP
#define ARCANOID_S2DRENDERCONTEXT_HPP

#include "Engine/S2DCamera.hpp"
#include "SDL3/SDL.h"

struct S2DRenderContext {
    SDL_Renderer* renderer;
    S2DCamera* currCamera;
};

#endif //ARCANOID_S2DRENDERCONTEXT_HPP