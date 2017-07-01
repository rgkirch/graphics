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
        auto center = getWindowCenter();
        auto r = 70;
        gl::setMatricesWindow( getWindowSize() );
        gl::translate( getWindowCenter().x, 75 );
        gl::color( red );
        gl::drawSolidCircle( vec2{0}, r );
        gl::translate( 0, 150 );
        gl::color( green );
        gl::drawSolidCircle( vec2{0}, r );
        gl::translate( 0, 150 );
        gl::color( blue );
        gl::drawSolidCircle( vec2{0}, r );
    }
};

CINDER_APP( BasicApp, RendererGl )

