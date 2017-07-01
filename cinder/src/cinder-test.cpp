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
        gl::pushModelMatrix();
        gl::translate( getWindowCenter() );
        auto numCircles = 16;
        auto radius = getWindowHeight() / 2.f - 30;
        for(auto c = 0; c < numCircles; c++) {
            auto rel = c / (float)numCircles;
            auto angle = rel * M_PI * 2;
            auto offset = vec2{ cos(angle), sin(angle) };
            gl::pushModelMatrix();
            gl::translate( offset * radius );
            gl::color( Color{CM_HSV, rel, 1, 1} );
            gl::drawStrokedCircle( vec2{}, 30 );
            gl::popModelMatrix();
        }
        gl::color( Color{1,1,1} );
        gl::drawSolidCircle( vec2{}, 15 );
        gl::popModelMatrix();
    }
};

CINDER_APP( BasicApp, RendererGl )

