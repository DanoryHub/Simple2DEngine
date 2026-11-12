//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIITERABLE_HPP
#define ARCANOID_S2DIITERABLE_HPP

#include "Engine/S2DHelpers.hpp"

S2DENGINE_NAMESPACE_BEGIN

class IIterable {
public:
    virtual ~IIterable() {};
    virtual void Iterate(float deltaTime) = 0;
};

S2DENGINE_NAMESPACE_END

#endif //ARCANOID_S2DIITERABLE_HPP
