//
// Created by IvanMiatselski on 02.06.2026.
//

#ifndef ENGINE_S2DMAINAPP_HPP
#define ENGINE_S2DMAINAPP_HPP

#include "SDL3/SDL.h"

#include <unordered_map>
#include <string>
#include <chrono>

class S2DGameScene;
struct S2DRenderContext;

class MainApp {
public:
        MainApp(MainApp const&) = delete;
        ~MainApp();
        void operator=(MainApp const&) = delete;

        static MainApp* GetInstance(
            const std::string &name, const std::string &version,
            const std::string &identifier, const std::string &title, const std::string &mainSceneName,
            const int screenWidth = 1920, const int screenHeight = 1080);
        static MainApp* GetInstance();

        void SetScenes(const std::unordered_map<std::string, S2DGameScene*> &newScenes);

        SDL_Renderer* GetRenderer() const;

        SDL_AppResult Init(void **appstate, int argc, char *argv[]);
        SDL_AppResult ProcessEvent(void *appstate, SDL_Event *event);
        SDL_AppResult Iterate(void *appstate);
        void Quit(void* appstate, SDL_AppResult result);

        void UpdateCurrScene(const std::string &nextSceneName);
private:
        MainApp(std::string name, std::string version,
                std::string identifier, std::string title, std::string mainSceneName,
                int screenWidth = 1920, int screenHeight = 1080);

        static MainApp* mainApp;

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

        S2DRenderContext *currentContext;

};

extern std::unordered_map<std::string, S2DGameScene*> InitializeScenes(SDL_Renderer* renderer);

#endif //ENGINE_S2DMAINAPP_HPP