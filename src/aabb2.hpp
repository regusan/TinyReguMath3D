#pragma once
#include "vec2.hpp"

namespace trm3d {

template <typename T> struct aabb2 {
    vec2<T> pos;  // 最小角 (min corner)
    vec2<T> size; // 幅・高さ

    constexpr aabb2() : pos{}, size{} {}
    constexpr aabb2(const vec2<T>& pos, const vec2<T>& size) : pos(pos), size(size) {}

    constexpr vec2<T> min() const { return pos; }
    constexpr vec2<T> max() const { return pos + size; }
    constexpr vec2<T> center() const { return pos + size * T(0.5); }

    constexpr bool contains(const vec2<T>& p) const {
        vec2<T> mx = max();
        return p.x >= pos.x && p.x <= mx.x && p.y >= pos.y && p.y <= mx.y;
    }

    constexpr bool intersects(const aabb2& other) const {
        vec2<T> mx = max();
        vec2<T> omx = other.max();
        return pos.x <= omx.x && mx.x >= other.pos.x && pos.y <= omx.y && mx.y >= other.pos.y;
    }
};

} // namespace trm3d
