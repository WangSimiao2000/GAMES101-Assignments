cmake_minimum_required(VERSION 3.10)
project(Rasterizer)

# 设置 OpenCV 的路径
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../opencv/build)

# 设置OpenCV的包含目录
find_package(OpenCV REQUIRED)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加包含目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 设置 Eigen 的包含目录
include_directories("${CMAKE_SOURCE_DIR}/../eigen-3.4.0")

# 添加可执行文件
add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)

# 链接 OpenCV 库
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})
