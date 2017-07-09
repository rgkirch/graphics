cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

add_executable(bitcoinPriceHistory graph.cpp)
target_link_libraries(bitcoinPriceHistory cinder)

