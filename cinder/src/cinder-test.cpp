#include <chrono>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;


class BasicApp : public App {
public:
    void	setup() override;
    void	draw() override;

    CameraPersp			mCam;
    gl::BatchRef		mRect;
    gl::GlslProgRef		mGlsl;
    gl::Texture2dRef        mTex;
};



void BasicApp::setup()
{
    mCam.lookAt( vec3( 3, 2, 3 ), vec3( 0 ) );

    auto img = loadImage( "/home/richie/Documents/rgkirch/glfw/cinder/lib/Cinder/samples/_opengl/Cube/assets/texture.jpg" );
    mTex = gl::Texture2d::create( img );
    mTex->bind( 0 );

    mGlsl = gl::GlslProg::create( gl::GlslProg::Format()
                                          .vertex(	CI_GLSL( 150,
                                                               uniform mat4	ciModelViewProjection;
                                                                       in vec4			ciPosition;
                                                                       in vec2			ciTexCoord0;
                                                                       out vec2		TexCoord0;

                                                                       void main( void ) {
                                                                           gl_Position	= ciModelViewProjection * ciPosition;
                                                                           TexCoord0 = ciTexCoord0;
                                                                       }
                                                      ) )
                                          .fragment(	CI_GLSL( 150,
                                                                 uniform vec4		uColor;
                                                                         uniform sampler2D	uTex0;

                                                                         in vec2				TexCoord0;
                                                                         out vec4			oColor;

                                                                         void main( void ) {
                                                                             oColor = texture( uTex0, TexCoord0 ) * uColor;
                                                                         }
                                                        ) ) );

    mRect = gl::Batch::create( geom::Plane(), mGlsl );

    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void BasicApp::draw()
{
    gl::clear( Color( 0.2f, 0.2f, 0.2f ) );
    gl::setMatrices( mCam );

    const int NUM_PLANES = 7;
    for( int p = 0; p < NUM_PLANES; ++p ) {
        float hue = p / (float)NUM_PLANES;
        ColorAf color( CM_HSV, hue, 1, 1, 1 );
        mGlsl->uniform( "uTex0", 0 );
        mGlsl->uniform( "uColor", color );

        gl::ScopedModelMatrix scpMtx;
        float angle = M_PI * p / (float)NUM_PLANES;
        gl::rotate( angleAxis( angle, vec3( 1, 0, 0 ) ) );
        mRect->draw();
    }

    gl::setMatricesWindow( getWindowSize() );
    gl::draw( mTex, Rectf( 0, getWindowHeight() - 100,
                           150, getWindowHeight() ) );
}


CINDER_APP( BasicApp, RendererGl )

