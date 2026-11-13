//
// Created by IvanMiatselski on 30.06.2026.
//

#include "Engine/S2DGameSettings.hpp"

#define TJ_INCLUDE_STD_STRING 1
#include <TinyJSON.h>

#include <memory>
#include <stdexcept>

namespace S2D {

GameSettings::GameSettings(const std::string& configFilePath) {
    LoadFromJson(configFilePath);
}

void GameSettings::LoadFromJson(const std::string& configFilePath) {
    TinyJSON::parse_options parseOptions;
    parseOptions.throw_exception = true;
    parseOptions.strict = true;

    std::unique_ptr<TinyJSON::TJValue> document;
    try {
        document.reset(TinyJSON::TJ::parse_file(configFilePath.c_str(), parseOptions));
    } catch (const TinyJSON::TJParseException& exception) {
        throw std::runtime_error(
            "Failed to read game settings from " + configFilePath + ": " + exception.what());
    }

    const auto* documentObject = dynamic_cast<const TinyJSON::TJValueObject*>(document.get());
    if (documentObject == nullptr) {
        throw std::runtime_error("Game settings file root must be a JSON object: " + configFilePath);
    }

    const auto* settings = dynamic_cast<const TinyJSON::TJValueObject*>(
        documentObject->try_get_value("settings"));
    if (settings == nullptr) {
        throw std::runtime_error(
            "Game settings file is missing the \"settings\" object: " + configFilePath);
    }

    try {
        name = settings->get<std::string>("name");
        title = settings->get<std::string>("title");
        version = settings->get<std::string>("version");
        identifier = settings->get<std::string>("identifier");
        windowWidth = settings->get<int>("windowWidth");
        windowHeight = settings->get<int>("windowHeight");
        initialSceneName = settings->get<std::string>("initialSceneName");
    } catch (const TinyJSON::TJParseException& exception) {
        throw std::runtime_error(
            "Failed to read game settings from " + configFilePath + ": " + exception.what());
    }
}

std::string GameSettings::GetName() const {
    return name;
}

std::string GameSettings::GetTitle() const {
    return title;
}

std::string GameSettings::GetVersion() const {
    return version;
}

std::string GameSettings::GetIdentifier() const {
    return identifier;
}

int GameSettings::GetWindowWidth() const {
    return windowWidth;
}

int GameSettings::GetWindowHeight() const {
    return windowHeight;
}

std::string GameSettings::GetInitialSceneName() const {
    return initialSceneName;
}

} // namespace S2D
