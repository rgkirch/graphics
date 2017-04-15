cmake_minimum_required(VERSION 3.6)
project(mygl)
find_package(glfw3 REQUIRED)
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lGLEW -lGLU -lGL")
set(CMAKE_VERBOSE_MAKEFILE on )
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /usr/include usr/local/include ./stb)

add_executable(mygl texture.cpp)
