#pragma once
#include <cassert>
#include <cmath>

namespace trm3d {

template <typename T> struct vec4 {
    union {
        T x, r, u;
    };
    union {
        T y, g, v;
    };
    union {
        T z, b;
    };
    union {
        T w, a;
    };

    constexpr vec4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
    constexpr vec4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
    explicit constexpr vec4(T s) : x(s), y(s), z(s), w(s) {}

    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            assert(false && "vec4: index out of range");
            return x;
        }
    }
    const T& operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            assert(false && "vec4: index out of range");
            return x;
        }
    }

    constexpr vec4 operator+(const vec4& o) const { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
    constexpr vec4 operator-(const vec4& o) const { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
    constexpr vec4 operator*(const vec4& o) const { return {x * o.x, y * o.y, z * o.z, w * o.w}; }
    constexpr vec4 operator/(const vec4& o) const { return {x / o.x, y / o.y, z / o.z, w / o.w}; }
    constexpr vec4 operator*(T s) const { return {x * s, y * s, z * s, w * s}; }
    constexpr vec4 operator/(T s) const { return {x / s, y / s, z / s, w / s}; }
    constexpr vec4 operator-() const { return {-x, -y, -z, -w}; }

    vec4& operator+=(const vec4& o) {
        x += o.x;
        y += o.y;
        z += o.z;
        w += o.w;
        return *this;
    }
    vec4& operator-=(const vec4& o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        w -= o.w;
        return *this;
    }
    vec4& operator*=(T s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }
    vec4& operator/=(T s) {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }

    constexpr bool operator==(const vec4& o) const {
        return x == o.x && y == o.y && z == o.z && w == o.w;
    }
    constexpr bool operator!=(const vec4& o) const { return !(*this == o); }
};

template <typename T> constexpr vec4<T> operator*(T s, const vec4<T>& v) { return v * s; }

template <typename T> constexpr T dot(const vec4<T>& a, const vec4<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T> constexpr T length2(const vec4<T>& v) { return dot(v, v); }

template <typename T> T length(const vec4<T>& v) { return std::sqrt(length2(v)); }

template <typename T> vec4<T> normalize(const vec4<T>& v) { return v / length(v); }

template <typename T> T distance(const vec4<T>& a, const vec4<T>& b) { return length(a - b); }

} // namespace trm3d
