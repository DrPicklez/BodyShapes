/*Class to create seperate flow of images behind a certain blob entering CV
 * Needed for multiple people entering screen:
      ** Find way of referencing images seperately
      ** Only call setup once to avoid mega memory
      ** microFocussing no longer required as probably only going to be one blob in view
 */
#include "bodyimage.h"
//--------------------------------------------------------------
void bodyImage::setup(int imageNum){

    imageNumN = imageNum;

    numImagesInFolder = 40;
    imageTiming = 6;    //use even for %
    counter = 0;    //Use counter in class instead of framenum to avoid error messages, only trigger on newCameraframe

    for(int i = 0; i < numImagesInFolder; i++){     //Find way of loading the images once to reduce required memory, instead of by vector
        ofImage image;
        loadedImage.push_back(image);

        loadedImage[i].load("a" + ofToString(i) + ".jpg");
        loadedImage[i].resize(ofGetWidth(), ofGetHeight());
    }
}
//--------------------------------------------------------------
void bodyImage::update(ofxCvGrayscaleImage mask, int xIn, int yIn, int widIn, int higIn){

    x = xIn;
    y = yIn;
    wIn = widIn;
    hIn = higIn;

    wid = mask.getWidth();
    hig= mask.getHeight();

    ofPixels maskPix = mask.getPixels();

    ofPixels colorfull;
    colorfull.allocate(wIn, hIn, OF_IMAGE_COLOR_ALPHA);

    ofColor b = ofColor(0, 0, 0, 0);        //clear bground

    for(int i = 0; i < widIn; i ++){        //This method a lot quicker than cropping, **using method from squares
        for(int j = 0; j < higIn; j ++){

            int offSetX = (i + x);
            int offSetY = (j + y);
            int index = (wid * offSetY + offSetX);

            ofColor c = loadedImage[imageNumN].getColor(offSetX, offSetY);

            if(maskPix[index] > 0){ // Scrub Pixels for pixels in macro focus
/* microFocussing FOR REFERENCE
                if(maskPix[index + 1] > closeRange){    //Find close and far values for microfocus, allowing for overlap
                  closeRange = maskPix[index];
                }
                if(maskPix[index + 1] < farRange){
                  farRange = maskPix[index];
                }
                if((maskPix[index] < farRange)&&(maskPix[index] > closeRange)){
*/
                    colorfull.setColor(i, j, c);
                }

            else{colorfull.setColor(i, j, b);}
        }
    }

    /* cropping method FOR REFERENCE
        for(int i = 0; i < wid; i ++){
            for(int j = 0; j < hig; j ++){
                int maskIndex = wid * j + i;


                if(maskPix[maskIndex] > closeRange){    //Find Closest Value
                    closeRange = maskPix;
                }
                ofColor c = loadedImage.getColor(i, j);
                if(maskPix[maskIndex] > 0){ // Scrub Pixels for all in range !!change later for multi detect!!
                   colorfull.setColor(i, j, c);
            }
                else{colorfull.setColor(i, j, b);}
        }
    }
*/

    colorImage.setFromPixels(colorfull);
    counter ++;
    counter = counter % imageTiming;
}
//--------------------------------------------------------------
void bodyImage::imageFlip(){

    if((counter) == 0){       //Loading Images seperately during playback KillingFrameRate find a way of storing within a buffer
          imageNumN = int(ofRandom(0, numImagesInFolder));
    }
    bool vert, horz;        //Flipping for nautious effect
    if((counter % imageTiming) == imageTiming/2){
        vert = !vert;
    }
    if((counter % imageTiming) == 0){
        horz = !horz;
    }
    loadedImage[imageNumN].mirror(vert,horz);
}
//--------------------------------------------------------------
void bodyImage::draw(){
    ofSetColor(255,255,255,255);
    colorImage.draw(x, y, wIn, hIn);
}
