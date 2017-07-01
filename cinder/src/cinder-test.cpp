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
};

void BasicApp::setup()
{
    mCam.lookAt( vec3( 3, 2, 3 ), vec3( 0 ) );

    mGlsl = gl::GlslProg::create( gl::GlslProg::Format()
                                          .vertex(	CI_GLSL( 150,
                                                               uniform mat4	ciModelViewProjection;
                                                                       in vec4			ciPosition;

                                                                       void main( void ) {
                                                                           gl_Position	= ciModelViewProjection * ciPosition;
                                                                       }
                                                      ) )
                                          .fragment(	CI_GLSL( 150,
                                                                 uniform vec4	uColor;
                                                                         out vec4		oColor;

                                                                         void main( void ) {
                                                                             oColor = uColor;
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

    const int NUM_PLANES = 30;
    for( int p = 0; p < NUM_PLANES; ++p ) {
        float hue = p / (float)NUM_PLANES;
        ColorAf color( CM_HSV, hue, 1, 1, 1 );
        mGlsl->uniform( "uColor", color );

        gl::ScopedModelMatrix scpMtx;
        float angle = M_PI * p / (float)NUM_PLANES;
        gl::rotate( angleAxis( angle, vec3( 1, 0, 0 ) ) );
        mRect->draw();
    }
}


CINDER_APP( BasicApp, RendererGl )

