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
    std::pair<int, int> getFood();
    void step();
private:
    int boxWidth, boxHeight;
    std::list<std::pair<int, int>> snake;
    std::pair<int, int> food;
    std::pair<int, int> direction;
    static std::pair<int, int> newFood(int width, int height, std::list<std::pair<int, int>> snake);
};

std::pair<int, int> SnakeInABox::newFood(int width, int height, std::list<std::pair<int, int>> snake) {
    assert(snake.size() < width * height);
    int x,y;
    std::vector<bool> available;
    available.resize(width * height, true);
    for(auto item : snake) {
        std::tie(x,y) = item;
        available[y * width + x] = false;
    }
    int numberAvailable = width * height - snake.size();
    int indexOfAvailable = rand() % numberAvailable;
    for(int i = 0; i < width * height; i++) {
        if(available[i] == true) {
            if(indexOfAvailable == 0) {
                x = i % width;
                y = i / width;
                return {x,y};
            }
            indexOfAvailable--;
        }
    }

}
void SnakeInABox::step() {
    static auto lastStep = std::chrono::system_clock::now();
    if(std::chrono::system_clock::now() - lastStep > std::chrono::milliseconds(200)) {
        lastStep = std::chrono::system_clock::now();
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
                food = newFood(boxWidth, boxHeight, snake);
            } else {
                snake.pop_back();
            }
        } else {
            snake.clear();
            snake.push_front( {0,0} );
            direction = {1, 0};
            food = newFood(boxWidth, boxHeight, snake);
        }
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
        food = newFood(boxWidth, boxHeight, snake);
    }
}
void SnakeInABox::callOnEach(std::function<void(int, int)> f) {
    for(auto p : snake) {
        f(p.first, p.second);
    }
}
