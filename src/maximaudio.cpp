/*Class for audio management
 * Uses 10 different samples
    ** Uses ofxMaxim (https://github.com/micknoise/Maximilian)
    ** Requires jack to be running for RTaudio playback
    ** Takes info from target squares to control audio playback rate
*/
#include "maximaudio.h"
//--------------------------------------------------------------
void maximAudio::setup(){
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 24); // Buffers = files(10), outPuts(2), mixStrips(10) = 22
    int numSamples = 10;

    for(int i = 0; i < numSamples; i ++){
        sample[i].load(ofToDataPath("audio" + ofToString(i) + "-2.wav"));
    }

    numSamplez = numSamples;    //To avoid sample loading error on startup as used below on audioRate.
}
//--------------------------------------------------------------
void maximAudio::dataSetup(){
    squareCoverage.push_back(0);
}
//--------------------------------------------------------------
void maximAudio::dataIn(int n, int coverage, int max){
    squareCoverage[n] = ofMap(coverage, 0, max, 0.02, 2, true);
}
//--------------------------------------------------------------
void maximAudio::audioOut(float * output, int bufferSize, int nChannels){

    for(int i = 0; i < bufferSize; i++){
        mixSamples = 0;
        for(int samplesN = 0; samplesN < numSamplez ; samplesN ++){
            long sampleLength = sample[samplesN].length;

            mixSamples += (sample[samplesN].play(squareCoverage[samplesN]) / (numSamplez * bufferSize)) * 900;      //IterateThroughSample
            mix[samplesN].stereo(mixSamples,outputs,0.5);
        }

        output[i * nChannels] = outputs[0];
        output[i * nChannels + 1] = outputs[1];
    }
}
