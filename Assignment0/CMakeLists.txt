cmake_minimum_required(VERSION 3.5)  # 使用较新版本的 CMake
project(Transformation)

# 设置 Eigen 的包含目录
include_directories("${CMAKE_SOURCE_DIR}/../eigen3")

# 添加可执行文件
add_executable(Transformation main.cpp)
