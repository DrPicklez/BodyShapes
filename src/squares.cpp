#include "squares.h"
/* Class for interaction with audio:
    ** Creates 10 squares in random positions on startup
    ** Uses square positions to compare aginst an ofxGrayScaleImage
    ** Creates 10 values in accordance to seperate square area coverage
    ** Sends this to control audio in maximaudio class
    ** Can also send OSC messages as a backup (this was first plan)
*/
//--------------------------------------------------------------
void squares::setup(int widIn, int higIn, int numSquaresIn){

    wid = widIn;
    hig = higIn;
    numSquares = numSquaresIn;

    sqWid = wid/numSquares;
    sqHig = hig/numSquares;

//    sender.setup("localhost", PORT);    //OSC sender init

    int widthMSquare = wid - sqWid;    //for OSC scaling
    int heightMSquare = hig - sqHig;


    for(int i = 0; i < numSquares; i ++){

        int randomX = (ofRandom(0, wid));      //Random Position
        int randomY = (ofRandom(0, hig));

        int locX = randomX - (randomX % int(sqWid));        // % to prevent overlapping of sqaures
        int locY = randomY - (randomY % int(sqHig));

        squareX.push_back(locX);            //Set Square Positions & init squareCover
        squareY.push_back(locY);
        squareCover.push_back(0);
        sounds.dataSetup();         //bizzare vector setup, between classes

/* OSC For back-up PD sketch
        //OSC MESSAGING FOR BACKUP PD SKETCH
        int boxX = ofMap(locX, 0, widthMSquare, 0, 10u);
        ofxOscMessage oscMessagePositionX;
        oscMessagePositionX.setAddress("/boxX"+ofToString(i)); // Send OSC messages
        oscMessagePositionX.addIntArg(boxX);
        sender.sendMessage(oscMessagePositionX);

        int boxY = ofMap(locY, 0, heightMSquare, 0, 10);
        ofxOscMessage oscMessagePositionY;
        oscMessagePositionY.setAddress("/boxY"+ofToString(i)); // Send OSC messages
        oscMessagePositionY.addIntArg(boxY);
        sender.sendMessage(oscMessagePositionY);
*/
    }

    sounds.setup();

}
//--------------------------------------------------------------
void squares::update(ofxCvGrayscaleImage mask){

    ofPixels maskPix = mask.getPixels();

    int squareSize = sqWid * sqHig;

    for(int i = 0; i < numSquares; i ++){       //Iterate Though Squares

        int coverage = 0;       // initCoverCount

        for(int x = 0; x < sqWid; x ++){
            for(int y = 0; y < sqHig; y ++){

                int offSetX = (x + squareX[i]);
                int offSetY = (y + squareY[i]);
                int index = (wid * offSetY + offSetX);

                if(maskPix[index] > 0){ // Scrub Pixels for White. Do not directly reference other image pixels as image might hold 0 values.
                  coverage ++;
                }
            }
        }
        sounds.dataIn(i, coverage, squareSize);
        squareCover[i] = int(ofMap(coverage, 0, squareSize, 0, 127));   //Set square coverage at index
/*  OSC For Backup PD sketch
        ofxOscMessage oscMessage;       //init oscMessage
        oscMessage.setAddress("/box"+ofToString(i)); // Send OSC messages
        oscMessage.addIntArg(squareCover[i]);
        sender.sendMessage(oscMessage);
*/
    }
}

void squares::draw(){

    ofPushStyle();

    for(int i = 0; i < numSquares; i ++){

        ofColor squareColor = ofColor(255, 255, 0, 255);
        ofSetColor(squareColor);
        ofNoFill();
        ofDrawRectangle(squareX[i], squareY[i], sqWid, sqHig);  //Draw Target Rectangle

        int colAlpha = squareCover[i] * 2;
        ofColor squareFill = ofColor(squareColor, colAlpha);
        ofSetColor(squareFill);
        ofFill();
        ofDrawRectangle(squareX[i], squareY[i], sqWid, sqHig);  //Draw Rectangle
    }
    ofPopStyle();
}
