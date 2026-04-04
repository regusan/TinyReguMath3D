# TinyReguMath3D

GLM 風の軽量 3D 数学ライブラリ。

- ヘッダーオンリー
- C++17
- 依存なし
- 左手系 / Y-up / +Z forward（DirectX スタイル）、NDC depth [0, 1]

## 型一覧

| 型 | 説明 |
|----|------|
| `vec2<T>` / `vec2f`, `vec2d`, `vec2i`, `vec2u` | 2次元ベクトル |
| `vec3<T>` / `vec3f`, `vec3d`, `vec3i`, `vec3u` | 3次元ベクトル |
| `vec4<T>` / `vec4f`, `vec4d`, `vec4i`, `vec4u` | 4次元ベクトル |
| `mat3<T>` / `mat3f`, `mat3d` | 3x3 行列（列優先） |
| `mat4<T>` / `mat4f`, `mat4d` | 4x4 行列（列優先） |

## 導入

### CMake

```cmake
add_subdirectory(TinyReguMath3D)
target_link_libraries(your_target PRIVATE TinyReguMath3D)
```

### ヘッダー直接インクルード

```cpp
#include <TinyReguMath3D.hpp>
```

## 使い方

### ベクトル

```cpp
using namespace trm3d;

vec3f v{1.0f, 2.0f, 3.0f};
v.x; v.r; v.u;   // 同じ成分（1成分目）
v.y; v.g; v.v;   // 同じ成分（2成分目）
v.z; v.b; v.w;   // 同じ成分（3成分目）
v[0];             // 添字アクセス

// 演算
vec3f a{1, 0, 0}, b{0, 1, 0};
cross(a, b);       // 外積 → (0, 0, 1)
dot(a, b);         // 内積 → 0
length(v);         // ノルム
normalize(v);      // 正規化
distance(a, b);    // 距離
```

### 行列（列優先）

```cpp
mat4f m;              // 単位行列
m[j];                 // j列目（vec4）
m[j][i];              // i行, j列
```

### トランスフォーム

```cpp
mat4f id;
mat4f T = translate(id, {3.0f, 0.0f, 0.0f});
mat4f S = scale(id, {2.0f, 2.0f, 2.0f});
mat4f R = rotate(id, pi / 2.0f, {0.0f, 0.0f, 1.0f});

// 合成（SRT: スケール→回転→平行移動）
mat4f SRT = T * R * S;
```

### プロジェクション

```cpp
// 透視投影（左手系、depth [0,1]）
mat4f proj = perspective(pi / 4.0f, 16.0f / 9.0f, 0.1f, 100.0f);

// 正射影
mat4f ortho_m = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

// ビュー行列
mat4f view = lookAt(vec3f{0, 0, 5}, vec3f{0, 0, 0}, vec3f{0, 1, 0});
```

### ストリーム入出力

```cpp
vec3f v{1, 2, 3};
std::cout << v;           // → (1, 2, 3)

std::istringstream ss("(1, 2, 3)");
ss >> v;
```

## ビルド（サンプル）

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./example
```
