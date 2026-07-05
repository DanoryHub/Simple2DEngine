//
// Created by IvanMiatselski on 02.06.2026.
//

#ifndef SIMPLE2DENGINE_MAIN_APP_H
#define SIMPLE2DENGINE_MAIN_APP_H

#include <unordered_map>
#include <string>
#include <chrono>

class S2DGameScene;
enum SDL_AppResult;

class MainApp {
public:
        MainApp(
                std::string name, std::string version,
                std::string identifier, std::string title, std::string mainSceeneName,
                std::unordered_map<std::string, S2DGameScene*> newScenes,
                int screenWidth = 1920, int screenHeight = 1080
                );
        ~MainApp() = default;
        SDL_AppResult Init(void **appstate, int argc, char *argv[]);
        SDL_AppResult ProcessEvent(void *appstate, SDL_Event *event);
        SDL_AppResult Iterate(void *appstate);
        void Quit(void* appstate, SDL_AppResult result);

        void UpdateCurrScene(const std::string &nextSceneName);
private:
        // Init variables
        int appScreenWidth;
        int appScreenHeight;

        SDL_Window *mainWindow = nullptr;
        SDL_Renderer *renderer = nullptr;

        S2DGameScene *currScene = nullptr;

        std::string startSceneName;
        std::string currSceneName;
        std::unordered_map<std::string, S2DGameScene*> scenes;

        std::string appVersion, appName, appIdentifier;
        std::string windowTitle;

        // Main loop persistent variables
        std::chrono::time_point<std::chrono::steady_clock> currentTime;
        double physSimDeltaTime = .01;

};

#endif //SIMPLE2DENGINE_MAIN_APP_H