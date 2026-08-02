//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DCAMERA_HPP
#define ARCANOID_S2DCAMERA_HPP

#include "Engine/S2DVector2.hpp"

class S2DCamera {
protected:
    S2DVector2<float> cameraPosition{0, 0};
    S2DVector2<float> cameraScale{1, 1};
    float cameraRotation = 0.f;

public:
    S2DCamera();
    ~S2DCamera();

    S2DVector2<float> getPosition() const;
    void setPosition(const S2DVector2<float>* cameraPosition);

    S2DVector2<float> getScale() const;
    void setScale(const S2DVector2<float>* cameraScale);

    float getRotation() const;
    void setRotation(float cameraRotation);
};


#endif //ARCANOID_S2DCAMERA_HPP