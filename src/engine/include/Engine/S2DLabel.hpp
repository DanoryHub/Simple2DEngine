//
// Created by ivan_miatselski on 2026-08-17.
//

#ifndef ENGINE_S2DLABEL_H
#define ENGINE_S2DLABEL_H

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DVector4.hpp"

#include <string>

S2DENGINE_NAMESPACE_BEGIN

struct Label {
    float textSize = 0.f;
    std::string text = "text";
    std::string fontSource;
    S2D::Vector4<float> textColor = S2D::Vector4<float>(0.f, 0.f, 0.f, 0.f);
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DLABEL_H
