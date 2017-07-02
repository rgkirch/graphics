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
    void resize() override;

    CameraPersp     mCam;
    gl::GlslProgRef	mShader;
    std::vector<gl::BatchRef> mTile;
    int tilesWide = 4;
    int tilesHigh = 4;
};

void BasicApp::resize()
{
    mCam.setAspectRatio( getWindowAspectRatio() );
}

void BasicApp::setup()
{
    setWindowSize( vec2{400,400} );
    setFullScreen( false );
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0, 0, 0 ) );
    mTile.reserve(tilesWide * tilesHigh);
    int i = 0;
    for(auto x = 1.f / (tilesWide + 1); x < 1; x += 1.f / (tilesWide + 1)) {
        for(auto y = 1.f / (tilesHigh + 1); y < 1; y += 1.f / (tilesHigh + 1)) {
            auto c = Color(CM_HSV, i / (float)(tilesWide * tilesHigh), 1, 1 );
            auto color = geom::Constant(geom::COLOR, c);
            auto trans = geom::Translate( x, y, 0 );
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
auto settingsFn = [] ( App::Settings *settings )->void {
    settings->setFullScreen( false );
    settings->setWindowSize( 400,400 );
};
CINDER_APP(
    BasicApp,
    RendererGl,
    settingsFn
)

