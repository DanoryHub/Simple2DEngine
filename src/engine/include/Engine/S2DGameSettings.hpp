//
// Created by IvanMiatselski on 30.06.2026.
//

#ifndef ARCANOID_S2DGAMESETTINGS_HPP
#define ARCANOID_S2DGAMESETTINGS_HPP
#include <string>
#include <unordered_map>


class S2DGameScene;

class S2DGameSettings {
public:
    virtual ~S2DGameSettings() = default;
    virtual std::string GetName() const = 0;
    virtual std::string GetTitle() const = 0;
    virtual std::string GetVersion() const = 0;
    virtual std::string GetIdentifier() const = 0;
    virtual int GetWindowWidth() const = 0;
    virtual int GetWindowHeight() const = 0;
    virtual std::string GetInitialSceneName() const = 0;
    virtual  std::unordered_map<std::string, S2DGameScene*> GetAllScenes() = 0;
};

extern S2DGameSettings* CreateGameSettings();

#endif //ARCANOID_S2DGAMESETTINGS_HPP