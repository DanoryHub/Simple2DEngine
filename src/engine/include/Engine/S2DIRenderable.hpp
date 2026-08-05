//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DIRENDERABLE_HPP
#define ARCANOID_S2DIRENDERABLE_HPP

#include <memory>

class S2DRenderContext;

class S2DIRenderable {
public:
    virtual ~S2DIRenderable() {};
    virtual void Render(std::shared_ptr<S2DRenderContext> renderContext) = 0;
};

#endif //ARCANOID_S2DIRENDERABLE_HPP