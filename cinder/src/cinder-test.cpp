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

    CameraPersp         mCam;
    gl::BatchRef        mCube;
    gl::GlslProgRef		mGlsl;
};

void BasicApp::setup()
{
    mCam.lookAt( vec3( 3, 2, 4 ), vec3( 0 ) );

    mGlsl = gl::GlslProg::create(
        gl::GlslProg::Format()
        .vertex(
            CI_GLSL( 150,
                uniform mat4    ciModelViewProjection;
                in vec4         ciPosition;
                void main( void ) {
                    gl_Position = ciModelViewProjection * ciPosition;
                }
            )
        )
        .fragment(
            CI_GLSL( 150,
                out vec4 oColor;
                void main( void ) {
                    oColor = vec4( 1, 0.5, 0.25, 1 );
                }
            )
        )
    );

    mCube = gl::Batch::create( geom::Cube(), mGlsl );

    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void BasicApp::draw()
{
    gl::clear( Color( 0.2f, 0.2f, 0.2f ) );
    gl::setMatrices( mCam );
    mCube->draw();
}

CINDER_APP( BasicApp, RendererGl )

