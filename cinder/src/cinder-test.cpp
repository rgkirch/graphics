#include <chrono>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
    void setup() override;
    void draw() override;

    CameraPersp		mCam;
    gl::BatchRef	mShapes[3][3];
};

void BasicApp::setup()
{
    auto lambert = gl::ShaderDef().lambert().color();
    gl::GlslProgRef	shader = gl::getStockShader( lambert );

    auto capsule = geom::Capsule().subdivisionsAxis( 10 ).subdivisionsHeight( 10 );
    mShapes[0][0] = gl::Batch::create( capsule, shader );
    auto sphere = geom::Sphere().subdivisions( 30 );
    mShapes[0][1] = gl::Batch::create( sphere, shader );
    auto cylinder = geom::Cylinder().subdivisionsAxis( 40 ).subdivisionsHeight( 2 );
    mShapes[0][2] = gl::Batch::create( cylinder, shader );
    auto cube = geom::Cube();
    mShapes[1][0] = gl::Batch::create( cube, shader );
    auto cone = geom::Cone();
    mShapes[1][1] = gl::Batch::create( cone, shader );
    auto torus = geom::Torus();
    mShapes[1][2] = gl::Batch::create( torus, shader );
    auto helix = geom::Helix().subdivisionsAxis( 20 ).subdivisionsHeight( 10 );
    mShapes[2][0] = gl::Batch::create( helix, shader );
    auto icosahedron = geom::Icosahedron();
    mShapes[2][1] = gl::Batch::create( icosahedron, shader );
    auto teapot = geom::Teapot() >> geom::Scale( 1.5f );
    mShapes[2][2] = gl::Batch::create( teapot, shader );

    mCam.lookAt( vec3( 5, 11, 5 ), vec3( 0 ) );
}

void BasicApp::draw()
{
    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();

    gl::setMatrices( mCam );

    float gridSize = 5;

    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j ) {
            float x = ( -0.5f + i / 2.0f ) * gridSize;
            float z = ( -0.5f + j / 2.0f ) * gridSize;

            gl::ScopedModelMatrix scpModelMatrix;
            gl::translate( x, 1, z );
            gl::color( i / 2.0f, 1 - i * j, j / 2.0f );
            mShapes[i][j]->draw();
        }
    }
}

CINDER_APP( BasicApp, RendererGl )

