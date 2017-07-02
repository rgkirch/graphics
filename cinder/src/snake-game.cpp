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
    gl::BatchRef    mTile;
};

void BasicApp::setup()
{
    auto lambert = gl::ShaderDef().lambert().color();
    gl::GlslProgRef	shader = gl::getStockShader( lambert );
    mCam.lookAt( vec3( 0, 0, 5 ), vec3( 0, 0, 0 ) );
}

void BasicApp::draw()
{
    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();

    gl::setMatrices( mCam );

    gl::ScopedModelMatrix scpModelMtx;
    gl::drawCube( vec3{}, vec3{0.1f});
}

CINDER_APP( BasicApp, RendererGl )

