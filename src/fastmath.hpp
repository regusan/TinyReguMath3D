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

// x∈[0,1] で atan(x) をミニマックス多項式で近似する内部関数
// 係数はすべて x=1 で合計が π/4 になるよう設計
// Order=2:  5次
// Order=1:  3次
// Order=3:  9次
template <int Order, typename T> T fast_atan(T x) {
    static_assert(Order >= 1 && Order <= 3, "fast_atan: Order は 1, 2, 3 のみ有効");
    T x2 = x * x;
    if constexpr (Order == 1) {
        return x * (T(0.9998) + x2 * T(-0.2148));
    } else if constexpr (Order == 2) {
        // 末項を π/4 に一致させるよう調整: 0.9998660 - 0.3302995 + a2 = π/4 → a2 = 0.1158431
        return x * (T(0.9998660) + x2 * (T(-0.3302995) + x2 * T(0.1158431)));
    } else {
        // A&S 4.4.49 完全5項、合計 = 0.9998660-0.3302995+0.1801410-0.0851330+0.0208351 ≈ π/4
        return x * (T(0.9998660) +
                    x2 * (T(-0.3302995) +
                          x2 * (T(0.1801410) + x2 * (T(-0.0851330) + x2 * T(0.0208351)))));
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
// asin(x) = atan2(x, sqrt(1-x²)) として fast_atan2 を使用
// rsqrt_quake で sqrt を高速化。x=±1 は端点クランプで保護
// x の範囲: [-1, 1]、float 専用
template <int Order> float fast_asin(float x) {
    static_assert(Order >= 1 && Order <= 3, "fast_asin: Order は 1, 2, 3 のみ有効");
    constexpr float half_pi = 1.5707963267948966f;
    float s = 1.0f - x * x;
    if (s <= 0.0f)
        return x > 0.0f ? half_pi : -half_pi;
    // sqrt(s) = s * rsqrt(s) で除算を避ける
    float cos_val = s * rsqrt_quake(s);
    return fast_atan2<Order>(x, cos_val);
}

// rsqrt_quake による高速 normalize (精度 ~23bit)
// float 専用
inline vec2<float> fast_normalize(const vec2<float>& v) { return v * rsqrt_quake(dot(v, v)); }
inline vec3<float> fast_normalize(const vec3<float>& v) { return v * rsqrt_quake(dot(v, v)); }
inline vec4<float> fast_normalize(const vec4<float>& v) { return v * rsqrt_quake(dot(v, v)); }

} // namespace trm3d
