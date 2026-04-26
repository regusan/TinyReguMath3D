#pragma once
#include <cassert>
#include <cmath>

namespace trm3d {

template <typename T> struct vec2 {
    union {
        T x, r, u;
    };
    union {
        T y, g, v;
    };

    constexpr vec2() : x(T(0)), y(T(0)) {}
    constexpr vec2(T x_, T y_) : x(x_), y(y_) {}
    explicit constexpr vec2(T s) : x(s), y(s) {}

    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(false && "vec2: index out of range");
            return x;
        }
    }
    const T& operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(false && "vec2: index out of range");
            return x;
        }
    }

    constexpr vec2 operator+(const vec2& o) const { return {x + o.x, y + o.y}; }
    constexpr vec2 operator-(const vec2& o) const { return {x - o.x, y - o.y}; }
    constexpr vec2 operator*(const vec2& o) const { return {x * o.x, y * o.y}; }
    constexpr vec2 operator/(const vec2& o) const { return {x / o.x, y / o.y}; }
    constexpr vec2 operator*(T s) const { return {x * s, y * s}; }
    constexpr vec2 operator/(T s) const { return {x / s, y / s}; }
    constexpr vec2 operator-() const { return {-x, -y}; }

    vec2& operator+=(const vec2& o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    vec2& operator-=(const vec2& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    vec2& operator*=(T s) {
        x *= s;
        y *= s;
        return *this;
    }
    vec2& operator/=(T s) {
        x /= s;
        y /= s;
        return *this;
    }

    constexpr bool operator==(const vec2& o) const { return x == o.x && y == o.y; }
    constexpr bool operator!=(const vec2& o) const { return !(*this == o); }
};

template <typename T> constexpr vec2<T> operator*(T s, const vec2<T>& v) { return v * s; }

template <typename T> constexpr T dot(const vec2<T>& a, const vec2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T> constexpr T length2(const vec2<T>& v) { return dot(v, v); }

template <typename T> T length(const vec2<T>& v) { return std::sqrt(length2(v)); }

template <typename T> vec2<T> normalize(const vec2<T>& v) { return v / length(v); }

template <typename T> T distance(const vec2<T>& a, const vec2<T>& b) { return length(a - b); }

} // namespace trm3d
