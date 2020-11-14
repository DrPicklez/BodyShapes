#ifndef TUBEMAP_H
#define TUBEMAP_H
#include "ofMain.h"
#include "ofxOpenCv.h"

class tubeMap
{
public:
    void setup(int wid, int hig, int cvWid, int cvHig);
    void update(int xIn, int yIn, int wIn, int hIn);
    void draw(int wid, int hig);
    ofVec2f dataSmoother(ofVec2f input);

    ofPixels colorfull, mapPixAlpha, mapCropped, mapPix;
    ofImage map;

    int ofWidth, width, rectWid, cvWidth;
    int ofHeight, height, rectHig, cvHeight;

    deque <int> xDataSmoother;

    int buffCount = 0;
    int numPoints = 20;
    ofVec2f points[20];
};

#endif // TUBEMAP_H
