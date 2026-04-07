#include <TinyReguMath3D.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    using namespace trm3d;

    // =========================================================================
    // vec
    // =========================================================================

    std::cout << "=== vec3f ===" << std::endl;
    vec3f v{1.0f, 2.0f, 3.0f};
    std::cout << "v        = " << v << std::endl;     // (1, 2, 3)
    std::cout << "v.x/.r/.u = " << v.x << std::endl;  // 個別成分アクセス
    std::cout << "v[0]      = " << v[0] << std::endl; // 添字アクセス

    std::cout << "\n=== 算術演算 ===" << std::endl;
    vec3f a{1.0f, 0.0f, 0.0f};
    vec3f b{0.0f, 1.0f, 0.0f};
    std::cout << "cross({1,0,0}, {0,1,0}) = " << cross(a, b) << std::endl;            // (0,0,1)
    std::cout << "dot({1,0,0}, {0,1,0})   = " << dot(a, b) << std::endl;              // 0
    std::cout << "length({3,4,0})         = " << length(vec3f{3, 4, 0}) << std::endl; // 5
    std::cout << "normalize({3,4,0})      = " << normalize(vec3f{3, 4, 0}) << std::endl;

    // =========================================================================
    // mat3
    // =========================================================================

    std::cout << "\n=== mat3f ===" << std::endl;

    // --- column-major の仕組み ---
    // m[col][row] でアクセス。m[0] は第0列。
    //
    // mat3f m は次の行列を表す:
    //   col0    col1    col2
    //   (1,0,0) (0,2,0) (0,0,3)  ← 各列がメモリ上で連続
    //
    //   可視化:
    //   | 1  0  0 |
    //   | 0  2  0 |
    //   | 0  0  3 |
    mat3f diag({1, 0, 0}, {0, 2, 0}, {0, 0, 3}); // 対角行列
    std::cout << "対角行列:\n" << diag << std::endl;
    std::cout << "diag[0]    (第0列) = " << diag[0] << std::endl;      // (1,0,0)
    std::cout << "diag[1]    (第1列) = " << diag[1] << std::endl;      // (0,2,0)
    std::cout << "diag[0][0] (行0,列0) = " << diag[0][0] << std::endl; // 1
    std::cout << "diag[1][1] (行1,列1) = " << diag[1][1] << std::endl; // 2

    // mat3 * vec3 : 列ベクトルを右から掛ける
    vec3f scaled = diag * vec3f{1, 1, 1};
    std::cout << "diag * (1,1,1) = " << scaled << std::endl; // (1,2,3)

    // identity
    mat3f id3;
    std::cout << "\nidentity:\n" << id3 << std::endl;

    // transpose
    mat3f t = transpose(diag);
    std::cout << "transpose(diag):\n" << t << std::endl;

    // determinant / inverse
    std::cout << "det(diag) = " << determinant(diag) << std::endl; // 6
    mat3f inv = inverse(diag);
    std::cout << "inverse(diag):\n" << inv << std::endl;
    std::cout << "diag * inverse(diag) (≒identity):\n" << diag * inv << std::endl;

    // =========================================================================
    // mat4
    // =========================================================================

    std::cout << "\n=== mat4f ===" << std::endl;

    mat4f id4;
    std::cout << "identity:\n" << id4 << std::endl;

    // --- column-major の実例 ---
    // mat4f の第3列 (index=3) が平行移動成分
    //
    //   | 1  0  0  tx |
    //   | 0  1  0  ty |   ← cols[3] = (tx, ty, tz, 1)
    //   | 0  0  1  tz |
    //   | 0  0  0  1  |
    mat4f T = translate(id4, {3.0f, 0.0f, 0.0f});
    std::cout << "translate(id, {3,0,0}):\n" << T << std::endl;
    std::cout << "平行移動列 T[3] = " << T[3] << std::endl; // (3,0,0,1)

    vec4f p{1, 0, 0, 1};                                   // 同次座標
    std::cout << "T * (1,0,0,1) = " << T * p << std::endl; // (4,0,0,1)

    // scale
    mat4f S = scale(id4, {2.0f, 2.0f, 2.0f});
    std::cout << "\nscale(id, {2,2,2}):\n" << S << std::endl;

    // rotate (Z軸 90度)
    const float pi = std::acos(-1.0f);
    mat4f R = rotate(id4, pi / 2.0f, {0.0f, 0.0f, 1.0f});
    std::cout << "\nrotate(id, 90deg, Z):\n" << R << std::endl;
    std::cout << "R * (1,0,0,1) ≒ " << R * vec4f{1, 0, 0, 1} << std::endl; // (0,1,0,1)

    // 変換合成: SRT (スケール→回転→平行移動 の順に適用)
    // column-majorでは 左から掛けた行列が後から適用される
    mat4f SRT = T * R * S;
    std::cout << "\nSRT = T*R*S:\n" << SRT << std::endl;
    std::cout << "SRT * (1,0,0,1) = " << SRT * vec4f{1, 0, 0, 1} << std::endl;
    // scale(1,0,0)→(2,0,0), rotate→(0,2,0), translate→(3,2,0)

    // perspective
    mat4f proj = perspective(pi / 4.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    std::cout << "\nperspective(fovy=45deg, aspect=16/9, near=0.1, far=100):\n"
              << proj << std::endl;

    // lookAt
    mat4f view = lookAt(vec3f{0, 0, 5}, vec3f{0, 0, 0}, vec3f{0, 1, 0});
    std::cout << "lookAt(eye={0,0,5}, center={0,0,0}, up={0,1,0}):\n" << view << std::endl;

    // inverse
    mat4f invT = inverse(T);
    std::cout << "inverse(T):\n" << invT << std::endl;
    std::cout << "T * inverse(T) (≒identity):\n" << T * invT << std::endl;

    // =========================================================================
    // fastmath
    // =========================================================================

    std::cout << "\n=== fastmath ===" << std::endl;

    const float deg2rad = pi / 180.0f;

    // 誤差統計を計算するラムダ (絶対値平均・分散)
    auto stats = [](const std::vector<float>& errs) -> std::pair<float, float> {
        float mean = 0.0f;
        for (float e : errs)
            mean += std::abs(e);
        mean /= static_cast<float>(errs.size());
        float var = 0.0f;
        for (float e : errs)
            var += (std::abs(e) - mean) * (std::abs(e) - mean);
        var /= static_cast<float>(errs.size());
        return {mean, var};
    };

    // fast_atan2: -180°〜179° を 1° 刻みで (y=sin θ, x=cos θ)
    {
        std::cout << "\n[fast_atan2] -180〜179deg, 1deg刻み (360サンプル)" << std::endl;

        std::vector<float> e1, e2, e3;
        for (int deg = -180; deg < 180; ++deg) {
            float th = deg * deg2rad;
            float y = std::sin(th);
            float x = std::cos(th);
            float ref = std::atan2(y, x);
            e1.push_back(fast_atan2<1>(y, x) - ref);
            e2.push_back(fast_atan2<2>(y, x) - ref);
            e3.push_back(fast_atan2<3>(y, x) - ref);
        }

        auto [m1, v1] = stats(e1);
        auto [m2, v2] = stats(e2);
        auto [m3, v3] = stats(e3);
        std::cout << "  Order=1  mean=" << m1 << "  var=" << v1 << std::endl;
        std::cout << "  Order=2  mean=" << m2 << "  var=" << v2 << std::endl;
        std::cout << "  Order=3  mean=" << m3 << "  var=" << v3 << std::endl;
    }

    // fast_asin: -90°〜90° を 1° 刻みで (x=sin θ)
    {
        std::cout << "\n[fast_asin] -90〜90deg, 1deg刻み (181サンプル)" << std::endl;

        std::vector<float> e1, e2, e3;
        for (int deg = -90; deg <= 90; ++deg) {
            float x = std::sin(deg * deg2rad);
            float ref = std::asin(x);
            e1.push_back(fast_asin<1>(x) - ref);
            e2.push_back(fast_asin<2>(x) - ref);
            e3.push_back(fast_asin<3>(x) - ref);
        }

        auto [m1, v1] = stats(e1);
        auto [m2, v2] = stats(e2);
        auto [m3, v3] = stats(e3);
        std::cout << "  Order=1  mean=" << m1 << "  var=" << v1 << std::endl;
        std::cout << "  Order=2  mean=" << m2 << "  var=" << v2 << std::endl;
        std::cout << "  Order=3  mean=" << m3 << "  var=" << v3 << std::endl;
    }

    // fast_normalize: 1°刻みで方向ベクトルを正規化し length の誤差を測定
    {
        std::cout << "\n[fast_normalize] 0〜359deg, 1deg刻み (360サンプル)" << std::endl;

        std::vector<float> errs;
        for (int deg = 0; deg < 360; ++deg) {
            float th = deg * deg2rad;
            vec3f v{std::cos(th), std::sin(th), 0.0f};
            float len = length(fast_normalize(v));
            errs.push_back(len - 1.0f);
        }

        auto [m, var] = stats(errs);
        std::cout << "  length誤差  mean=" << m << "  var=" << var << std::endl;
    }

    return 0;
}
