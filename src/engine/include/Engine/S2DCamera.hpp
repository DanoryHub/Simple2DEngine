//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ENGINE_S2DCAMERA_HPP
#define ENGINE_S2DCAMERA_HPP

#include "Engine/S2DVector2.hpp"

namespace S2D {

class Camera {
protected:
    S2D::Vector2<float> cameraPosition{0, 0};
    S2D::Vector2<float> cameraScale{1, 1};
    float cameraRotation = 0.f;

public:
    Camera();
    ~Camera();

    S2D::Vector2<float> getPosition() const;
    void setPosition(const S2D::Vector2<float>& value);

    S2D::Vector2<float> getScale() const;
    void setScale(const S2D::Vector2<float>& value);

    float getRotation() const;
    void setRotation(float cameraRotation);
};

} // namespace S2D

#endif //ENGINE_S2DCAMERA_HPP
