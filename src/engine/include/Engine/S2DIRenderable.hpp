//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIRENDERABLE_HPP
#define ARCANOID_S2DIRENDERABLE_HPP

#include "Engine/S2DHelpers.hpp"

#include <memory>

S2DENGINE_NAMESPACE_BEGIN

class RenderContext;

class IRenderable {
public:
    virtual ~IRenderable() {};
    virtual void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) = 0;
};

S2DENGINE_NAMESPACE_END

#endif //ARCANOID_S2DIRENDERABLE_HPP
