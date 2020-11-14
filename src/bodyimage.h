#ifndef BODYIMAGE_H
#define BODYIMAGE_H
#include "ofMain.h"
#include "ofxOpenCv.h"

class bodyImage{
public:
    void setup(int imageNum);
    void update(ofxCvGrayscaleImage mask, int xIn, int yIn, int widIn, int higIn);
    void imageFlip();
    void draw();

    ofImage colorImage;
    vector <ofImage> loadedImage;
    int imageNumN, x, y, wid, hig, wIn, hIn, counter, imageTiming, closeRange, farRange, numImagesInFolder;



};

#endif // BODYIMAGE_H
