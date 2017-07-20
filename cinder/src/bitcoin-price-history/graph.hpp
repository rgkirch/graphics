#pragma once

#include <unordered_map>
#include <boost/optional.hpp>
#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poloniex-datum.hpp"

using namespace ci;
using namespace ci::app;

class BitcoinPriceHistory : public App {
public:
    void setup() override;

    void draw() override;

    void resize() override;

    void mouseDown(MouseEvent event) override;

    CameraPersp mCam;
    gl::GlslProgRef mShader;
//    std::vector< gl::BatchRef > mTile;
    std::vector<vec2> points;
    vector<ci::Path2d> paths;

//    Font mFont;
//    gl::TextureFontRef mTextureFont;

    vector<float> mapValuesToPixels(vector<double> prices) const;

    boost::optional<Poloniex::History> getDataFromFileOrInternet() const;

    boost::optional<XmlTree> loadXmlTreeFromFile(string fileToLoadFrom) const;

    Path2d pointsToPath(vector<double> points) const;

    boost::optional<Poloniex::History> history;
};

auto settingsFn = [](App::Settings *settings) -> void {
    settings->setFullScreen(false);
    settings->setWindowSize(1920, 1080);
};

CINDER_APP(
        BitcoinPriceHistory,
        RendererGl,
        settingsFn
)
