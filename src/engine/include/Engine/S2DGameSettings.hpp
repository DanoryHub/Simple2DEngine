//
// Created by IvanMiatselski on 30.06.2026.
//

#ifndef ENGINE_S2DGAMESETTINGS_HPP
#define ENGINE_S2DGAMESETTINGS_HPP

#include <string>
#include <memory>

namespace S2D {

class GameScene;

class GameSettings {
public:
    virtual ~GameSettings() = default;
    virtual std::string GetName() const = 0;
    virtual std::string GetTitle() const = 0;
    virtual std::string GetVersion() const = 0;
    virtual std::string GetIdentifier() const = 0;
    virtual int GetWindowWidth() const = 0;
    virtual int GetWindowHeight() const = 0;
    virtual std::string GetInitialSceneName() const = 0;
};

} // namespace S2D

extern std::shared_ptr<S2D::GameSettings> CreateGameSettings();

#endif //ENGINE_S2DGAMESETTINGS_HPP
