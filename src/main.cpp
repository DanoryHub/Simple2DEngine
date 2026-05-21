#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int main(int argc, char** argv)
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    return -1;
  }

  SDL_Quit();

  return 0;
}