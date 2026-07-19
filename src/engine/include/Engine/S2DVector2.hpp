//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ENGINE_S2DVECTOR2_HPP
#define ENGINE_S2DVECTOR2_HPP

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

    S2DVector2<targetType>& operator+=(targetType scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    S2DVector2<targetType>& operator+=(const S2DVector2<targetType>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    S2DVector2<targetType> operator+(targetType scalar) const {
        S2DVector2<targetType> result = *this;
        result += scalar;
        return result;
    }

    S2DVector2<targetType> operator+(const S2DVector2<targetType>& other) const {
        S2DVector2<targetType> result = *this;
        result += other;
        return result;
    }

    S2DVector2<targetType>& operator-=(targetType scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    S2DVector2<targetType>& operator-=(const S2DVector2<targetType>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    S2DVector2<targetType> operator-(targetType scalar) const {
        S2DVector2<targetType> result = *this;
        result -= scalar;
        return result;
    }

    S2DVector2<targetType> operator-(const S2DVector2<targetType>& other) const {
        S2DVector2<targetType> result = *this;
        result -= other;
        return result;
    }

    S2DVector2<targetType> operator*(targetType scalar) const {
        S2DVector2<targetType> result = *this;
        result *= scalar;
        return result;
    }

    S2DVector2<targetType> operator*(S2DVector2<targetType>& other) const {
        S2DVector2<targetType> result = *this;
        result *= other;
        return result;
    }

    S2DVector2<targetType>& operator*=(targetType scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    S2DVector2<targetType>& operator*=(const S2DVector2<targetType>& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    S2DVector2<targetType> operator/(targetType scalar) const {
        S2DVector2<targetType> result = *this;
        result /= scalar;
        return result;
    }

    S2DVector2<targetType> operator/(const S2DVector2<targetType>& other) const {
        S2DVector2<targetType> result = *this;
        result /= other;
        return result;
    }

    S2DVector2<targetType>& operator/=(targetType scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    S2DVector2<targetType>& operator/=(const S2DVector2<targetType>& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    bool operator==(const S2DVector2<targetType>& other) const{
        return x == other.x && y == other.y;
    }

    targetType Length() const {
        return static_cast<targetType>(sqrt(x * x + y * y));
    }

    S2DVector2<targetType> Normalize() const {
        targetType length = Length();
        if (length > 0) {
            return *this / length;
        }
        return *this;
    }

    targetType DotProduct(const S2DVector2<targetType>& other) const {
        return x * other.x + y * other.y;
    }
};


#endif //ENGINE_S2DVECTOR2_HPP