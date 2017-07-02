#include <chrono>
#include "cinder/Easing.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
    void setup() override;
    void draw() override;

    static const int NUM_TILES = 2;

    std::vector<vec2> mTileLocations{
        {-1, 1},
        {1, -1}
    };
    CameraPersp     mCam;
    gl::GlslProgRef	mShader;
    gl::BatchRef    mTile;
};

void BasicApp::setup()
{
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 5 ), vec3( 0, 0, 0 ) );
    mTile = gl::Batch::create( geom::Cube() >> geom::Scale( .5f ), mShader);
}

void BasicApp::draw()
{
    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();

    gl::setMatrices( mCam );
    auto tilesWide = 4;
    auto tilesHigh = 4;

    gl::ScopedModelMatrix scpModelMtx;
    for(auto x = 1.f / (tilesWide + 1); x < 1; x++) {
        for(auto y = 1.f / (tilesHigh + 1); y < 1; y++) {
            gl::translate( getWindowCenter() - getWindowWidth() );
            gl::drawCube( vec3{x, y, 0}, vec3{0.1f});
        }
    }
}

CINDER_APP( BasicApp, RendererGl )

