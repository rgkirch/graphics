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
    ci::Path2d path;

//    Font mFont;
//    gl::TextureFontRef mTextureFont;

    vector<float> mapValuesToPixels(Poloniex::History history) const;

    boost::optional<Poloniex::History> getDataFromFileOrInternet() const;

    boost::optional<XmlTree> loadXmlTreeFromFile(string fileToLoadFrom) const;
};

auto settingsFn = [](App::Settings *settings) -> void {
    settings->setFullScreen(false);
    settings->setWindowSize(800, 800);
};

CINDER_APP(
        BitcoinPriceHistory,
        RendererGl,
        settingsFn
)
