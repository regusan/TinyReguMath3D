#pragma once
#include "vec3.hpp"

namespace trm3d {

template <typename T> struct aabb3 {
    vec3<T> pos;  // 最小角 (min corner)
    vec3<T> size; // 幅・高さ・奥行き

    constexpr aabb3() : pos{}, size{} {}
    constexpr aabb3(const vec3<T>& pos, const vec3<T>& size) : pos(pos), size(size) {}

    constexpr vec3<T> min() const { return pos; }
    constexpr vec3<T> max() const { return pos + size; }
    constexpr vec3<T> center() const { return pos + size * T(0.5); }

    constexpr bool contains(const vec3<T>& p) const {
        vec3<T> mx = max();
        return p.x >= pos.x && p.x <= mx.x && p.y >= pos.y && p.y <= mx.y && p.z >= pos.z &&
               p.z <= mx.z;
    }

    constexpr bool intersects(const aabb3& other) const {
        vec3<T> mx = max();
        vec3<T> omx = other.max();
        return pos.x <= omx.x && mx.x >= other.pos.x && pos.y <= omx.y && mx.y >= other.pos.y &&
               pos.z <= omx.z && mx.z >= other.pos.z;
    }
};

} // namespace trm3d