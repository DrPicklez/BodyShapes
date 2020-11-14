#ifndef MAXIMAUDIO_H
#define MAXIMAUDIO_H
#include "ofMain.h"
#include "ofxMaxim.h"   //'micknoise' and colaborative contributions (https://github.com/micknoise/Maximilian)
#include "ofxOsc.h"

class maximAudio: public ofBaseApp{
public:
    void setup();
    void audioOut(float * ouptput, int bufferSize, int nChannels);
    void dataIn(int n, int coverage, int max);
    void dataSetup();

    int bufferSize, sampleRate;
    double outputs[2];
    double preMix[2];

    maxiSample sample[10];
    maxiMix mix[10];
    double currentSample;
    double mixSamples;


    int numSamplez;
    long maxLen;
    long samplePosition;
    long speed;

    vector <double> squareCoverage;



};

#endif // MAXIMAUDIO_H
