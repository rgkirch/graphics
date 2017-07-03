#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/snake-game.hpp"

TEST(directionTest, one) {
    Direction dir;
    ASSERT_FALSE( dir.isUp() );
    ASSERT_FALSE( dir.isRight() );
    ASSERT_FALSE( dir.isLeft() );
    ASSERT_FALSE( dir.isDown() );
}
