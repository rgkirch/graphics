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
            snake.up();
            snake.step();
            break;
        case KeyEvent::KEY_DOWN:
            snake.down();
            snake.step();
            break;
        case KeyEvent::KEY_LEFT:
            snake.left();
            snake.step();
            break;
        case KeyEvent::KEY_RIGHT:
            snake.right();
            snake.step();
            break;
    }
}

void SnakeGame::resize()
{
    mCam.setAspectRatio( getWindowAspectRatio() );
}

void SnakeGame::setup()
{
    mFont = Font( "Times New Roman", 24 );
    mTextureFont = gl::TextureFont::create( mFont );
    XmlTree doc(loadFile( "/home/richie/Documents/rgkirch/glfw/cinder/assets/values.xml" ));
    tilesWide = doc.getChild("snakeGame/tilesWide").getValue<int>();
    tilesHigh = doc.getChild("snakeGame/tilesHigh").getValue<int>();
    tileScale = doc.getChild("snakeGame/tilesScale").getValue<float>();
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

void SnakeGame::drawSnakeCube(int x, int y) {
    x+=1;
    y+=1;
    gl::BatchRef box;
    auto c = Color(.2f, .8f, .2f);
    auto color = geom::Constant(geom::COLOR, c);
    auto trans = geom::Translate( 1.f / (tilesWide + 1) * x * 2 - 1, 1.f / (tilesHigh + 1) * y * 2 - 1, .2f );
    auto scale = geom::Scale(tileScale);
    box = gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader);
    box->draw();
}

void SnakeGame::draw() {
//    gl::clear();
//    gl::enableDepthRead();
//    gl::enableDepthWrite();
//
//    gl::setMatrices(mCam);
//
//    gl::ScopedModelMatrix scpModelMtx;
//    for (int i = 0; i < mTile.size(); i++) {
//        mTile[i]->draw();
//    }
////    gl::color(.2f, .8f, .2f);
////    gl::drawCube( vec3{}, vec3{1} );
//    snake.callOnEach( std::bind(&SnakeGame::drawSnakeCube, &(*this), std::placeholders::_1, std::placeholders::_2) );
//
//    auto food = snake.getFood();
//    gl::BatchRef foodBox;
//    auto c = Color(.8f, .2f, .2f);
//    auto color = geom::Constant(geom::COLOR, c);
//    auto trans = geom::Translate( 1.f / (tilesWide + 1) * (food.first + 1) * 2 - 1, 1.f / (tilesHigh + 1) * (food.second + 1) * 2 - 1, .2f );
//    auto scale = geom::Scale(tileScale);
//    foodBox = gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader);
//    foodBox->draw();

    gl::setMatricesWindow( getWindowSize() );
    gl::enableAlphaBlending();
    gl::clear( Color( 0, 0, 0 ) );
    gl::color( Color::white() );
    mTextureFont->drawString( "hello" , vec2{0, 0} );
}
