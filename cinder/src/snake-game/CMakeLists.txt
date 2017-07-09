cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

add_executable(snakeGame snake-game.cpp)
target_link_libraries(snakeGame cinder)

