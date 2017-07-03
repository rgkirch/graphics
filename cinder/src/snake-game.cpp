#include "snake-game.hpp"

void SnakeGame::keyDown(KeyEvent event )
{
    switch( event.getCode() ) {
        case KeyEvent::KEY_SPACE:
            setup();
            break;
        case KeyEvent::KEY_ESCAPE:
            quit();
            break;
        case KeyEvent::KEY_UP:
//            snake.up();
            break;
        case KeyEvent::KEY_DOWN:
//            snake.down();
            break;
        case KeyEvent::KEY_LEFT:
//            snake.left();
            break;
        case KeyEvent::KEY_RIGHT:
//            snake.right();
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
    for (int i = 0; i < mTile.size(); i++) {
        mTile[i]->draw();
    }
}
