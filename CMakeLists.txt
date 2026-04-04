cmake_minimum_required(VERSION 3.16)
project(TinyReguMath3D CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ヘッダーオンリーライブラリ
add_library(TinyReguMath3D INTERFACE)
target_include_directories(TinyReguMath3D INTERFACE src/)

# 使用例
add_executable(example examples/main.cpp)
target_link_libraries(example PRIVATE TinyReguMath3D)
