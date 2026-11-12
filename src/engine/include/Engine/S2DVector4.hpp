//
// Created by ivan_miatselski on 2026-08-16.
//

#ifndef ENGINE_S2DVECTOR4_HPP
#define ENGINE_S2DVECTOR4_HPP

#include "Engine/S2DHelpers.hpp"
#include "Engine/S2DVector2.hpp"

S2DENGINE_NAMESPACE_BEGIN

template <VectorType targetType>
struct Vector4 {
    targetType x, y, z, w;
};

S2DENGINE_NAMESPACE_END

#endif //ENGINE_S2DVECTOR4_HPP
