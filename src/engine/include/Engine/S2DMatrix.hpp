//
// Created by IvanMiatselski on 01.08.2026.
//

#ifndef ENGINE_S2DMATRIX_HPP
#define ENGINE_S2DMATRIX_HPP

#include <array>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <type_traits>

#include "Engine/S2DVector2.hpp"

namespace S2D {

template <typename targetType>
concept MatrixType = std::is_arithmetic_v<targetType>;

template <MatrixType targetType>
class Matrix {
public:

    Matrix();
    Matrix(size_t xy);
    Matrix(size_t x, size_t y);

    targetType& operator()(size_t x, size_t y);
    const targetType& operator()(size_t x, size_t y) const;
    Matrix<targetType> operator*(const Matrix<targetType>& other) const;
    S2D::Vector2<targetType> operator*(const S2D::Vector2<targetType>& other) const;

    void populate(const std::vector<targetType>& otherData);
    Matrix<targetType> copySelf();
    std::array<size_t, 2> getSize() const;

    static Matrix<targetType> Identity(size_t iSize);
    static Matrix<targetType> Translation(targetType x, targetType y);
    static Matrix<targetType> Scaling(targetType xScale, targetType yScale);
    static Matrix<targetType> Rotation(float angle);

protected:
    size_t rowLength = 0;
    size_t dataLengthThreshold = 0;
    std::array<size_t, 2> matrixSize{};
    std::vector<targetType> data;

    static bool isSafeMatrixSize(size_t xy);
    static bool isSafeMatrixSize(size_t x, size_t y);
};

} // namespace S2D

#include "S2DMatrix.ipp"

#endif //ENGINE_S2DMATRIX_HPP
