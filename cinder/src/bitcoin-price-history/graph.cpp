#include "graph.hpp"
#include "bitcoin.hpp"

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0, 0, 0 ) );
    HTTPDownloader downloader;
    std::string content = downloader.download("https://poloniex.com/public?command=returnChartData&currencyPair=BTC_XMR&start=1496970103&end=9999999999&period=86400");
}
void BitcoinPriceHistory::mouseDown(MouseEvent event) {
    points.push_back( vec2{event.getX(), event.getY()} );
}

void BitcoinPriceHistory::draw() {
    gl::clear();
    gl::setMatricesWindow( getWindowSize() );
    gl::color( Color::white() );
    ci::Path2d path;

    if(points.size() > 1) {
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
