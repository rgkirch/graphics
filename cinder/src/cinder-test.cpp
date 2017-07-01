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
        float r = 100;
        gl::color(red);
        gl::drawSolidCircle( center + vec2{-r, r}, r );
        gl::color(green);
        gl::drawSolidCircle( center + vec2{r, r}, r );
        gl::color(blue);
        gl::drawSolidCircle( center + vec2{0, -.73 * r}, r );
    }
};

CINDER_APP( BasicApp, RendererGl )

