#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/snake-game/snakeInABox.hpp"

TEST(directionTest, one) {
    SnakeInABox snake(4, 4);
    snake.up();
}
