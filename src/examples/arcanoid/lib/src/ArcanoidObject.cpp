//
// Created by IvanMiatselski on 02.07.2026.
//

#include "Arcanoid/ArcanoidObject.hpp"
#include <iostream>

void ArcanoidObject::Iterate(float deltaTime) {
    S2DGameObject::Iterate(deltaTime);

    std::cout << "ArcanoidObject::Iterate, Object " << objectName << std::endl;
}
