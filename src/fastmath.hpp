#pragma once
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <cmath>
#include <cstdint>

namespace trm3d {

// Quake の高速逆数平方根
// 初期推定値 + Newton法1回
// float 専用
inline float rsqrt_quake(float x) {
    float x2 = x * 0.5f;
    std::uint32_t i;
    // float のビット列を uint32_t として読む
    __builtin_memcpy(&i, &x, sizeof(i));
    i = 0x5f3759df - (i >> 1);
    float y;
    __builtin_memcpy(&y, &i, sizeof(y));
    y = y * (1.5f - x2 * y * y);
    return y;
}

// |x| <= 1 の範囲で atan(x) をミニマックス多項式で近似する内部関数
template <int Order, typename T> T fast_atan(T x) {
    static_assert(Order >= 1 && Order <= 3, "fast_atan: Order は 1, 2, 3 のみ有効");
    T x2 = x * x;
    if constexpr (Order == 1) { // Order=1: 3次多項式
        return x * (T(0.9998) + x2 * T(-0.2148));
    } else if constexpr (Order == 2) { // Order=2: 5次多項式
        return x * (T(0.9997) + x2 * (T(-0.3301) + x2 * T(0.1801)));
    } else { // Order=3: 7次多項式
        return x * (T(0.9998676) + x2 * (T(-0.3302995) + x2 * (T(0.1801410) + x2 * T(-0.0851330))));
    }
}

// atan2(y, x) の高速近似 (全象限対応)
template <int Order, typename T> T fast_atan2(T y, T x) {
    static_assert(Order >= 1 && Order <= 3, "fast_atan2: Order は 1, 2, 3 のみ有効");
    constexpr T pi = T(3.14159265358979323846);
    constexpr T half_pi = pi / T(2);

    T ax = std::abs(x);
    T ay = std::abs(y);

    T denom = ax > ay ? ax : ay;
    if (denom == T(0))
        return T(0);

    // t = min(|x|,|y|) / max(|x|,|y|) で [0,1] に正規化
    T t = (ax < ay ? ax : ay) / denom;
    T a = fast_atan<Order>(t); // fast_atan(t) で近似

    // 象限・軸ごとに補正
    if (ay > ax)
        a = half_pi - a;
    if (x < T(0))
        a = pi - a;
    if (y < T(0))
        a = -a;

    return a;
}

// asin(x) の高速近似
// asin(x) = atan(x * rsqrt(1 - x²)) として rsqrt_quake を使用
// x の範囲: [-1, 1]、float 専用
template <int Order> float fast_asin(float x) {
    static_assert(Order >= 1 && Order <= 3, "fast_asin: Order は 1, 2, 3 のみ有効");
    return fast_atan<Order>(x * rsqrt_quake(1.0f - x * x));
}

// rsqrt_quake による高速 normalize (精度 ~23bit)
// float 専用
inline vec2<float> fast_normalize(const vec2<float>& v) { return v * rsqrt_quake(dot(v, v)); }
inline vec3<float> fast_normalize(const vec3<float>& v) { return v * rsqrt_quake(dot(v, v)); }
inline vec4<float> fast_normalize(const vec4<float>& v) { return v * rsqrt_quake(dot(v, v)); }

} // namespace trm3d
