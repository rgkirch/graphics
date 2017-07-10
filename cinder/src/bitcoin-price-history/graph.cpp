#include <algorithm>
#include "graph.hpp"
#include "bitcoin.hpp"
#include "json.hpp"

using json = nlohmann::json;

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader( gl::ShaderDef().lambert().color() );
    mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0, 0, 0 ) );


    HTTPDownloader downloader;
    auto content = downloader.download("https://poloniex.com/public?command=returnChartData&currencyPair=USDT_BTC&start=1496970103&end=9999999999&period=86400");
    auto j = json::parse(content);
    for(auto r : j) {
        for(auto k : dataKeys) {
            data[k].push_back(r[k]);
        }
    }
    double max = *std::max_element(std::begin(data["close"]), std::end(data["close"]));
    std::vector<float> pixelHeights;
    std::transform(
            std::begin(data["close"]),
            std::end(data["close"]),
            std::back_inserter(pixelHeights),
            std::bind(
                    [](double d, double max, int windowHeight)->double {
                        return (1 - (d / max)) * (windowHeight - 1);
                    }
                    ,std::placeholders::_1
                    ,max
                    ,getWindowHeight()
            )
    );
    path.moveTo( vec2{0, pixelHeights.front()} );
    for (int i = 1; i < pixelHeights.size(); i++) {
        auto v =  vec2{(float)i / pixelHeights.size() * getWindowWidth(), pixelHeights[i]};
        console() << v << std::endl;
        path.lineTo( v );
    }
}
void BitcoinPriceHistory::mouseDown(MouseEvent event) {
    console() << vec2{event.getX(), event.getY()} << std::endl;
}

void BitcoinPriceHistory::draw() {
    gl::clear();
    gl::setMatricesWindow( getWindowSize() );
    gl::color( Color::white() );
    gl::draw( path );
}
void BitcoinPriceHistory::resize() {
    mCam.setAspectRatio( getWindowAspectRatio() );
}
