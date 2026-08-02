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

template <typename targetType>
concept MatrixType = std::is_arithmetic_v<targetType>;
template <MatrixType targetType>
class S2DMatrix {
public:

    S2DMatrix();
    S2DMatrix(size_t xy);
    S2DMatrix(size_t x, size_t y);

    targetType& operator()(size_t x, size_t y);
    const targetType& operator()(size_t x, size_t y) const;
    S2DMatrix<targetType> operator*(const S2DMatrix<targetType>& other) const;
    S2DVector2<targetType> operator*(const S2DVector2<targetType>& other) const;

    void populate(const std::vector<targetType>& otherData);
    S2DMatrix<targetType> copySelf();
    std::array<size_t, 2> getSize() const;

    static S2DMatrix<targetType> Identity(size_t iSize);
    static S2DMatrix<targetType> Translation(targetType x, targetType y);
    static S2DMatrix<targetType> Scaling(targetType xScale, targetType yScale);
    static S2DMatrix<targetType> Rotation(float angle);

protected:
    size_t rowLength = 0;
    size_t dataLengthThreshold = 0;
    std::array<size_t, 2> matrixSize{};
    std::vector<targetType> data;

    static bool isSafeMatrixSize(size_t xy);
    static bool isSafeMatrixSize(size_t x, size_t y);
};

#include "S2DMatrix.ipp"

#endif //ENGINE_S2DMATRIX_HPP