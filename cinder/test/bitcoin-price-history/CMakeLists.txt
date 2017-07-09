cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

add_executable(bitcoinPriceHistoryTest bitcoin-price-history-test.cpp)
target_link_libraries(bitcoinPriceHistoryTest cinder curl gtest gtest_main gmock)

