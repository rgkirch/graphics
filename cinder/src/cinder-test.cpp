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
        static long count = 0;
//        auto now = std::chrono::system_clock::now();
//        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
//        auto turn = ms / 10000.f;
        count++;
        auto turn = count * M_PI * 2 / 60.f;
        gl::clear();
        CameraPersp cam;
        cam.lookAt( vec3( sin(turn), cos(turn), 3 ), vec3( 0 ) );
        gl::setMatrices( cam );
        auto lambert = gl::ShaderDef().lambert();
        auto shader = gl::getStockShader( lambert );
        shader->bind();
        gl::drawSphere( vec3(), 1.0f );
        console() << "frame" << std::endl;
    }
};

CINDER_APP( BasicApp, RendererGl )

