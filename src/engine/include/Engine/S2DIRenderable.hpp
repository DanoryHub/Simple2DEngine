//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIRENDERABLE_HPP
#define ARCANOID_S2DIRENDERABLE_HPP

#include <memory>

namespace S2D {

class RenderContext;

class IRenderable {
public:
    virtual ~IRenderable() {};
    virtual void Render(const std::shared_ptr<S2D::RenderContext>& renderContext) = 0;
};

} // namespace S2D

#endif //ARCANOID_S2DIRENDERABLE_HPP
