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
    vec2 mouseLastPressed;
    vec2 mousePosition;
    vec2 mouseDragged;
    vec2 scale{1};

//    Font mFont;
//    gl::TextureFontRef mTextureFont;

    boost::optional<Poloniex::History> getDataFromFileOrInternet() const;

    boost::optional<XmlTree> loadXmlTreeFromFile(string fileToLoadFrom) const;

    Path2d pointsToPath(vector<double> points) const;

    void mouseDrag(MouseEvent event) override;

    void mouseWheel(MouseEvent event) override;

    void mouseUp(MouseEvent event) override;

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
