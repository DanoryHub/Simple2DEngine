//
// Created by IvanMiatselski on 30.06.2026.
//

#ifndef ENGINE_S2DGAMESETTINGS_HPP
#define ENGINE_S2DGAMESETTINGS_HPP

#include <string>
#include <memory>

namespace S2D {

class GameSettings {
public:
    explicit GameSettings(const std::string& configFilePath);
    virtual ~GameSettings() = default;

    virtual std::string GetName() const;
    virtual std::string GetTitle() const;
    virtual std::string GetVersion() const;
    virtual std::string GetIdentifier() const;
    virtual int GetWindowWidth() const;
    virtual int GetWindowHeight() const;
    virtual std::string GetInitialSceneName() const;

private:
    void LoadFromJson(const std::string& configFilePath);

    std::string name;
    std::string title;
    std::string version;
    std::string identifier;
    std::string initialSceneName;
    int windowWidth = 1920;
    int windowHeight = 1080;
};

} // namespace S2D

extern std::shared_ptr<S2D::GameSettings> CreateGameSettings();

#endif //ENGINE_S2DGAMESETTINGS_HPP
