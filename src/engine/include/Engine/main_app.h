//
// Created by IvanMiatselski on 02.06.2026.
//

#ifndef SIMPLE2DENGINE_MAIN_APP_H
#define SIMPLE2DENGINE_MAIN_APP_H

#include "SDL3/SDL.h"

class MainApp {
public:
        MainApp(
                const char* name, const char* version,
                const char* identifier, const char* title,
                int screenWidth = 1920, int screenHeight = 1080
                );

        ~MainApp();

        SDL_AppResult Init(void **appstate, int argc, char *argv[]);

        SDL_AppResult ProcessEvent(void *appstate, SDL_Event *event);

        SDL_AppResult Iterate(void *appstate);

        void Quit(void* appstate, SDL_AppResult result);

private:
        int appScreenWidth;
        int appScreenHeight;

        SDL_Window *mainWindow = nullptr;
        SDL_Renderer *renderer = nullptr;

        const char *appVersion, *appName, *appIdentifier;
        const char *windowTitle;
};

#endif //SIMPLE2DENGINE_MAIN_APP_H