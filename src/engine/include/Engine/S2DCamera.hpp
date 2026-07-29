//
// Created by IvanMiatselski on 29.07.2026.
//

#ifndef ARCANOID_S2DCAMERA_HPP
#define ARCANOID_S2DCAMERA_HPP

#include "Engine/S2DVector2.hpp"

class S2DCamera {
protected:
    S2DVector2<float>* cameraPosition;

public:
    S2DCamera();
    ~S2DCamera();

    S2DVector2<float>* getCameraPosition() const;
    void setCameraPosition(const S2DVector2<float>* cameraPosition);
};


#endif //ARCANOID_S2DCAMERA_HPP