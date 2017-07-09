#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/bitcoin-price-history/bitcoin.hpp"

TEST(download, data) {
    HTTPDownloader downloader;
    std::string content = downloader.download("https://poloniex.com/public?command=returnChartData&currencyPair=BTC_XMR&start=1496970103&end=9999999999&period=86400");
    std::cout << content << std::endl;
}

