//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Engine/S2DGameObject.hpp"

namespace S2D {

void GameObject::setName(const std::string& name) {
    objectName = name;
}

const std::string& GameObject::getName() const {
    return objectName;
}

void GameObject::Iterate(float deltaTime) {}

} // namespace S2D
