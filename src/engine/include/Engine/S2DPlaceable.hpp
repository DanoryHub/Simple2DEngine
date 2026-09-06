//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ENGINE_S2DPLACEABLE_HPP
#define ENGINE_S2DPLACEABLE_HPP

#include <memory>
#include <string>

#include "Engine/S2DVector2.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DIRenderable.hpp"
#include "SDL3/SDL_render.h"

struct SDL_Renderer;
class S2DRenderContext;
class S2DTexture;

class S2DPlaceable: virtual public S2DGameObject{
protected:
    S2DVector2<float> position = S2DVector2<float>(0.f, 0.f);
    S2DVector2<float> scale = S2DVector2<float>(1.f, 1.f);
    S2DVector2<float> baseScale = S2DVector2<float>(1.f, 1.f);
    float rotation = 0.f;
public:
    S2DPlaceable();

    S2DVector2<float> GetPosition() const;
    void SetPosition(const S2DVector2<float>& newPosition);

    S2DVector2<float> GetScale() const;
    void SetScale(const S2DVector2<float>& newScale);

    float GetRotation() const;
    void SetRotation(float newRotation);
};


#endif //ENGINE_S2DPLACEABLE_HPP