#include <chrono>
#include "cinder/Easing.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
    void    setup() override;
    void    draw() override;

    CameraPersp         mCam;
    gl::BatchRef        mSphere;
    gl::TextureRef      mTexture;
    gl::GlslProgRef     mGlsl;
};

void BasicApp::setup()
{
    auto img = loadImage( "/home/richie/Documents/rgkirch/glfw/cinder/lib/Cinder/samples/_opengl/MipMap/resources/checkerboard.png" );
    mTexture = gl::Texture::create( img );
    mTexture->bind();

    auto shader = gl::ShaderDef().texture().lambert();
    mGlsl = gl::getStockShader( shader );
    auto sphere = geom::Sphere().subdivisions( 50 );
    mSphere = gl::Batch::create( sphere, mGlsl );

    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void BasicApp::draw()
{
    auto x = getElapsedFrames() / (4 * 60.f) * M_PI * 2;
    mCam.lookAt( vec3( sin(x) * 4, 2, cos(x) * 4 ), vec3( 0 ) );

    gl::clear( Color( 0.2f, 0.2f, 0.2f ) );
    gl::setMatrices( mCam );

    mSphere->draw();

    // draw the texture itself in the upper right corner
    gl::setMatricesWindow( getWindowSize() );
    Rectf drawRect( 0, 0, mTexture->getWidth() / 3,
                    mTexture->getHeight() / 3 );
    gl::draw( mTexture, drawRect );
}

CINDER_APP( BasicApp, RendererGl )

