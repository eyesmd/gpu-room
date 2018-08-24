cmake_minimum_required(VERSION 3.11.0)
project (graphics-computing)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Target
add_executable(room src/room.cpp include/glad/glad.c src/error.cpp src/error.h src/room.h include/stb/stb_image.h include/stb/stb_image.c src/entities/Texture.cpp src/entities/Texture.h src/entities/Shader.h src/entities/BasicCamera.cpp src/entities/BasicCamera.h)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(room ${GLFW_LIBRARIES})

# Compilation Options
include_directories(include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

