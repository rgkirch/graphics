#include <chrono>
#include <functional>
#include <list>
#include <utility>
#include <vector>
#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class Direction {
public:
    Direction() : direction(5) {};
    bool isUp() { return direction == 1; }
    bool isRight() { return direction == 2; }
    bool isDown() { return direction == 3; }
    bool isLeft() { return direction == 4; }
    bool setUp() { direction = 1; }
    bool setRight() { direction = 2; }
    bool setDown() { direction = 3; }
    bool setLeft() { direction = 4; }
private:
    // 1 up, 2 right, 3 down, 4 left
    int direction;
};

class Snake {
public:
    Snake() : Snake(0, 0) {}
    Snake(int x, int y) {
        snake.push_back( std::make_pair(x, y) );
    }
    Snake(int x, int y, Direction dir) : Snake(x, y) {
        headDir = dir;
    }
    void setup() {
        snake.clear();
    }
    void callOnEach(std::function<void(int, int)> f) {
        int x,y;
        for(auto p : snake) {
            f(p.first, p.second);
        }
    }
    void keyDown(KeyEvent event) {
        switch(event.getCode()) {
            case KeyEvent::KEY_UP:
                //            headDir.isUp();
                break;
            case KeyEvent::KEY_DOWN:
                //            headDir.isDown();
                break;
            case KeyEvent::KEY_LEFT:
                //            headDir.isLeft();
                break;
            case KeyEvent::KEY_RIGHT:
                //            headDir.isRight();
                break;
        }
    }
    void goUp() { headDir.setUp(); }
    void goRight() { headDir.setRight(); }
    void goDown() { headDir.setDown(); }
    void goLeft() { headDir.setLeft(); }
private:
    std::list<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction headDir;
};

class SnakeGame : public App {
public:
    void setup() override;
    void draw() override;
    void resize() override;
    void keyDown( KeyEvent event ) override;

    CameraPersp mCam;
    gl::GlslProgRef mShader;
    std::vector< gl::BatchRef > mTile;
    float tileScale;
    int tilesWide;
    int tilesHigh;
    Snake snake;
    std::vector< std::function<void()> > pokeForSetup {std::bind(&Snake::setup, &snake)};
    std::vector< std::function<void(KeyEvent)> > pokeForKeyDown {std::bind(&Snake::keyDown, &snake, std::placeholders::_1)};
};

auto settingsFn = [] ( App::Settings *settings )->void {
    settings->setFullScreen( false );
    settings->setWindowSize( 400,400 );
};
CINDER_APP(
    SnakeGame,
    RendererGl,
    settingsFn
)
