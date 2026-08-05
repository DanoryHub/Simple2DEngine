//
// Created by IvanMiatselski on 30.06.2026.
//

#ifndef ARCANOID_ARCANOIDSETTINGS_HPP
#define ARCANOID_ARCANOIDSETTINGS_HPP
#include <string>

#include "Engine/S2DGameSettings.hpp"

class S2DGameScene;

class ArcanoidSettings: public S2DGameSettings{
public:
    ~ArcanoidSettings() override {};
    std::string GetName() const override;
    std::string GetTitle() const override;
    std::string GetVersion() const override;
    std::string GetIdentifier() const override;
    int GetWindowWidth() const override;
    int GetWindowHeight() const override;
    std::string GetInitialSceneName() const override;
};

#endif //ARCANOID_ARCANOIDSETTINGS_HPP