//
// Created by IvanMiatselski on 02.06.2026.
//

#include "Engine/S2DMainApp.hpp"
#include "Engine/S2DGameScene.hpp"
#include "Engine/S2DRenderContext.hpp"
#include "Engine/S2DCollisionDetectionSystem.hpp"

#include <utility>

#include "SDL3/SDL.h"
#include "SDL3_mixer/SDL_mixer.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"


MainApp::MainApp(
    std::string name, std::string version,
    std::string identifier, std::string title, std::string mainSceneName,
    int screenWidth, int screenHeight):
    appScreenWidth(screenWidth),
    appScreenHeight(screenHeight),
    startSceneName(std::move(mainSceneName)),
    appVersion(std::move(version)),
    appName(std::move(name)),
    appIdentifier(std::move(identifier)),
    windowTitle(std::move(title)) {
    currSceneName = startSceneName;
    UpdateCurrScene(currSceneName);
}

void MainApp::SetScenes(const std::unordered_map<std::string, std::shared_ptr<S2DGameScene>> &newScenes) {
    scenes = newScenes;
    UpdateCurrScene(currSceneName);
}

void MainApp::UpdateCurrScene(const std::string &nextSceneName) {
    if (!scenes.empty()) {
        currScene = scenes[nextSceneName];

        collisionSystem->clearCollidables();
        for (auto collidable: currScene->getAllCollidables()){
            collisionSystem->registerCollidable(collidable);
        }

        currentContext->registerCamera(currScene->getSceneCamera());

        if (soundMixer != nullptr){
            currScene->passDeviceAudioMixer(soundMixer);
        }
    }
}

MainApp::~MainApp() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (mainWindow != nullptr) {
        SDL_DestroyWindow(mainWindow);
    }
    SDL_Quit();
}

SDL_AppResult MainApp::Init(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata(appName.c_str(), appVersion.c_str(), appIdentifier.c_str());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL: Cant initialize video subsystem with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(windowTitle.c_str(), appScreenWidth, appScreenHeight, SDL_WINDOW_RESIZABLE, &mainWindow, &renderer)) {
        SDL_Log("SDL: Cant create window or renderer with error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!MIX_Init()){
        SDL_Log("SDL: Cant initialize SDL mixer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_AudioSpec audioSpec;
    audioSpec.freq = 44100;
    audioSpec.format = SDL_AUDIO_S16LE;
    audioSpec.channels = 2;

    soundMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec);
    if (!soundMixer){
        SDL_Log("SDL: Cant create mixer device: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetWindowMinimumSize(mainWindow, minAppScreenWidth, minAppScreenHeight);

    collisionSystem = std::make_shared<S2DCollisionDetectionSystem>(appScreenHeight, appScreenWidth);

    ImGui::StyleColorsLight();
    ImGui_ImplSDL3_InitForSDLRenderer(mainWindow, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    currentContext = std::make_shared<S2DRenderContext>();
    currentContext->registerRenderer(renderer);
    currentContext->setLogicalSize(appScreenWidth, appScreenHeight);

    currentTime = std::chrono::steady_clock::now();

    SetScenes(InitializeScenes());

    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::ProcessEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    currScene->receiveInput(event);
    ImGui_ImplSDL3_ProcessEvent(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult MainApp::Iterate(void *appstate) {
    auto newTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> deltaTime = newTime - currentTime;
    currentTime = newTime;
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    collisionSystem->checkAllCollisions(currentContext->getRenderer(), currentContext->getCameraPosition(), currentContext->getCameraScale());
    currScene->Iterate(deltaTime.count());
    currScene->Render(currentContext);
    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void MainApp::Quit(void *appstate, SDL_AppResult result) {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
