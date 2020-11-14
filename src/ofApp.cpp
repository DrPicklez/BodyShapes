#include "ofApp.h"


/* Created by William Parry,

 * Uses primitive tools within openFrameworks & third party addons:
 * http://openframeworks.cc/
 * ofxKinext, ofxMaxim, ofxOpenCv, ofxBlur ofxOsc.

 * Requires Audio & Image files in bin/data (https://www.dropbox.com/sh/i3u1ehl5f2ott1t/AABwjK7HbHD8NsUxDO5JWlxia?dl=0).
 * ofxMaxim requires Jack audio control if using in Linux.

 * Requires Microsoft Kinect.
*/

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundColor(0);

    video.init();
    video.open();

    nearThreshold = 250;    //CV Focussing
    farThreshold = 150;

    grayImage.allocate(video.width, video.height); //Allocate space to avoid error messages
    blur.allocate(video.width, video.height);
    mask.allocate(video.width, video.height);
    bufferForStretch.allocate(mask.width, mask.height);     //init FBO and clear it
    bufferForStretch.begin();
    ofClear(0, 0, 0, 0);
    bufferForStretch.end();

    blurz.setup(ofGetWidth(), ofGetHeight(), 4, .1, 5);

    maxPeople = 1;

    for(int i = 0; i < maxPeople; i ++){
        bodyImage bodyVec;      // allocate seperate images for multiple bodies
        body.push_back(bodyVec); //create a setup once for body image to reference images
        body[i].setup(i + 1);
    }

    map.setup(ofGetWidth(), ofGetHeight(), mask.width, mask.height);
    targets.setup(mask.getWidth(), mask.getHeight(), 10);

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

    if (video.isFrameNew() ) { //new frame if needed
        depthFocus();
        contourFinder.findContours(mask, 10, (mask.width * mask.height), maxPeople, false, false);

        if(contourFinder.nBlobs > 0){
        ofRectangle rectOne = contourFinder.blobs.at(0).boundingRect;
        map.update(rectOne.x, rectOne.y, rectOne.width, rectOne.height);
        }

        for(int i = 0; i < contourFinder.nBlobs; i++){
            ofRectangle rect = contourFinder.blobs.at(i).boundingRect;
            body[i].update(mask, rect.x, rect.y, rect.width, rect.height); //Draw the seperate bodyImages
            body[i].imageFlip();
        }

        targets.update(mask);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(contourFinder.nBlobs > 0){
        map.draw(ofGetWidth(), ofGetHeight());
    }
    bufferForStretch.begin();       //strech bodies to window & add seperate blur effect
//    blurz.begin();                        /////BLUR!!
    ofSetColor(0, 0, 0, 20);   //Blur Effect #1
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());     //Create background
    for(int i = 0; i < contourFinder.nBlobs; i++){
        body[i].draw();
    }
//    blurz.end();                        /////BLUR!!
//    blurz.draw();                        /////BLUR!!

    targets.draw();                   //Only for debugging

    ofPushStyle();
    ofSetColor(0, 255, 0, 255);
    ofPopStyle();
    bufferForStretch.end();
    bufferForStretch.draw(0, 0, ofGetWidth(), ofGetHeight());
//    video.drawDepth(0, 0, ofGetWidth(), ofGetHeight());
//    ofDrawBitmapString("Threshold:" + ofToString(thresh), 10, 10);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int button){
    if(button == '>'){
        farThreshold ++;}
    if(button == '<'){
        farThreshold -- ;}

}
//--------------------------------------------------------------
void ofApp::depthFocus(){

    grayImage.setFromPixels(video.getDepthPixels());

    ofPixels pix = grayImage.getPixels();
    int numPixels = pix.size();
    for(int i = 0; i < numPixels; i++) {
        if(pix[i] < farThreshold) {   //Thresholding
            pix[i] = 0;
        }
    }

    blur.setFromPixels(pix);
    blur.blurGaussian(5);   //blur to remove sore edges
    blur.mirror(0, 1);
    mask = blur;
    grayImage.flagImageChanged();
}
