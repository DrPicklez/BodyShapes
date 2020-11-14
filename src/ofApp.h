#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlur.h"    //Golan Levin and Kyle McDonald. https://github.com/kylemcdonald/ofxBlur
#include "ofxOsc.h"
#include "ofxKinect.h"      //https://openkinect.org/wiki/Main_Page
#include "bodyimage.h"
#include "squares.h"
#include "maximaudio.h"
#include "tubemap.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void depthFocus();
    void keyPressed(int button);

    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage blur;
    ofxCvGrayscaleImage mask;
    ofxCvContourFinder contourFinder;
    ofxCvBlob blobs;

    ofFbo bufferForStretch;

    ofxKinect video;
    ofxBlur blurz;

    vector <bodyImage> body;
    squares targets;
    tubeMap map;

    int nearThreshold, farThreshold, imageNum, maxPeople;

    int thresh = 50;
    int coverage = 0;
    float noiseInc;
};
