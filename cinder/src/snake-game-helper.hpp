#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <utility>
#include <vector>

class SnakeInABox {
public:
    SnakeInABox();
    SnakeInABox(int width, int height);
    void callOnEach(std::function<void(int, int)> f);
    void up();
    void right();
    void down();
    void left();
    void reset();
    void reset(int width, int height);
    std::pair<int, int> getFood();
    void step();
private:
    int boxWidth, boxHeight;
    std::list<std::pair<int, int>> snake;
    std::pair<int, int> food;
    std::pair<int, int> direction;
    void newFood();
    bool isSnakeHere(int x, int y);
};

bool SnakeInABox::isSnakeHere(int x, int y) {
    for(auto t : snake) {
        if(t.first == x && t.second == y) {
            return true;
        }
    }
    return false;
}
void SnakeInABox::newFood() {
    int x, y;
    do {
        x = rand() % boxWidth;
        y = rand() % boxWidth;
    } while(isSnakeHere(x, y));
    food = {x,y};
}
void SnakeInABox::step() {
    int x, y;
    std::tie(x, y) = snake.front();
    x += direction.first;
    y += direction.second;
    auto end = --std::end(snake);
    auto begin = std::begin(snake);
    bool stop = std::find(begin, end, std::make_pair(x,y)) != end;
    snake.push_front( {x, y} );
    if(x < boxWidth && x >= 0 && y < boxHeight && y >= 0 && !stop) {
        if(x == food.first && y == food.second) {
            newFood();
        } else {
            snake.pop_back();
        }
    } else {
        reset();
    }
}
void SnakeInABox::up() {
    direction = std::make_pair( 0,1 );
}
void SnakeInABox::right() {
    direction = std::make_pair( 1,0 );
}
void SnakeInABox::down() {
    direction = std::make_pair( 0,-1 );
}
void SnakeInABox::left() {
    direction = std::make_pair( -1,0 );
}
std::pair<int, int> SnakeInABox::getFood() {
    return food;
}
SnakeInABox::SnakeInABox() : SnakeInABox(8, 8) {}
SnakeInABox::SnakeInABox(int width, int height) : boxWidth(width), boxHeight(height) {
    if(width > 2 && height > 2) {
        snake.push_front( {0,0} );
        direction = std::make_pair( 1, 0 );
        newFood();
    }
}
void SnakeInABox::callOnEach(std::function<void(int, int)> f) {
    for(auto p : snake) {
        f(p.first, p.second);
    }
}
void SnakeInABox::reset() {
    snake.clear();
    snake.push_front( {0,0} );
    direction = {1, 0};
    newFood();
}
void SnakeInABox::reset(int width, int height) {
    reset();
    boxWidth = width;
    boxHeight = height;
}
