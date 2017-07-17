#include "graph.hpp"
#include "bitcoin.hpp"
#include "json.hpp"
#include "poloniex-datum.hpp"

using json = nlohmann::json;

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader(gl::ShaderDef().lambert().color());
    mCam.lookAt(vec3(0, 0, 3), vec3(0, 0, 0));

    Poloniex::Request request;
    request.setCurrencyPair("USDT_BTC").setStart(1496970103L).setEnd(9999999999L).setPeriod(86400L);
//    auto history = downloadData(request);
    auto history = Poloniex::dataFromFile("/home/richie/Documents/rgkirch/glfw/cinder/assets/two-years-poloniex-btc.json");
#define ITERIFY(x) std::begin(x), std::end(x)
    double max = *std::max_element(ITERIFY(history.close));
    std::vector<float> pixelHeights;
    std::transform(ITERIFY(history.close),
                   std::back_inserter(pixelHeights),
                   std::bind(
                           [](double d, double max, int windowHeight) -> double {
                               return (1 - (d / max)) * (windowHeight - 1);
                           },
                           std::placeholders::_1, max, getWindowHeight()));
    path.moveTo(vec2{0, pixelHeights.front()});
    for (int i = 1; i < pixelHeights.size(); i++) {
        auto v = vec2{(float) i / pixelHeights.size() * getWindowWidth(),
                      pixelHeights[i]};
//        console() << v << std::endl;
        path.lineTo(v);
    }
}

void BitcoinPriceHistory::mouseDown(MouseEvent event) {
    console() << vec2{event.getX(), event.getY()} << std::endl;
}

void BitcoinPriceHistory::draw() {
    gl::clear();
    gl::setMatricesWindow(getWindowSize());
    gl::color(Color::white());
    gl::draw(path);
}

void BitcoinPriceHistory::resize() {
    mCam.setAspectRatio(getWindowAspectRatio());
}
