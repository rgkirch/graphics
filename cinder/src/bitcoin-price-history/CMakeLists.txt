cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)
#add_definitions(-DCURL_STATICLIB)
add_executable(bitcoinPriceHistory graph.cpp)
target_link_libraries(bitcoinPriceHistory cinder curl nlohmann_json)

