//
// Created by ivan_miatselski on 2026-08-17.
//

#ifndef ENGINE_S2DLABEL_H
#define ENGINE_S2DLABEL_H

#include "Engine/S2DVector4.hpp"

#include <string>

struct S2DLabel {
    float textSize = 0.f;
    std::string text = "text";
    std::string fontSource;
    S2DVector4<float> textColor = S2DVector4<float>(0.f, 0.f, 0.f, 0.f);
};


#endif //ENGINE_S2DLABEL_H
