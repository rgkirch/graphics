#include <chrono>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

auto red = Color(1,0,0);
auto green = Color(0,1,0);
auto blue = Color(0,0,1);

class BasicApp : public App {
public:
    void draw() override {
        gl::clear();
        gl::enableDepthRead();
        gl::enableDepthWrite();

        static long count = 0;
        count++;
        auto turn = count * M_PI * 2 / (60.f * 4);

        CameraPersp cam;
        cam.lookAt( vec3( sin(turn) * 6, 2.5f, cos(turn) * 6 ), vec3( 0, 1.5f, 0 ) );
        gl::setMatrices( cam );

        auto lambert = gl::ShaderDef().lambert().color();
        auto shader = gl::getStockShader( lambert );
        shader->bind();

        auto numSpheres = 64;
        auto maxAngle = M_PI * 7.f;
        auto spiralRadius = 1.f;
        auto height = 3.f;

        for( auto s = 0; s < numSpheres; ++s ) {
            auto rel = s / (float)numSpheres;
            auto angle = rel * maxAngle;
            auto y = rel * height;
            auto r = rel * spiralRadius * spiralRadius;
            vec3 offset( r * cos( angle ), y, r * sin( angle ) );

            gl::pushModelMatrix();
            gl::translate( offset );
            gl::color( Color( CM_HSV, rel, 1, 1 ) );
            gl::drawSphere( vec3(), 0.1f, 30 );
            gl::popModelMatrix();
        }
    }
};

CINDER_APP( BasicApp, RendererGl )

