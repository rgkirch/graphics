#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/snake-game/snake-game-helper.hpp"

TEST(directionTest, one) {
    SnakeInABox snake(4, 4);
    snake.up();
    ASSERT_FALSE( snake.isAlive() );
}
