#include <chrono>
#include <vector>
#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class Direction {
public:
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
    int direction {5};
};

class SnakeGame : public App {
public:
    void setup() override;
    void draw() override;
    void resize() override;
    void keyDown( KeyEvent event ) override;

    CameraPersp mCam;
    gl::GlslProgRef mShader;
    std::vector<gl::BatchRef> mTile;
    std::list<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction headDir;
    float tileScale;
    int tilesWide;
    int tilesHigh;
};

void SnakeGame::keyDown( KeyEvent event )
{
    switch( event.getCode() ) {
        case KeyEvent::KEY_SPACE:
            setup();
            break;
        case KeyEvent::KEY_ESCAPE:
            quit();
            break;
        case KeyEvent::KEY_UP:
            headDir.isUp();
            break;
        case KeyEvent::KEY_DOWN:
            headDir.isDown();
            break;
        case KeyEvent::KEY_LEFT:
            headDir.isLeft();
            break;
        case KeyEvent::KEY_RIGHT:
            headDir.isRight();
            break;
    }
}

void SnakeGame::resize()
{
    mCam.setAspectRatio( getWindowAspectRatio() );
}

void SnakeGame::setup()
{
    XmlTree doc(loadFile( "/home/richie/Documents/rgkirch/glfw/cinder/assets/values.xml" ));
    tilesWide = atoi(doc.getChild("snakeGame/tilesWide").getValue().c_str());
    tilesHigh = atoi(doc.getChild("snakeGame/tilesHigh").getValue().c_str());
    tileScale = atof(doc.getChild("snakeGame/tilesScale").getValue().c_str());
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    snake.clear();
    mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0, 0, 0 ) );
    mTile.clear();
    mTile.reserve(tilesWide * tilesHigh);
    int i = 0;
    for(auto x = 1.f / (tilesWide + 1); x < 1; x += 1.f / (tilesWide + 1)) {
        for(auto y = 1.f / (tilesHigh + 1); y < 1; y += 1.f / (tilesHigh + 1)) {
//            auto c = Color(CM_HSV, i / (float)(tilesWide * tilesHigh), 1, 1 );
            auto c = Color( .3f, .3f, .3f );
            auto color = geom::Constant(geom::COLOR, c);
            auto trans = geom::Translate( x * 2 - 1, y * 2 - 1, 0 );
            auto scale = geom::Scale(tileScale);
            mTile.push_back(gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader));
            i++;
        }
    }

}

void SnakeGame::draw() {
    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();

    gl::setMatrices(mCam);

    gl::ScopedModelMatrix scpModelMtx;
//    gl::color(.3f,.3f,1);
    for (int i = 0; i < mTile.size(); i++) {
        mTile[i]->draw();
    }
//    gl::drawCube( vec3{}, vec3{} );
}
auto settingsFn = [] ( App::Settings *settings )->void {
    settings->setFullScreen( false );
    settings->setWindowSize( 400,400 );
};
CINDER_APP(
    SnakeGame,
    RendererGl,
    settingsFn
)

