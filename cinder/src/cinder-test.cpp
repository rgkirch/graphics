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
    gl::BatchRef        mRect;
    gl::GlslProgRef		mGlsl;
};

void BasicApp::setup()
{
    mCam.lookAt( vec3( 2, 1, 3 ), vec3( 0 ) );

    mGlsl = gl::GlslProg::create( gl::GlslProg::Format()
                                          .vertex(	CI_GLSL( 150,
                                                               uniform mat4	ciModelViewProjection;
                                                                       in vec4			ciPosition;
                                                                       in vec4			ciColor;
                                                                       out vec4		Color;

                                                                       void main( void ) {
                                                                           gl_Position	= ciModelViewProjection * ciPosition;
                                                                           Color = ciColor;
                                                                       }
                                                      ) )
                                          .fragment(	CI_GLSL( 150,
                                                                 in vec4		Color;
                                                                         out vec4	oColor;

                                                                         void main( void ) {
                                                                             oColor = Color;
                                                                         }
                                                        ) ) );

    auto rect = geom::Rect().colors( Color( 1, 0, 0 ),
                                     Color( 0, 0, 1 ),
                                     Color( 0, 0, 1 ),
                                     Color( 1, 0, 0 ) );
    mRect = gl::Batch::create( rect, mGlsl );

    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void BasicApp::draw()
{
    gl::clear( Color( 0.2f, 0.2f, 0.2f ) );
    gl::setMatrices( mCam );
    mRect->draw();
}


CINDER_APP( BasicApp, RendererGl )

