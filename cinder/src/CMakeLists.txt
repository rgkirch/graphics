cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

add_executable(myProgram cinder-test.cpp)
target_link_libraries(myProgram cinder)

