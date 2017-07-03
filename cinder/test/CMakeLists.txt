cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(myTestProgram snake_game_test.cpp)
target_link_libraries(myTestProgram cinder)
target_link_libraries(myTestProgram gtest gtest_main gmock)

