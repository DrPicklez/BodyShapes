/* Class to create a background:
    ** Setup was initially used to remove white pixels from the map
    ** Now using GIMP eddited color inverted image of map.
    ** The returned image is a section of the map
    ** This section is determind by co-ordinates from ofxOpenCV contourFinder blob
    ** map Image taken from duckduckgo search
*/
#include "tubemap.h"
//--------------------------------------------------------------
void tubeMap::setup(int wid, int hig, int cvWid, int cvHig){

    ofWidth = wid;              //setup global dimentions
    ofHeight = hig;
    cvWidth = cvWid;
    cvHeight = cvHig;

    map.load("tubeMapEdit.png");

    mapPixAlpha = map.getPixels();

    width = mapPixAlpha.getWidth();
    height = mapPixAlpha.getHeight();

    rectWid = mapPixAlpha.getWidth() / 6;
    rectHig = mapPixAlpha.getHeight() / 6;

    mapCropped.allocate(rectWid, rectHig, OF_IMAGE_COLOR);
/*
    ofColor black = ofColor(0, 0, 0);

    for(int x = 0; x < width; x++){         //Remove map white.
        for(int y = 0; y < height; y++){

            ofColor mapColor = mapPix.getColor(x, y);
            int averageColor = ((mapColor.r + mapColor.g) + mapColor.b) / 3;    //indexpixelsforfaster

            if(averageColor > 240){
                mapPixAlpha.setColor(x, y, black);          //Set color to black
            }
            else{mapPixAlpha.setColor(x, y, mapColor);}
        }
    }
*/
}

//--------------------------------------------------------------
void tubeMap::update(int xIn, int yIn, int widIn, int higIn){

    ofVec2f dataIn = ofVec2f(xIn, yIn);     //Smoth out data frm contour Finder
    dataIn = dataSmoother(dataIn);

    int xPos = dataIn.x;
    int yPos = dataIn.y;

    xPos = ofMap(xPos, 0, cvWidth, 0, width - widIn,true);      //Scaling to avoid off target
    yPos = ofMap(yPos, 0, cvHeight, 0, height - rectHig,true);

        for(int x = 0; x < rectWid; x ++){      //Draw section of image depending on body position
            for(int y = 0; y < rectHig; y ++){
                int offSetX = (x + xPos);
                int offSetY = (y + yPos);

                ofColor mapColor = mapPixAlpha.getColor(offSetX, offSetY);
                mapCropped.setColor(x, y, mapColor);
            }
        }
}

//--------------------------------------------------------------
void tubeMap::draw(int wid, int hig){
    ofImage image;

    image.setFromPixels(mapCropped);
    image.draw(0, 0, wid, hig);
}

//--------------------------------------------------------------
ofVec2f tubeMap::dataSmoother(ofVec2f input){       //To smooth out the noisy data from contourFinder

    buffCount = buffCount % numPoints;
    points[buffCount].set(input);
    ofVec2f centroid;
    centroid.average(points, numPoints);
    buffCount ++;
    return centroid;
}

