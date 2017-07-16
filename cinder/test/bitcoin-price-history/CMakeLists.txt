cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

add_executable(bitcoinPriceHistoryTest bitcoin-price-history-test.cpp)
add_executable(poloniex-data-test poloniex-data-test.cpp)
target_link_libraries(bitcoinPriceHistoryTest curl gtest gtest_main gmock nlohmann_json)
target_link_libraries(poloniex-data-test curl gtest gtest_main gmock nlohmann_json)

