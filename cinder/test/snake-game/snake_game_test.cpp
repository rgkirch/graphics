#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/snake-game/snakeInABox.hpp"
#include "cinder/Xml.h"


using std::string;
using namespace ci;


string raw = R"something(
<?xml version="1.0"?>
<data>
    <poloniexData>
        <file>small-poloniex-data.json</file>
        <file>two-years-poloniex-btc.json</file>
    </poloniexData>
</data>
)something";

TEST(directionTest, one) {
    SnakeInABox snake(4, 4);
    snake.up();
}

TEST(xml, xmlTest) {
    XmlTree *doc = new XmlTree(raw);
    auto files = doc->getChild("data/poloniexData");
    for (auto f : files) {
        std::cout << f.getValue<string>() << std::endl;
    }
    delete doc;
}
