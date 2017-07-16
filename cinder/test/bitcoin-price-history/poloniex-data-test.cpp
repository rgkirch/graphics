#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/bitcoin-price-history/poloniex-datum.hpp"
//#include "cinder/Xml.h"

using std::string;
//using namespace ci;

TEST(history, pushBackData) {
    Poloniex::History ph;
//    ph.data.push_back({.01, .02, .03, .04, .05, .06, .07, .08});
}

TEST(request, stringOperator) {
    Poloniex::Request request;
    request.setCurrencyPair("USDT_BTC");
    request.setStart(1496970103L);
    request.setEnd(9999999999L);
    request.setPeriod(86400L);
    string expected = "https://poloniex.com/public?command=returnChartData&currencyPair=USDT_BTC&start=1496970103&end=9999999999&period=86400";
    string actual = request;
    ASSERT_EQ(expected, actual);
}

TEST(download, downloadDataTest) {
    Poloniex::Request request;
    request.setCurrencyPair("USDT_BTC");
    request.setStart(1496970103L);
    request.setEnd(9999999999L);
    request.setPeriod(86400L);
//    auto history = downloadData(request);
//    string actual = request;
//    ASSERT_EQ(expected, actual);
}

TEST(poleniex, getAsFile) {
    Poloniex::Request request;
    request.setCurrencyPair("USDT_BTC");
    request.setStart(1388534400L);
    request.setEnd(1483228800L);
    request.setPeriod(14400L);
    std::cout << "wget \"" << (string)(request) << "\"" << std::endl;
}

TEST(xml, xmlTest) {
//    XmlTree doc(loadFile("/home/richie/Documents/rgkirch/graphics/cinder/assets/values.xml"));
//    auto files = doc.getChild("data/poloniexData/file");
//    for(auto f : files) {
//        std::cout << f.getValue<string>() << std::endl;
//    }
}
