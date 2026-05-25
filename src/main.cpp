#include <string>
#include "stdlib.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gHelloWorld = nullptr;

constexpr int EXIT_OK = 0;
constexpr int EXIT_WINDOW_LOAD_ERROR = 1;
constexpr int EXIT_MEDIA_LOAD_ERROR = 2;


bool init() {

  bool success = true;

  // Init SDL video subsystem
  if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Create main window
  gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0);
  if (gWindow == nullptr) {
    SDL_Log("Faled to initialize SDL window with error: %s\n", SDL_GetError());
    return  false;
  }

  // Init surface ref
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return success;
};

bool loadMedia() {
  bool success = true;
  // Load bmp image into hello world vaeiable
  std::string mediaPath = "./media/hello-sdl3/hello-sdl3.bmp";
  gHelloWorld = SDL_LoadBMP(mediaPath.c_str());
  if (gHelloWorld == nullptr) {
    SDL_Log("Faled to load media with error: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

void close(){
  SDL_DestroySurface( gHelloWorld );
  gHelloWorld = nullptr;

  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gScreenSurface = nullptr;

  SDL_Quit();
}


int main(int argc, char* argv[]){
  int exitCode = EXIT_OK;

  if (!init()) {
    SDL_Log("Failed to initialize main loop!\n");
    return EXIT_WINDOW_LOAD_ERROR;
  }

  if (!loadMedia()) {
    SDL_Log("Failed to load media!\n");
    return EXIT_MEDIA_LOAD_ERROR;
  }

  bool bQuit = false;

  SDL_Event event;
  SDL_zero(event);

  while (!bQuit) {
    while (SDL_PollEvent(&event)) {
      // SDL events processing
      if (event.type == SDL_EVENT_QUIT) {
        //Exit main loop
        bQuit = true;
      }
    }
    SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);
  }

  // Cleanup
  close();
  return exitCode;
}