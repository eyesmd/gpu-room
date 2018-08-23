cmake_minimum_required(VERSION 3.11.0)
project (graphics-computing)

# Target
add_executable(room room.cpp glad.c error.cpp error.h room.h stb_image.h stb_image.c Texture.cpp Texture.h Shader.h)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(room ${GLFW_LIBRARIES})

# Compilation Options
include_directories(include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

