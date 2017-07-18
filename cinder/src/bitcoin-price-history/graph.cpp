#include "graph.hpp"

using json = nlohmann::json;
using std::string;

boost::optional<XmlTree> loadXmlTreeFromFile(std::string fileToLoadFrom) {
    if (boost::filesystem::exists(fileToLoadFrom)) {
        return XmlTree(loadFile(fileToLoadFrom));
    } else {
        return {};
    }
}

boost::optional<Poloniex::History> getDataFromFileOrInternet() {
    boost::optional<Poloniex::History> history;
    auto doc = loadXmlTreeFromFile("/home/richie/Documents/rgkirch/graphics/cinder/assets/values.xml");
    if (doc) {
        auto file = doc.get().getChild("data/poloniexData/dataSource").getValue<string>();
        if (file == "file") {
            history = Poloniex::dataFromFile(
                    "/home/richie/Documents/rgkirch/graphics/cinder/assets/two-years-poloniex-btc.json");
        } else {
            Poloniex::Request request;
            request.setCurrencyPair("USDT_BTC").setStart(1496970103L).setEnd(9999999999L).setPeriod(86400L);
            history = downloadData(request);
        }
    }
    return history;
}

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader(gl::ShaderDef().lambert().color());
    mCam.lookAt(vec3(0, 0, 3), vec3(0, 0, 0));

    auto history = getDataFromFileOrInternet();
    if (history) {
#define ITERIFY(x) std::begin(x), std::end(x)
        double max = *std::max_element(ITERIFY(history.get().close));
        std::vector<float> pixelHeights;
        std::transform(ITERIFY(history.get().close),
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
//            console() << v << std::endl;
            path.lineTo(v);
        }
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
