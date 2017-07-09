#include "graph.hpp"

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0, 0, 0 ) );
}
void BitcoinPriceHistory::mouseDown(MouseEvent event) {
    points.push_back( vec2{event.getX(), event.getY()} );
}

void BitcoinPriceHistory::draw() {
    gl::clear();
    gl::setMatricesWindow( getWindowSize() );
    gl::color( Color::white() );

    if(not points.empty()) {
        ci::Path2d path;
        path.moveTo( points.front() );
        for (int i = 0; i < points.size(); i++) {
            path.lineTo( points[i] );
        }
        gl::draw( path );
    }
}
void BitcoinPriceHistory::resize() {
    mCam.setAspectRatio( getWindowAspectRatio() );
}
