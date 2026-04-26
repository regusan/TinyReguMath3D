#pragma once
#include "vec3.hpp"
#include "vec4.hpp"
#include <cassert>
#include <cmath>

namespace trm3d {

// Column-major 4x4 matrix. cols[j][i] = row i, col j.
template <typename T> struct mat4 {
    vec4<T> cols[4];

    // Identity
    constexpr mat4()
        : cols{vec4<T>(T(1), T(0), T(0), T(0)), vec4<T>(T(0), T(1), T(0), T(0)),
               vec4<T>(T(0), T(0), T(1), T(0)), vec4<T>(T(0), T(0), T(0), T(1))} {}

    constexpr mat4(const vec4<T>& c0, const vec4<T>& c1, const vec4<T>& c2, const vec4<T>& c3)
        : cols{c0, c1, c2, c3} {}

    // Diagonal (scalar * identity)
    explicit constexpr mat4(T s)
        : cols{vec4<T>(s, T(0), T(0), T(0)), vec4<T>(T(0), s, T(0), T(0)),
               vec4<T>(T(0), T(0), s, T(0)), vec4<T>(T(0), T(0), T(0), s)} {}

    vec4<T>& operator[](int i) {
        switch (i) {
        case 0:
            return cols[0];
        case 1:
            return cols[1];
        case 2:
            return cols[2];
        case 3:
            return cols[3];
        default:
            assert(false && "mat4: index out of range");
            return cols[0];
        }
    }
    const vec4<T>& operator[](int i) const {
        switch (i) {
        case 0:
            return cols[0];
        case 1:
            return cols[1];
        case 2:
            return cols[2];
        case 3:
            return cols[3];
        default:
            assert(false && "mat4: index out of range");
            return cols[0];
        }
    }

    constexpr mat4 operator+(const mat4& o) const {
        return {cols[0] + o.cols[0], cols[1] + o.cols[1], cols[2] + o.cols[2], cols[3] + o.cols[3]};
    }
    constexpr mat4 operator-(const mat4& o) const {
        return {cols[0] - o.cols[0], cols[1] - o.cols[1], cols[2] - o.cols[2], cols[3] - o.cols[3]};
    }
    constexpr mat4 operator*(T s) const {
        return {cols[0] * s, cols[1] * s, cols[2] * s, cols[3] * s};
    }
    constexpr mat4 operator/(T s) const {
        return {cols[0] / s, cols[1] / s, cols[2] / s, cols[3] / s};
    }
    constexpr mat4 operator-() const { return {-cols[0], -cols[1], -cols[2], -cols[3]}; }

    mat4& operator+=(const mat4& o) {
        cols[0] += o.cols[0];
        cols[1] += o.cols[1];
        cols[2] += o.cols[2];
        cols[3] += o.cols[3];
        return *this;
    }
    mat4& operator-=(const mat4& o) {
        cols[0] -= o.cols[0];
        cols[1] -= o.cols[1];
        cols[2] -= o.cols[2];
        cols[3] -= o.cols[3];
        return *this;
    }
    mat4& operator*=(T s) {
        cols[0] *= s;
        cols[1] *= s;
        cols[2] *= s;
        cols[3] *= s;
        return *this;
    }

    constexpr bool operator==(const mat4& o) const {
        return cols[0] == o.cols[0] && cols[1] == o.cols[1] && cols[2] == o.cols[2] &&
               cols[3] == o.cols[3];
    }
    constexpr bool operator!=(const mat4& o) const { return !(*this == o); }
};

template <typename T> constexpr mat4<T> operator*(T s, const mat4<T>& m) { return m * s; }

// mat4 * vec4
template <typename T> constexpr vec4<T> operator*(const mat4<T>& m, const vec4<T>& v) {
    return {m[0].x * v.x + m[1].x * v.y + m[2].x * v.z + m[3].x * v.w,
            m[0].y * v.x + m[1].y * v.y + m[2].y * v.z + m[3].y * v.w,
            m[0].z * v.x + m[1].z * v.y + m[2].z * v.z + m[3].z * v.w,
            m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w * v.w};
}

// vec4 * mat4 (row vector)
template <typename T> constexpr vec4<T> operator*(const vec4<T>& v, const mat4<T>& m) {
    return {m[0].x * v.x + m[0].y * v.y + m[0].z * v.z + m[0].w * v.w,
            m[1].x * v.x + m[1].y * v.y + m[1].z * v.z + m[1].w * v.w,
            m[2].x * v.x + m[2].y * v.y + m[2].z * v.z + m[2].w * v.w,
            m[3].x * v.x + m[3].y * v.y + m[3].z * v.z + m[3].w * v.w};
}

// mat4 * mat4
template <typename T> constexpr mat4<T> operator*(const mat4<T>& a, const mat4<T>& b) {
    return {a * b[0], a * b[1], a * b[2], a * b[3]};
}

template <typename T> constexpr mat4<T> transpose(const mat4<T>& m) {
    return {{m[0].x, m[1].x, m[2].x, m[3].x},
            {m[0].y, m[1].y, m[2].y, m[3].y},
            {m[0].z, m[1].z, m[2].z, m[3].z},
            {m[0].w, m[1].w, m[2].w, m[3].w}};
}

template <typename T> constexpr T determinant(const mat4<T>& m) {
    T c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    T c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    T c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    T c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    T c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    T c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    T c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    T c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    T c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    return m[0][0] * (m[1][1] * c00 - m[2][1] * c02 + m[3][1] * c03) -
           m[0][1] * (m[1][0] * c00 - m[2][0] * c02 + m[3][0] * c03) +
           m[0][2] * (m[1][0] * c04 - m[2][0] * c06 + m[3][0] * c07) -
           m[0][3] * (m[1][0] * c08 - m[2][0] * c10 + m[3][0] * c11);
}

template <typename T> mat4<T> inverse(const mat4<T>& m) {
    T c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    T c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    T c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    T c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    T c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    T c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    T c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    T c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    T c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    T c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    T c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    T c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
    T c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    T c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    T c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    T c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    T c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    T c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    vec4<T> fac0(c00, c00, c02, c03);
    vec4<T> fac1(c04, c04, c06, c07);
    vec4<T> fac2(c08, c08, c10, c11);
    vec4<T> fac3(c12, c12, c14, c15);
    vec4<T> fac4(c16, c16, c18, c19);
    vec4<T> fac5(c20, c20, c22, c23);

    vec4<T> v0(m[1][0], m[0][0], m[0][0], m[0][0]);
    vec4<T> v1(m[1][1], m[0][1], m[0][1], m[0][1]);
    vec4<T> v2(m[1][2], m[0][2], m[0][2], m[0][2]);
    vec4<T> v3(m[1][3], m[0][3], m[0][3], m[0][3]);

    vec4<T> inv0(v1 * fac0 - v2 * fac1 + v3 * fac2);
    vec4<T> inv1(v0 * fac0 - v2 * fac3 + v3 * fac4);
    vec4<T> inv2(v0 * fac1 - v1 * fac3 + v3 * fac5);
    vec4<T> inv3(v0 * fac2 - v1 * fac4 + v2 * fac5);

    vec4<T> signA(T(+1), T(-1), T(+1), T(-1));
    vec4<T> signB(T(-1), T(+1), T(-1), T(+1));

    mat4<T> result(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

    vec4<T> row0(result[0][0], result[1][0], result[2][0], result[3][0]);
    vec4<T> dot0(m[0] * row0);
    T det = (dot0.x + dot0.y) + (dot0.z + dot0.w);

    return result * (T(1) / det);
}

} // namespace trm3d
