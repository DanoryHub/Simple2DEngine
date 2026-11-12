//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameObject.hpp"

S2DENGINE_NAMESPACE_BEGIN

void GameObject::setName(const std::string& name) {
    objectName = name;
}

const std::string& GameObject::getName() const {
    return objectName;
}

void GameObject::Iterate(float deltaTime) {}

S2DENGINE_NAMESPACE_END
