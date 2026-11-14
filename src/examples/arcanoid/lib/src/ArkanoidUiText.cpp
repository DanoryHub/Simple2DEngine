#include "Arkanoid/ArkanoidUiText.hpp"

namespace Arkanoid {

UiText::UiText(const std::string& text,
               const S2D::Vector2<float>& position,
               float size,
               const S2D::Vector4<float>& color)
    : S2D::Text(text, position, size) {
    setTextColor(color);
    setTextFont(kUiFontPath, size);
    windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
}

void UiText::setLabel(const std::string& text) {
    textLabel.text = text;
}

void UiText::setColor(const S2D::Vector4<float>& color) {
    setTextColor(color);
}

void UiText::setWindowPosition(const S2D::Vector2<float>& position) {
    windowPos = position;
}

} // namespace Arkanoid
