#pragma once
#include "aabb2.hpp"
#include "aabb3.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <ostream>

namespace trm3d {

template <typename T> std::ostream& operator<<(std::ostream& os, const vec2<T>& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const vec3<T>& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const vec4<T>& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const mat3<T>& m) {
    os << "mat3(\n";
    for (int r = 0; r < 3; ++r) {
        os << "  (" << m[0][r] << ", " << m[1][r] << ", " << m[2][r] << ')';
        if (r < 2)
            os << ',';
        os << '\n';
    }
    return os << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const mat4<T>& m) {
    os << "mat4(\n";
    for (int r = 0; r < 4; ++r) {
        os << "  (" << m[0][r] << ", " << m[1][r] << ", " << m[2][r] << ", " << m[3][r] << ')';
        if (r < 3)
            os << ',';
        os << '\n';
    }
    return os << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const aabb2<T>& b) {
    return os << "aabb2(pos=" << b.pos << ", size=" << b.size << ')';
}

template <typename T> std::ostream& operator<<(std::ostream& os, const aabb3<T>& b) {
    return os << "aabb3(pos=" << b.pos << ", size=" << b.size << ')';
}

} // namespace trm3d
