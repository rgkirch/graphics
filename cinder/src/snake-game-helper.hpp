#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <utility>
#include <vector>

class SnakeInABox {
public:
    SnakeInABox(int width, int height);
    void callOnEach(std::function<void(int, int)> f);
    void up();
    void right();
    void down();
    void left();
    bool isDead();
    bool isAlive();
    std::pair<int, int> getFood();
    void step();
private:
    int boxWidth, boxHeight;
    std::list<std::pair<int, int>> snake;
    std::pair<int, int> food;
    std::pair<int, int> direction;
    bool alive;
    void newFood();
    bool isSnakeHere(int x, int y);
    void die();
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
void SnakeInABox::die() {
    alive = false;
    snake.clear();
    direction = {1, 0};
}
void SnakeInABox::step() {
    if(!alive) return;
    int x, y;
    std::tie(x, y) = snake.front();
    x += direction.first;
    y += direction.second;
    if(x > boxWidth || x < 0) {
        die();
    }
    if(y > boxHeight || y < 0) {
        die();
    }
    for(auto t : snake) {
        int t1, t2;
        std::tie(t1, t2) = t;
        if(t1 == x && t2 == y) {
            die();
        }
    }
    if(x == food.first && y == food.second) {
        newFood();
    } else {
        snake.pop_back();
    }
    snake.push_back( {x, y} );
}
void SnakeInABox::up() {
    direction = std::make_pair( 0,-1 );
}
void SnakeInABox::right() {
    direction = std::make_pair( 1,0 );
}
void SnakeInABox::down() {
    direction = std::make_pair( 0,1 );
}
void SnakeInABox::left() {
    direction = std::make_pair( -1,0 );
}
bool SnakeInABox::isDead() {
    return !alive;
}
bool SnakeInABox::isAlive() {
    return alive;
}
std::pair<int, int> SnakeInABox::getFood() {
    return food;
}
SnakeInABox::SnakeInABox(int width, int height) : boxWidth(width), boxHeight(height) {
    if(width > 2 && height > 2) {
        alive = true;
        snake.push_back( {0,0} );
        direction = std::make_pair( 1, 0 );
    } else {
        alive = false;
    }
}
void SnakeInABox::callOnEach(std::function<void(int, int)> f) {
    if(!alive) return;
    int x,y;
    for(auto p : snake) {
        f(p.first, p.second);
    }
}
