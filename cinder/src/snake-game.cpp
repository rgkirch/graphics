#include <chrono>
#include <vector>
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

    CameraPersp     mCam;
    gl::GlslProgRef	mShader;
    std::vector<gl::BatchRef> mTile;
    int tilesWide = 4;
    int tilesHigh = 4;
};

void BasicApp::setup()
{
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 5 ), vec3( 0, 0, 0 ) );
    for(auto x = 1.f / (tilesWide + 1); x < 1; x++) {
        for(auto y = 1.f / (tilesHigh + 1); y < 1; y++) {
            mTile.push_back(gl::Batch::create( geom::Cube() >> geom::Scale(.2f) >> geom::Translate( vec3{x,y,0} ), mShader));
        }
    }
}

void BasicApp::draw()
{
    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();

    gl::setMatrices( mCam );

    gl::ScopedModelMatrix scpModelMtx;
    for(int i = 0; i < mTile.size(); i++) {
        gl::color( Color( CM_HSV, i / (float)mTile.size(), 1, 1 ) );
        mTile[i]->draw();
    }
}

CINDER_APP( BasicApp, RendererGl )

