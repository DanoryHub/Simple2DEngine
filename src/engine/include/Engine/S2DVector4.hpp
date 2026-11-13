//
// Created by ivan_miatselski on 2026-08-16.
//

#ifndef ENGINE_S2DVECTOR4_HPP
#define ENGINE_S2DVECTOR4_HPP

#include "Engine/S2DVector2.hpp"

namespace S2D {

template <VectorType targetType>
struct Vector4 {
    targetType x, y, z, w;
};

} // namespace S2D

#endif //ENGINE_S2DVECTOR4_HPP
