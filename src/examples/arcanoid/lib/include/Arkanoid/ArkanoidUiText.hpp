#ifndef ARKANOID_ARCANOIDUITEXT_HPP
#define ARKANOID_ARCANOIDUITEXT_HPP

#include "Arkanoid/ArkanoidConfig.hpp"

#include "Engine/S2DText.hpp"

#include <string>

namespace Arkanoid {

// S2D::Text exposes its label only as protected state.  Deriving from the
// engine widget lets the game update score/level/lives text while still
// rendering through the engine's UI path.
class UiText final: public S2D::Text {
public:
    UiText(const std::string& text,
           const S2D::Vector2<float>& position,
           float size,
           const S2D::Vector4<float>& color);

    void setLabel(const std::string& text);
    void setColor(const S2D::Vector4<float>& color);
    void setWindowPosition(const S2D::Vector2<float>& position);
};

} // namespace Arkanoid

#endif // ARKANOID_ARCANOIDUITEXT_HPP
