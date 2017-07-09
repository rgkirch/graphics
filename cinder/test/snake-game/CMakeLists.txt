cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/snake-game)
add_executable(snakeGameTest snake_game_test.cpp)
target_link_libraries(snakeGameTest cinder)
target_link_libraries(snakeGameTest gtest gtest_main gmock)

