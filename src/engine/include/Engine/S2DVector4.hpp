//
// Created by ivan_miatselski on 2026-08-16.
//

#ifndef ENGINE_S2DVECTOR4_HPP
#define ENGINE_S2DVECTOR4_HPP

#include "S2DVector2.hpp"

template <VectorType targetType>
struct S2DVector4 {
    targetType x, y, z, w;
};

#endif //ENGINE_S2DVECTOR4_HPP
