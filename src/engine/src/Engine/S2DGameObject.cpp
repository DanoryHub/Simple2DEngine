//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameObject.hpp"

void S2DGameObject::setName(const std::string& name) {
    objectName = name;
}

const std::string& S2DGameObject::getName() const {
    return objectName;
}

void S2DGameObject::Iterate(float deltaTime) {}

