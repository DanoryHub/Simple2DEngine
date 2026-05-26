#include <string>
#include "stdlib.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"
#include "render/texture.h"

constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

SDL_Window* gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

S2DTexture *pngTexture;

int main(int argc, char* argv[]){
    return 0;
}