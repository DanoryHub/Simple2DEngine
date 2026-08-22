//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ARCANOID_ARCANOIDPLACEABLE_HPP
#define ARCANOID_ARCANOIDPLACEABLE_HPP

#include "Engine/S2DPlaceable.hpp"
#include "Engine/S2DMovable.hpp"


class ArcanoidPlaceable: public S2DMovable{
protected:
    float speedMax = 90.f;

    float rotationSpeedMax = 30.f;
    float currentRotationDeg = 0.f;
    float currMovingSpeed = 0.f;

    bool movingForward = false;
    bool movingBackward = false;
    bool rotatingLeft = false;
    bool rotatingRight = false;

    S2DVector2<float> fwdVec = S2DVector2<float>(0, -1);

public:
    ArcanoidPlaceable(const std::string& newTexturePath);

    void Iterate(float deltaTime) override;
    void moveForward();
    void moveBackward();
    void rotateRight();
    void rotateLeft();
    void stopRotatingLeft();
    void stopRotatingRight();
    void stopMovingFwd();
    void stopMovingBckwd();
};


#endif //ARCANOID_ARCANOIDPLACEABLE_HPP