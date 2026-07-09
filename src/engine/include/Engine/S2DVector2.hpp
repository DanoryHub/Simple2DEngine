//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ARCANOID_S2DVECTOR2_HPP
#define ARCANOID_S2DVECTOR2_HPP

#include <concepts>

template <typename targetType>
concept VectorType = std::same_as<targetType, int> ||
                        std::same_as<targetType, float> ||
                        std::same_as<targetType, double>;
template <VectorType targetType>
struct S2DVector2 {
    targetType x, y;

    S2DVector2() : x(0), y(0) {}
    S2DVector2(targetType x, targetType y) : x(x), y(y) {}

    template <VectorType otherType>
    S2DVector2(const S2DVector2<otherType>& other) :
        x(static_cast<targetType>(other.x)), y(static_cast<targetType>(other.y)){}
};


#endif //ARCANOID_S2DVECTOR2_HPP