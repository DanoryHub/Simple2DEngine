//
// Created by IvanMiatselski on 09.07.2026.
//

#ifndef ENGINE_S2DVECTOR2_HPP
#define ENGINE_S2DVECTOR2_HPP

#include <cmath>
#include <type_traits>

namespace S2D {

template <typename targetType>
concept VectorType = std::is_arithmetic_v<targetType>;

template <VectorType targetType>
struct Vector2 {
    targetType x, y;

    Vector2() : x(0), y(0) {}
    Vector2(targetType x, targetType y) : x(x), y(y) {}

    template <VectorType otherType>
    Vector2(const Vector2<otherType>& other) :
        x(static_cast<targetType>(other.x)), y(static_cast<targetType>(other.y)){}

    Vector2<targetType>& operator+=(targetType scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2<targetType>& operator+=(const Vector2<targetType>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2<targetType> operator+(targetType scalar) const {
        Vector2<targetType> result = *this;
        result += scalar;
        return result;
    }

    Vector2<targetType> operator+(const Vector2<targetType>& other) const {
        Vector2<targetType> result = *this;
        result += other;
        return result;
    }

    Vector2<targetType>& operator-=(targetType scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vector2<targetType>& operator-=(const Vector2<targetType>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2<targetType> operator-(targetType scalar) const {
        Vector2<targetType> result = *this;
        result -= scalar;
        return result;
    }

    Vector2<targetType> operator-(const Vector2<targetType>& other) const {
        Vector2<targetType> result = *this;
        result -= other;
        return result;
    }

    Vector2<targetType> operator*(targetType scalar) const {
        Vector2<targetType> result = *this;
        result *= scalar;
        return result;
    }

    Vector2<targetType> operator*(Vector2<targetType>& other) const {
        Vector2<targetType> result = *this;
        result *= other;
        return result;
    }

    Vector2<targetType>& operator*=(targetType scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2<targetType>& operator*=(const Vector2<targetType>& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2<targetType> operator/(targetType scalar) const {
        Vector2<targetType> result = *this;
        result /= scalar;
        return result;
    }

    Vector2<targetType> operator/(const Vector2<targetType>& other) const {
        Vector2<targetType> result = *this;
        result /= other;
        return result;
    }

    Vector2<targetType>& operator/=(targetType scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2<targetType>& operator/=(const Vector2<targetType>& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    bool operator==(const Vector2<targetType>& other) const{
        return x == other.x && y == other.y;
    }

    targetType Length() const {
        return static_cast<targetType>(std::sqrt(x * x + y * y));
    }

    Vector2<targetType> Normalize() const {
        targetType length = Length();
        if (length > 0) {
            return *this / length;
        }
        return *this;
    }

    targetType DotProduct(const Vector2<targetType>& other) const {
        return x * other.x + y * other.y;
    }
};

} // namespace S2D

#endif //ENGINE_S2DVECTOR2_HPP
