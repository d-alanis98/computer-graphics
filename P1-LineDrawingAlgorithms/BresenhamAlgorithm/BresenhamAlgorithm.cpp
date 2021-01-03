#include <iostream>
#include <set>
#include <vector>
#include <float.h>
#include <cstring>
#include "BresenhamAlgorithm.hpp"
#include "../../utils/PixelWithData/PixelWithData.hpp"

using namespace std;

typedef pair<unsigned int, unsigned int> Pixel;

void BresenhamAlgorithm::drawLine( 
    unsigned int x, 
    unsigned int y, 
    unsigned int x2, 
    unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b
){

    int width = x2 - x;
    int heigth = y2 - y;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

    //We clear the list of pixels to draw
    pixelsToDraw.clear();
    /*
        Increments in X axis
        x2 - x < 0 in 5th, 6th, 7th and 8th octant, and x2 - x > 0 in 1st, 2nd, 3rd and 4th octant
        In 5th, 6th, 7th and 8th octant we are going "backwards" in X, thats why dx1 = -1, othwerwise we go forward, if 0 we won't move in X
    */
    dx1 = (width < 0) ? -1 : (width > 0) ? 1 : 0;
    dx2 = (width < 0) ? -1 : (width > 0) ? 1 : 0;
    /*
        Increments in Y axis
        y2 - y < 0 in 1st, 2nd, 7th and 8th octant, and y2 - y > 0 in 3rd, 4th, 5th and 6th octant
        In 1st, 2nd, 7th and 8th octant we are going "backwards" (up) in Y, thats why dy1 = -1, othwerwise we go forward (down), if 0 we won't move in Y
    */
    dy1 = (heigth < 0) ? -1 : (heigth > 0) ? 1 : 0;

    //We start assuming that the longest magnitude is the width (x2 - x) (this will be verified later)
    int longest = abs(width);
    int shortest = abs(heigth);

    //If height > width we "swap" the direction of the drawing, we are going to do increments or decrements in Y while X remains the same
    if(shortest > longest) {
        //We update with the correct value
        longest = abs(heigth);
        shortest = abs(width);
        dx2 = 0;      
        //The same logic as dy1: In 1st, 2nd, 7th and 8th octant we are going "backwards" (up) in Y, thats why dy2 = -1, othwerwise we go forward (down) dy2 = 1, if 0 we won't move in Y
        dy2 = (heigth < 0) ? -1 : (heigth > 0) ? 1 : 0;    
    }
    
    //To get the half of the number but without performing an expensive division and rounding we use bit operations
    int half = longest >> 1;
    bool criterion;

    //We clear the set of pixels to draw
    initializePixelsToDraw();
    //We start from 0 (the origin of the octants) to the biggest dimension (width or height)
    for(int i = 0; i <= longest; i++) {
        setPixel(x, y, r, g, b);
        //We also add it to the list of pixels
        addPixelToDraw(x, y);
        //We sum the shortest dimension value to the half variable
        half += shortest;
        // If the new half is bigger than the longest value, this mean that we have surpased the limit, so we need to move in the required direction (backward or forward in X or Y)
        criterion = half > longest;
        //If the criterion condition is met, we need to perform the movement along the other axis (the one of the shortest dimension) to get the correct line slope in the final image
        if(criterion) {
            half -= longest;
            x += dx1;
            y += dy1;
        } 
        //Otherwise, we move normally over the longest dimension axis without moving up or down in the other axis, i.e we keep in a straight line wether in X or Y
        else {
            //If the width is the largest dimension, we go backward or forward in X, Y = 0
            x += dx2;
            //If the height is the largest dimension we go backward or forward in Y, X = 0
            y += dy2;
        }
    }
}

void BresenhamAlgorithm::drawLine( 
    unsigned int x, 
    unsigned int y, 
    unsigned int x2, 
    unsigned int y2, 
    PixelWithData *firstPixelData,
    PixelWithData *secondPixelData
) {
    //We get color data from pixel
    unsigned char r = firstPixelData->getRedColor();
    unsigned char g = firstPixelData->getGreenColor();
    unsigned char b = firstPixelData->getBlueColor();
    //We invoke drawLine with PixelWithData instance
    drawLine(x, y, x2, y2, r, g, b);
    //We set the pixel data in state
    setFirstPixelData(firstPixelData);
    setSecondPixelData(secondPixelData);
}

void BresenhamAlgorithm::drawLine(
    unsigned int x, 
    unsigned int y, 
    unsigned int x2, 
    unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b,
    PixelWithData *firstPixelData,
    PixelWithData *secondPixelData
) {
    //We draw line without the PixelWithData instance
    drawLine(x, y, x2, y2, r, g, b);
    //We set the pixel data in state
    setFirstPixelData(firstPixelData);
    setSecondPixelData(secondPixelData);
}



void BresenhamAlgorithm::addPixelToDraw(unsigned int x, unsigned int y) {
    pixelsToDraw.insert(Pixel(x, y));
    //We also push it to the vector of pixels (to keep the original order of the Bresenham algorithm and not the sorted one)
    pixelsVector.push_back(Pixel(x, y));
}

set<Pixel> BresenhamAlgorithm::getPixelsToDraw() {
    return pixelsToDraw;
}


vector<Pixel> BresenhamAlgorithm::getPixelsToDrawVector() {
    return pixelsVector;
}

void BresenhamAlgorithm::initializePixelsToDraw() {
    pixelsVector.clear();
}

void BresenhamAlgorithm::initializePixelsWithDataVector(unsigned int vectorSize) {
    //We clear and resize the vector
    this->pixelsWithData.clear();
}

void BresenhamAlgorithm::setZCoordinateForEachPixel() {
    double firstZCoordinate = firstPixelData->get3DSpaceCoordinates()->getZ();
    double secondZCoordinate = secondPixelData->get3DSpaceCoordinates()->getZ();
    unsigned int numberOfPixels = pixelsVector.size() - 1;
    //We calculate the step
    double step = (double)(secondZCoordinate - firstZCoordinate) / (double) numberOfPixels;
    //We initialize the interpolated Z with the first z coordinate
    double interpolatedZ = firstZCoordinate;
    //We initialize the pixelsWithData vector (for efficiency), and resize it with the known size (number of pixels + 1)
    initializePixelsWithDataVector(numberOfPixels + 1);
    for(Pixel pixel : pixelsVector) {
        //We insert a new PixelWithData instance with the raster coordinates, color data and interpolated Z coordinate for each pixel
        insertPixelWithDataToTheSet(pixel.first, pixel.second, interpolatedZ);
        interpolatedZ += step;
    }
}

void BresenhamAlgorithm::applyZBuffer(vector<PixelWithData *> listOfAllPixelsWithData) {
    initializeSecondaryRaster();
    for(PixelWithData *currentPixelWithData : listOfAllPixelsWithData) {
        unsigned int x = (unsigned int) currentPixelWithData->getRasterX();
        unsigned int y = (unsigned int) currentPixelWithData->getRasterY();
        //We get the current raster pixel for that coordinates
        PixelWithData *rasterPixel = secondaryRaster[x][y];
        //We get the Z coordinate of the current pixel
        double currentPixelZFrom3DSpace = currentPixelWithData->get3DSpaceCoordinates()->getZ();
        //We update the new min Z if the condition is met
        if(currentPixelZFrom3DSpace < rasterPixel->get3DSpaceCoordinates()->getZ())
            secondaryRaster[x][y] = currentPixelWithData;
    }
    //Finally, we set the new data
    setRasterDataFromSecondaryRaster();

}

void BresenhamAlgorithm::insertPixelWithDataToTheSet(double x, double y, double interpolatedZ) {
    PixelWithData *pixelWith3DSpaceZCoordinate = new PixelWithData(
        firstPixelData->getRedColor(),
        firstPixelData->getGreenColor(),
        firstPixelData->getBlueColor(),
        0,
        0,
        interpolatedZ
    );
    pixelWith3DSpaceZCoordinate->setRasterCoordinates(x, y);
    pixelsWithData.push_back(pixelWith3DSpaceZCoordinate);
}

void BresenhamAlgorithm::initializeSecondaryRaster() {
    vector<PixelWithData *> rasterRow;
    for(int i = 0; i < RASTER_WIDTH; i++) {
        rasterRow.clear();
        for(int j = 0; j < RASTER_HEIGHT; j++) {
            rasterRow.push_back(new PixelWithData(
                80,
                80,
                80,
                DBL_MAX,
                DBL_MAX,
                DBL_MAX
            ));
        }
        secondaryRaster.push_back(rasterRow);
    }
}


void BresenhamAlgorithm::setRasterDataFromSecondaryRaster() {
    for(int i = 0; i < RASTER_WIDTH; i++) {
        for(int j = 0; j < RASTER_HEIGHT; j++) {
            PixelWithData *rasterPixelData = secondaryRaster[i][j];
            setPixel(
                rasterPixelData->getRasterX(),
                rasterPixelData->getRasterY(),
                rasterPixelData->getRedColor(),
                rasterPixelData->getGreenColor(),
                rasterPixelData->getBlueColor()
            );
        }
    }
}

void BresenhamAlgorithm::setFirstPixelData(PixelWithData *firstPixelData) {
    this->firstPixelData = firstPixelData;
}

PixelWithData *BresenhamAlgorithm::getFirstPixelData() {
    return firstPixelData;
}

void BresenhamAlgorithm::setSecondPixelData(PixelWithData *secondPixelData) {
    this->secondPixelData = secondPixelData;
}

PixelWithData *BresenhamAlgorithm::getSecondPixelData() {
    return secondPixelData;
}

vector<PixelWithData *> BresenhamAlgorithm::getPixelsWithData() {
    return pixelsWithData;
}