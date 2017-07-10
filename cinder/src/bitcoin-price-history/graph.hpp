#pragma once

#include <unordered_map>
#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

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
    std::unordered_map<std::string, std::vector<float>> data { {"close", {}}, {"date", {}}, {"high", {}}, {"low", {}}, {"open", {}}, {"quoteVolume", {}}, {"volume", {}}, {"weightedAverage", {}} };
    std::vector<std::string> dataKeys {"close", "date", "high", "low", "open", "quoteVolume", "volume", "weightedAverage"};
    ci::Path2d path;
//    Font mFont;
//    gl::TextureFontRef mTextureFont;
};

auto settingsFn = [] ( App::Settings *settings )->void {
    settings->setFullScreen( false );
    settings->setWindowSize( 800,800 );
};
CINDER_APP(
        BitcoinPriceHistory,
        RendererGl,
        settingsFn
)
