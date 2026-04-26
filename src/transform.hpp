#pragma once
#include "mat4.hpp"
#include "vec3.hpp"
#include <cmath>

// Coordinate convention:
//   Right-handed, Y-up, -Z forward
//   NDC depth: [0, 1]

namespace trm3d {

template <typename T> constexpr mat4<T> translate(const mat4<T>& m, const vec3<T>& v) {
    mat4<T> result = m;
    result[3] = m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3];
    return result;
}

template <typename T> constexpr mat4<T> scale(const mat4<T>& m, const vec3<T>& v) {
    return {m[0] * v.x, m[1] * v.y, m[2] * v.z, m[3]};
}

// Rotate m by angle (radians) around axis RH
template <typename T> mat4<T> rotate(const mat4<T>& m, T angle, const vec3<T>& axis) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    vec3<T> a = normalize(axis);
    vec3<T> t = a * (T(1) - c);

    mat4<T> rot;
    rot[0] = {c + t.x * a.x, t.x * a.y + s * a.z, t.x * a.z - s * a.y, T(0)};
    rot[1] = {t.y * a.x - s * a.z, c + t.y * a.y, t.y * a.z + s * a.x, T(0)};
    rot[2] = {t.z * a.x + s * a.y, t.z * a.y - s * a.x, c + t.z * a.z, T(0)};
    rot[3] = {T(0), T(0), T(0), T(1)};

    return m * rot;
}

// Perspective projection  RH, depth [0, 1]
template <typename T> mat4<T> perspective(T fovy, T aspect, T near, T far) {
    T f = T(1) / std::tan(fovy / T(2));
    mat4<T> result(T(0));
    result[0][0] = f / aspect;
    result[1][1] = f;
    result[2][2] = far / (near - far); // [0, 1] depth
    result[2][3] = T(-1);              // -Z forward (RH)
    result[3][2] = (far * near) / (near - far);
    return result;
}

// Orthographic projection  RH, depth [0, 1]
template <typename T> constexpr mat4<T> ortho(T left, T right, T bottom, T top, T near, T far) {
    mat4<T> result(T(1));
    result[0][0] = T(2) / (right - left);
    result[1][1] = T(2) / (top - bottom);
    result[2][2] = -T(1) / (far - near); // [0, 1] depth, negated for RH
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -near / (far - near);
    return result;
}

// View matrix  RH, -Z forward
template <typename T> mat4<T> lookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up) {
    vec3<T> f = normalize(center - eye);
    vec3<T> s = normalize(cross(f, up)); // RH: forward × up
    vec3<T> u = cross(s, f);

    mat4<T> result(T(1));
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = -f.x; // negation: -Z forward
    result[1][2] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -dot(s, eye);
    result[3][1] = -dot(u, eye);
    result[3][2] = dot(f, eye);
    return result;
}

} // namespace trm3d
