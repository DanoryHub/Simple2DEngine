//
// Created by IvanMiatselski on 08.07.2026.
//

#ifndef ENGINE_S2DPLACEABLE_HPP
#define ENGINE_S2DPLACEABLE_HPP

#include <memory>
#include <string>

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DVector2.hpp"
#include "Engine/S2DGameObject.hpp"
#include "Engine/S2DIRenderable.hpp"
#include "SDL3/SDL_render.h"

struct SDL_Renderer;

S2DENGINE_NAMESPACE_BEGIN

class RenderContext;
class Texture;

class Placeable: virtual public S2D::GameObject {
protected:
    S2D::Vector2<float> position = S2D::Vector2<float>(0.f, 0.f);
    S2D::Vector2<float> scale = S2D::Vector2<float>(1.f, 1.f);
    S2D::Vector2<float> baseScale = S2D::Vector2<float>(1.f, 1.f);
    float rotation = 0.f;
public:
    Placeable();

    S2D::Vector2<float> GetPosition() const;
    void SetPosition(const S2D::Vector2<float>& newPosition);

    S2D::Vector2<float> GetScale() const;
    void SetScale(const S2D::Vector2<float>& newScale);

    float GetRotation() const;
    void SetRotation(float newRotation);
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DPLACEABLE_HPP
