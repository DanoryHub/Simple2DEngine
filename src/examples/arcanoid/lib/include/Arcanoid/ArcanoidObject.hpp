//
// Created by IvanMiatselski on 02.07.2026.
//

#ifndef ARCANOID_ARCANOIDOBJECT_HPP
#define ARCANOID_ARCANOIDOBJECT_HPP

#include "Engine/S2DGameObject.hpp"

class ArcanoidObject: public S2D::GameObject {
public:
    void Iterate(float deltaTime) override;
};


#endif //ARCANOID_ARCANOIDOBJECT_HPP