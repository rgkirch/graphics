#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
    void draw() override {
        gl::clear();
        gl::drawSolidCircle( getWindowCenter(), 200 );
    }
};

CINDER_APP( BasicApp, RendererGl )

