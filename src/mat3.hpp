#pragma once
#include "vec3.hpp"
#include <cmath>
#include <stdexcept>

namespace trm3d {

// Column-major 3x3 matrix. cols[j][i] = row i, col j.
template <typename T> struct mat3 {
    vec3<T> cols[3];

    // Identity
    constexpr mat3()
        : cols{vec3<T>(T(1), T(0), T(0)), vec3<T>(T(0), T(1), T(0)), vec3<T>(T(0), T(0), T(1))} {}

    constexpr mat3(const vec3<T>& c0, const vec3<T>& c1, const vec3<T>& c2) : cols{c0, c1, c2} {}

    // Diagonal (scalar * identity)
    explicit constexpr mat3(T s)
        : cols{vec3<T>(s, T(0), T(0)), vec3<T>(T(0), s, T(0)), vec3<T>(T(0), T(0), s)} {}

    vec3<T>& operator[](int i) {
        switch (i) {
        case 0:
            return cols[0];
        case 1:
            return cols[1];
        case 2:
            return cols[2];
        default:
            throw std::out_of_range("mat3: index out of range");
        }
    }
    const vec3<T>& operator[](int i) const {
        switch (i) {
        case 0:
            return cols[0];
        case 1:
            return cols[1];
        case 2:
            return cols[2];
        default:
            throw std::out_of_range("mat3: index out of range");
        }
    }

    constexpr mat3 operator+(const mat3& o) const {
        return {cols[0] + o.cols[0], cols[1] + o.cols[1], cols[2] + o.cols[2]};
    }
    constexpr mat3 operator-(const mat3& o) const {
        return {cols[0] - o.cols[0], cols[1] - o.cols[1], cols[2] - o.cols[2]};
    }
    constexpr mat3 operator*(T s) const { return {cols[0] * s, cols[1] * s, cols[2] * s}; }
    constexpr mat3 operator/(T s) const { return {cols[0] / s, cols[1] / s, cols[2] / s}; }
    constexpr mat3 operator-() const { return {-cols[0], -cols[1], -cols[2]}; }

    mat3& operator+=(const mat3& o) {
        cols[0] += o.cols[0];
        cols[1] += o.cols[1];
        cols[2] += o.cols[2];
        return *this;
    }
    mat3& operator-=(const mat3& o) {
        cols[0] -= o.cols[0];
        cols[1] -= o.cols[1];
        cols[2] -= o.cols[2];
        return *this;
    }
    mat3& operator*=(T s) {
        cols[0] *= s;
        cols[1] *= s;
        cols[2] *= s;
        return *this;
    }

    constexpr bool operator==(const mat3& o) const {
        return cols[0] == o.cols[0] && cols[1] == o.cols[1] && cols[2] == o.cols[2];
    }
    constexpr bool operator!=(const mat3& o) const { return !(*this == o); }
};

template <typename T> constexpr mat3<T> operator*(T s, const mat3<T>& m) { return m * s; }

// mat3 * vec3
template <typename T> constexpr vec3<T> operator*(const mat3<T>& m, const vec3<T>& v) {
    return {m[0].x * v.x + m[1].x * v.y + m[2].x * v.z, m[0].y * v.x + m[1].y * v.y + m[2].y * v.z,
            m[0].z * v.x + m[1].z * v.y + m[2].z * v.z};
}

// vec3 * mat3 (row vector)
template <typename T> constexpr vec3<T> operator*(const vec3<T>& v, const mat3<T>& m) {
    return {m[0].x * v.x + m[0].y * v.y + m[0].z * v.z, m[1].x * v.x + m[1].y * v.y + m[1].z * v.z,
            m[2].x * v.x + m[2].y * v.y + m[2].z * v.z};
}

// mat3 * mat3
template <typename T> constexpr mat3<T> operator*(const mat3<T>& a, const mat3<T>& b) {
    return {a * b[0], a * b[1], a * b[2]};
}

template <typename T> constexpr mat3<T> transpose(const mat3<T>& m) {
    return {{m[0].x, m[1].x, m[2].x}, {m[0].y, m[1].y, m[2].y}, {m[0].z, m[1].z, m[2].z}};
}

template <typename T> constexpr T determinant(const mat3<T>& m) {
    return m[0].x * (m[1].y * m[2].z - m[2].y * m[1].z) -
           m[1].x * (m[0].y * m[2].z - m[2].y * m[0].z) +
           m[2].x * (m[0].y * m[1].z - m[1].y * m[0].z);
}

template <typename T> constexpr mat3<T> inverse(const mat3<T>& m) {
    T inv = T(1) / determinant(m);
    return {{(m[1].y * m[2].z - m[2].y * m[1].z) * inv, -(m[0].y * m[2].z - m[2].y * m[0].z) * inv,
             (m[0].y * m[1].z - m[1].y * m[0].z) * inv},
            {-(m[1].x * m[2].z - m[2].x * m[1].z) * inv, (m[0].x * m[2].z - m[2].x * m[0].z) * inv,
             -(m[0].x * m[1].z - m[1].x * m[0].z) * inv},
            {(m[1].x * m[2].y - m[2].x * m[1].y) * inv, -(m[0].x * m[2].y - m[2].x * m[0].y) * inv,
             (m[0].x * m[1].y - m[1].x * m[0].y) * inv}};
}

} // namespace trm3d
