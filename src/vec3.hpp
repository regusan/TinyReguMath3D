#pragma once
#include <cmath>
#include <stdexcept>

namespace trm3d {

template <typename T> struct vec3 {
    union {
        T x, r, u;
    };
    union {
        T y, g, v;
    };
    union {
        T z, b, w;
    };

    constexpr vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    constexpr vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    explicit constexpr vec3(T s) : x(s), y(s), z(s) {}

    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("vec3: index out of range");
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
        default:
            throw std::out_of_range("vec3: index out of range");
        }
    }

    constexpr vec3 operator+(const vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    constexpr vec3 operator-(const vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    constexpr vec3 operator*(const vec3& o) const { return {x * o.x, y * o.y, z * o.z}; }
    constexpr vec3 operator/(const vec3& o) const { return {x / o.x, y / o.y, z / o.z}; }
    constexpr vec3 operator*(T s) const { return {x * s, y * s, z * s}; }
    constexpr vec3 operator/(T s) const { return {x / s, y / s, z / s}; }
    constexpr vec3 operator-() const { return {-x, -y, -z}; }

    vec3& operator+=(const vec3& o) {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }
    vec3& operator-=(const vec3& o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }
    vec3& operator*=(T s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    vec3& operator/=(T s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    constexpr bool operator==(const vec3& o) const { return x == o.x && y == o.y && z == o.z; }
    constexpr bool operator!=(const vec3& o) const { return !(*this == o); }
};

template <typename T> constexpr vec3<T> operator*(T s, const vec3<T>& v) { return v * s; }

template <typename T> constexpr T dot(const vec3<T>& a, const vec3<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T> constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

template <typename T> constexpr T length2(const vec3<T>& v) { return dot(v, v); }

template <typename T> T length(const vec3<T>& v) { return std::sqrt(length2(v)); }

template <typename T> vec3<T> normalize(const vec3<T>& v) { return v / length(v); }

template <typename T> T distance(const vec3<T>& a, const vec3<T>& b) { return length(a - b); }

} // namespace trm3d
