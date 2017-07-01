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

    gl::Texture2dRef    mTex;
};

void BasicApp::setup()
{
    auto img = loadImage( "/home/richie/Documents/rgkirch/glfw/cinder/lib/Cinder/docs/htmlsrc/guides/opengl/images/clouds.jpg" );
    mTex = gl::Texture2d::create( img );
}

void BasicApp::draw()
{
    gl::clear();

    gl::draw( mTex );
}


CINDER_APP( BasicApp, RendererGl )

