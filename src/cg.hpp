#pragma once
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace trm3d {

// 反射ベクトルを返す
// I: 入射ベクトル (表面に向かう方向)
// N: 正規化済み法線ベクトル
// 戻り値: I - 2 * dot(N, I) * N
template <typename V> constexpr V reflect(const V& I, const V& N) {
    return I - N * (decltype(dot(N, I))(2) * dot(N, I));
}

} // namespace trm3d
