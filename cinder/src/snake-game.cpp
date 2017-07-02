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
    mCam.lookAt( vec3( 3, 3, 3 ), vec3( 0, 0, 0 ) );
    int i = 0;
    for(auto x = 1.f / (tilesWide + 1); x < 1; x += 1.f / (tilesWide + 1)) {
        for(auto y = 1.f / (tilesHigh + 1); y < 1; y += 1.f / (tilesHigh + 1)) {
            auto color = geom::Constant( geom::COLOR, Color( CM_HSV, i / (float)mTile.size(), 1, 1 ) );
            auto trans = geom::Translate( x*2, y*2, 0 );
            auto scale = geom::Scale(.1f);
            mTile.push_back(gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader));
            i++;
        }
    }
}

void BasicApp::draw() {
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

CINDER_APP( BasicApp, RendererGl )

