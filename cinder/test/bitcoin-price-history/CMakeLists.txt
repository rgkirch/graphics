cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/src/bitcoin-price-history)
add_executable(bitcoinPriceHistoryTest file-open-test.cpp)
target_link_libraries(bitcoinPriceHistoryTest curl gtest gtest_main gmock nlohmann_json)

