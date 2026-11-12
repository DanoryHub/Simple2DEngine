//
// Created by IvanMiatselski on 02.06.2026.
//

#ifndef ENGINE_S2DMAINAPP_HPP
#define ENGINE_S2DMAINAPP_HPP

#include "Engine/S2DHelpers.hpp"

#include "SDL3/SDL.h"

#include <unordered_map>
#include <string>
#include <chrono>
#include <memory>

struct MIX_Mixer;

S2DENGINE_NAMESPACE_BEGIN

class GameScene;
class RenderContext;
class CollisionDetectionSystem;

S2DENGINE_NAMESPACE_END

class MainApp {
public:
        MainApp() = default;
        MainApp(std::string name, std::string version,
            std::string identifier, std::string title, std::string mainSceneName,
            int screenWidth = 1920, int screenHeight = 1080);

        ~MainApp();
        void operator=(MainApp const&) = delete;
        void SetScenes(const std::unordered_map<std::string, std::shared_ptr<S2D::GameScene>> &newScenes);

        SDL_AppResult Init(void **appstate, int argc, char *argv[]);
        SDL_AppResult ProcessEvent(void *appstate, SDL_Event *event);
        SDL_AppResult Iterate(void *appstate);
        void Quit(void* appstate, SDL_AppResult result);

        void UpdateCurrScene(const std::string &nextSceneName);
private:
        int appScreenWidth, appScreenHeight;
        int minAppScreenWidth = 1280;
        int minAppScreenHeight = 720;

        SDL_Window *mainWindow = nullptr;
        SDL_Renderer *renderer = nullptr;
        MIX_Mixer* soundMixer = nullptr;

        std::shared_ptr<S2D::GameScene> currScene = nullptr;

        std::string startSceneName;
        std::string currSceneName;
        std::unordered_map<std::string, std::shared_ptr<S2D::GameScene>> scenes;

        std::string appVersion, appName, appIdentifier;
        std::string windowTitle;

        std::chrono::time_point<std::chrono::steady_clock> currentTime;
        double physSimDeltaTime = .01;

        std::shared_ptr<S2D::RenderContext> currentContext;
        std::shared_ptr<S2D::CollisionDetectionSystem> collisionSystem;

};

extern std::unordered_map<std::string, std::shared_ptr<S2D::GameScene>> InitializeScenes();

#endif //ENGINE_S2DMAINAPP_HPP
