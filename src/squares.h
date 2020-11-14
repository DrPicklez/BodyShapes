#ifndef SQUARES_H
#define SQUARES_H
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "maximaudio.h"
#define PORT 12345


class squares
{
public:
    void setup(int widIn, int higIn, int numSquaresIn);
    void update(ofxCvGrayscaleImage mask);
    void draw();


    vector <int> squareX, squareY, squareCover;
    ofColor squareColor;
//    ofxOscSender sender; //  OSC For Backup PD sketch
    maximAudio sounds;

    int wid, hig, numSquares, sqWid, sqHig;

};

#endif // SQUARES_H
