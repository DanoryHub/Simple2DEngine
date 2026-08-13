//
// Created by IvanMiatselski on 01.08.2026.
//

#ifndef ENGINE_S2DMATRIX_IPP
#define ENGINE_S2DMATRIX_IPP

#include <cmath>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <array>

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix(): matrixSize({0, 0}) {}

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix(const size_t xy):
    rowLength(xy),
    dataLengthThreshold(xy * xy),
    matrixSize({xy, xy})
{
    if (!isSafeMatrixSize(xy)) {
        throw std::invalid_argument("XY matrix size is too big.");
    }

    data = std::vector<targetType>(dataLengthThreshold, static_cast<targetType>(0));
}

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix(const size_t x, const size_t y):
    rowLength(x),
    dataLengthThreshold(x * y),
    matrixSize({x, y})
{
    if (!isSafeMatrixSize(x, y)) {
        throw std::invalid_argument("XY matrix size is too big.");
    }

    data = std::vector<targetType>(dataLengthThreshold, static_cast<targetType>(0));
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::copySelf() {
    S2DMatrix<targetType> resMatrix(matrixSize[0], matrixSize[1]);
    resMatrix.populate(data);
    return resMatrix;
}

template<MatrixType targetType>
void S2DMatrix<targetType>::populate(const std::vector<targetType>& otherData) {
    data = otherData;
}

template<MatrixType targetType>
targetType& S2DMatrix<targetType>::operator()(const size_t x, const size_t y) {
    if (x >= matrixSize[0] || y >= matrixSize[1]) {
        throw std::out_of_range("Matrix index out of range.");
    }

    return data[x + y * rowLength];
}

template<MatrixType targetType>
const targetType& S2DMatrix<targetType>::operator()(const size_t x, const size_t y) const {
    if (x >= matrixSize[0] || y >= matrixSize[1]) {
        throw std::out_of_range("Matrix index out of range.");
    }
    return data[x + y * rowLength];
}

template<MatrixType targetType>
std::array<size_t, 2> S2DMatrix<targetType>::getSize() const {
    return matrixSize;
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::operator*(const S2DMatrix<targetType>& other) const {
    if (matrixSize[0] != other.getSize()[1]) {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
    }

    size_t resultWidth = other.getSize()[0];
    size_t resultHeight = matrixSize[1];

    S2DMatrix<targetType> result(resultWidth, resultHeight);

    for (size_t row = 0; row < resultHeight; row++) {
        for (size_t col = 0; col < resultWidth; col++) {
            targetType sum = static_cast<targetType>(0);

            for (size_t k = 0; k < matrixSize[0]; k++) {
                sum += (*this)(k, row) * other(col, k);
            }

            result(col, row) = sum;
        }
    }

    return result;
}

template<MatrixType targetType>
S2DVector2<targetType> S2DMatrix<targetType>::operator*(const S2DVector2<targetType>& other) const {
    if (matrixSize[0] != 3 || matrixSize[1] != 3) {
        throw std::invalid_argument("Matrix must be 3x3 for 2D transformation.");
    }

    targetType newX = (*this)(0, 0) * other.x +
                      (*this)(1, 0) * other.y +
                      (*this)(2, 0) * static_cast<targetType>(1);

    targetType newY = (*this)(0, 1) * other.x +
                      (*this)(1, 1) * other.y +
                      (*this)(2, 1) * static_cast<targetType>(1);

    return S2DVector2<targetType>(newX, newY);
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::Identity(size_t iSize) {
    S2DMatrix<targetType> resMatrix(iSize);
    for (size_t j = 0; j < iSize; j++) {
        resMatrix(j, j) = static_cast<targetType>(1);
    }
    return resMatrix;
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::Translation(targetType x, targetType y) {
    S2DMatrix<targetType> resMatrix = S2DMatrix<targetType>::Identity(3);

    resMatrix(2, 0) = x;
    resMatrix(2, 1) = y;

    return resMatrix;
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::Scaling(targetType xScale, targetType yScale) {
    S2DMatrix<targetType> resMatrix = S2DMatrix<targetType>::Identity(3);

    resMatrix(0, 0) = xScale;
    resMatrix(1, 1) = yScale;

    return resMatrix;
}

template<MatrixType targetType>
S2DMatrix<targetType> S2DMatrix<targetType>::Rotation(float angle) {
    S2DMatrix<targetType> resMatrix = S2DMatrix<targetType>::Identity(3);

    constexpr float PI = 3.14159265f;
    float radAngle = angle * (PI / 180.0f);

    auto cosA = static_cast<targetType>(std::cos(radAngle));
    auto sinA = static_cast<targetType>(std::sin(radAngle));

    resMatrix(0, 0) = cosA;
    resMatrix(1, 0) = -sinA;
    resMatrix(0, 1) = sinA;
    resMatrix(1, 1) = cosA;

    return resMatrix;
}

template<MatrixType targetType>
bool S2DMatrix<targetType>::isSafeMatrixSize(const size_t xy) {
    return isSafeMatrixSize(xy, xy);
}

template<MatrixType targetType>
bool S2DMatrix<targetType>::isSafeMatrixSize(const size_t x, const size_t y) {
    if (x == 0) return true;
    return (SIZE_MAX / x) >= y;
}

#endif // ENGINE_S2DMATRIX_IPP
