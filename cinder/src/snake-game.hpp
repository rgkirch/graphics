#pragma once

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
#include "snake-game-helper.hpp"

using namespace ci;
using namespace ci::app;

class SnakeGame : public App {
public:
    void setup() override;
    void draw() override;
    void resize() override;
    void keyDown( KeyEvent event ) override;
    void drawSnakeCube(int x, int y);
    CameraPersp mCam;
    gl::GlslProgRef mShader;
    std::vector< gl::BatchRef > mTile;
    float tileScale;
    int tilesWide;
    int tilesHigh;
    SnakeInABox snake;
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
