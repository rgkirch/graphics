#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using std::cout;
using std::endl;

auto red = Color(1,0,0);
auto green = Color(0,1,0);
auto blue = Color(0,0,1);

class BasicApp : public App {
public:
    void draw() override {
        gl::clear();
        CameraPersp cam;
        cam.lookAt( vec3( 3, 3, 3 ), vec3( 0 ) );
        gl::setMatrices( cam );
        gl::drawCube( vec3(), vec3( 2 ) );
    }
};

CINDER_APP( BasicApp, RendererGl )

