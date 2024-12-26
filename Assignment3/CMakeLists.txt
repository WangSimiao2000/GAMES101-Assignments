cmake_minimum_required(VERSION 3.10)
project(Rasterizer)

set(CMAKE_CXX_STANDARD 17)

# 查找 OpenCV
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../opencv/build)
find_package(OpenCV REQUIRED)

# 添加 OpenCV 和 Eigen 的包含目录
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/../eigen3")

add_executable(Rasterizer 
	main.cpp 
	rasterizer.hpp 
	rasterizer.cpp 
	global.hpp 
	Triangle.hpp 
	Triangle.cpp 
	Texture.hpp 
	Texture.cpp 
	Shader.hpp 
	OBJ_Loader.h
)

# 链接 OpenCV 库
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})

#target_compile_options(Rasterizer PUBLIC -Wall -Wextra -pedantic)

# 设置 Rasterizer 为 Visual Studio 的启动项
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Rasterizer)