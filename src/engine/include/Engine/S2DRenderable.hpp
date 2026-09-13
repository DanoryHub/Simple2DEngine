//
// Created by ivan_miatselski on 2026-08-30.
//

#ifndef ENGINE_S2DRENDERABLE_HPP
#define ENGINE_S2DRENDERABLE_HPP

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DIRenderable.hpp"

#include <string>

class S2DRenderContext;

class S2DRenderable: public S2DPlaceable, public S2DIRenderable{
protected:
    std::string texturePath;

public:
    S2DRenderable(const std::string &newTexturePath);
    ~S2DRenderable() override;

    void Render(const std::shared_ptr<S2DRenderContext>& renderContext) override;
};


#endif //ENGINE_S2DRENDERABLE_HPP
