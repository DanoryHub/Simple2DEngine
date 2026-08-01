//
// Created by IvanMiatselski on 01.08.2026.
//

#ifndef ARCANOID_S2DMATRIX_HPP
#define ARCANOID_S2DMATRIX_HPP

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

    targetType operator()(size_t x, size_t y);

    void populate(const std::vector<targetType>& otherData);
    S2DMatrix<targetType> copySelf();

protected:
    std::vector<targetType> data;
    std::array<size_t, 2> matrixSize;
    size_t rowLength = 0;
    size_t dataLengthThreshold = 0;

    static bool isSafeMatrixSize(const size_t xy);
    static bool isSafeMatrixSize(const size_t x, const size_t y);
};

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix() {
    matrixSize = {0, 0};
}

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix(const size_t xy) {
    if (!isSafeMatrixSize(xy)) {
        throw std::invalid_argument("XY matrix size is too big.");
    }

    rowLength = xy;
    dataLengthThreshold = xy * xy;
    matrixSize = {xy, xy};
}

template<MatrixType targetType>
S2DMatrix<targetType>::S2DMatrix(size_t x, size_t y) {
    if (!isSafeMatrixSize(x, y)) {
        throw std::invalid_argument("XY matrix size is too big.");
    }

    rowLength = x;
    dataLengthThreshold = x * y;
    matrixSize = {x, y};
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
targetType S2DMatrix<targetType>::operator()(size_t x, size_t y) {
    if (x >= matrixSize[0] || y >= matrixSize[1]) {
        throw std::out_of_range("Matrix index out of range.");
    }

    return data[x + y * rowLength];
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

#endif //ARCANOID_S2DMATRIX_HPP