#include "graph.hpp"

using json = nlohmann::json;
using std::string;

boost::optional<XmlTree> BitcoinPriceHistory::loadXmlTreeFromFile(std::string fileToLoadFrom) const {
    if (boost::filesystem::exists(fileToLoadFrom)) {
        return XmlTree(loadFile(fileToLoadFrom));
    } else {
        return {};
    }
}

boost::optional<Poloniex::History> BitcoinPriceHistory::getDataFromFileOrInternet() const {
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
            history = Poloniex::downloadData(request);
        }
    }
    return history;
}

vector<float> BitcoinPriceHistory::mapValuesToPixels(vector<double> history) const {
#define ITERIFY(x) std::begin(x), std::end(x)
    double max = *max_element(ITERIFY(history));
    vector<float> pixelHeights;
    transform(ITERIFY(history),
              back_inserter(pixelHeights),
              bind(
                      [](double d, double max, int windowHeight) -> double {
                          return (1 - (d / max)) * (windowHeight - 1);
                      },
                      placeholders::_1, max, getWindowHeight()));
#undef ITERIFY
    return pixelHeights;
}

ci::Path2d BitcoinPriceHistory::pointsToPath(std::vector<double> points) const {
    ci::Path2d path;
    auto pixelHeights = mapValuesToPixels(points);
    path.moveTo(vec2{0, pixelHeights.front()});
    for (int i = 1; i < pixelHeights.size(); i++) {
        auto v = vec2{(float) i / pixelHeights.size() * getWindowWidth(),
                      pixelHeights[i]};
        path.lineTo(v);
    }
    return path;
}

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader(gl::ShaderDef().lambert().color());
    mCam.lookAt(vec3(0, 0, 3), vec3(0, 0, 0));

    auto history = getDataFromFileOrInternet();
    if (history) {
        paths.push_back(pointsToPath(history->high));
        paths.push_back(pointsToPath(history->open));
        paths.push_back(pointsToPath(history->close));
        paths.push_back(pointsToPath(history->low));
    }
}

void BitcoinPriceHistory::mouseDown(MouseEvent event) {
    console() << vec2{event.getX(), event.getY()} << std::endl;
}

void BitcoinPriceHistory::draw() {
    gl::clear();
    gl::setMatricesWindow(getWindowSize());
//    gl::setMatrices(mCam);
//    gl::color(Color::white());
    float mouseX = (getMousePos().x / (float)getWindowWidth() - .5f) * getWindowWidth();
    float mouseY = (getMousePos().y / (float)getWindowHeight() - .5f) * getWindowHeight();
    float scale = 2.f;
    gl::translate(mouseX * scale, mouseY * scale);
    gl::scale(scale, scale);
//    auto scale = geom::Scale(tileScale);
//    foodBox = gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader);
    for (int i = 0; i < paths.size(); i++) {
        gl::color(Color(CM_HSV, i / (float) paths.size(), 1, 1));
        gl::draw(paths[i]);
    }
}

void BitcoinPriceHistory::resize() {
    mCam.setAspectRatio(getWindowAspectRatio());
}
