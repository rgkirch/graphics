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

ci::Path2d BitcoinPriceHistory::pointsToPath(std::vector<double> points) const {
    ci::Path2d path;
    path.moveTo(vec2{0, points.front()});
    for (int i = 1; i < points.size(); i++) {
        path.lineTo(vec2{i, points[i]});
    }
    return path;
}

void BitcoinPriceHistory::setup() {
    mShader = gl::getStockShader(gl::ShaderDef().lambert().color());
    mCam.lookAt(vec3(0, 0, 3), vec3(0, 0, 0));

    auto history = getDataFromFileOrInternet();
    BitcoinPriceHistory::history = history;
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
//    float mouseX = (getMousePos().x / (float)getWindowWidth() - .5f) * getWindowWidth();
//    float mouseY = (getMousePos().y / (float)getWindowHeight() - .5f) * getWindowHeight();
//    gl::translate(mouseX * scale, mouseY * scale);
//    gl::scale(getMousePos().x / 3000.f, 1);
//    auto scale = geom::Scale(tileScale);
//    foodBox = gl::Batch::create( geom::Cube() >> scale >> trans >> color, mShader);
    for (int i = 0; i < paths.size(); i++) {
        gl::color(Color(CM_HSV, i / (float) paths.size(), 1, 1));
        gl::draw(paths[i]);
    }
//    if(history) {
//        assert(history.get().close.size() == history.get().open.size());
//        for(int i = 0; i < history.get().close.size(); i++) {
//            gl::drawSolidRect( Rectf(vec2(1, history->open), vec2(1, history->close)) );
//        }
//    }
}

void BitcoinPriceHistory::resize() {
    mCam.setAspectRatio(getWindowAspectRatio());
}
