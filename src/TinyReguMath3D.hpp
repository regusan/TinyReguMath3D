#pragma once
#include "cg.hpp"
#include "fastmath.hpp"
#include "io.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "transform.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <cstdint>

namespace trm3d {

// 指定型のエイリアス生成
#define TRMD_VECMAT_ALIAS(suffix, T)                                                               \
    using vec2##suffix = vec2<T>;                                                                  \
    using vec3##suffix = vec3<T>;                                                                  \
    using vec4##suffix = vec4<T>;                                                                  \
    using mat3##suffix = mat3<T>;                                                                  \
    using mat4##suffix = mat4<T>;

TRMD_VECMAT_ALIAS(f, float)
TRMD_VECMAT_ALIAS(d, double)
// _Float16 は環境依存
#ifdef __FLT16_MAX__
TRMD_VECMAT_ALIAS(f16, _Float16)
#endif
TRMD_VECMAT_ALIAS(f32, float)
TRMD_VECMAT_ALIAS(f64, double)

TRMD_VECMAT_ALIAS(i, int)
TRMD_VECMAT_ALIAS(u, unsigned int)
TRMD_VECMAT_ALIAS(i8, int8_t)
TRMD_VECMAT_ALIAS(i16, int16_t)
TRMD_VECMAT_ALIAS(i32, int32_t)
TRMD_VECMAT_ALIAS(u8, uint8_t)
TRMD_VECMAT_ALIAS(u16, uint16_t)
TRMD_VECMAT_ALIAS(u32, uint32_t)

#undef TRMD_VECMAT_ALIAS

} // namespace trm3d
