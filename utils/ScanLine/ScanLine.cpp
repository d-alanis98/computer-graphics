#include <iostream>
#include <vector>
#include <algorithm>    
#include "ScanLine.hpp"
#include "../PixelWithData/PixelWithData.hpp"

using namespace std;

void sortPixelsByX(vector<PixelWithData *> *); 
bool comparePixelXCoordinate(PixelWithData *, PixelWithData *);
bool comparePixelYCoordinate(PixelWithData *, PixelWithData *);  


//Constructors 

ScanLine::ScanLine() { };

ScanLine::ScanLine(BresenhamAlgorithm *raster) {
    this->raster = raster;
}

ScanLine::ScanLine(BresenhamAlgorithm *raster, vector<PixelWithData *> pixelsToDraw) {
    this->raster = raster;
    setPixelsToDraw(pixelsToDraw);
}

//Getters and setters

void ScanLine::setRaster(BresenhamAlgorithm *raster) {
    this->raster = raster;
}

void ScanLine::setPixelsToDraw(vector<PixelWithData *> pixelsToDraw) {
    this->pixelsToDraw = pixelsToDraw;
}

BresenhamAlgorithm *ScanLine::getRaster() {
    return raster;
}

vector<PixelWithData *> ScanLine::getPixelsToDraw() {
    return pixelsToDraw;
}


//Facade
void ScanLine::fillFaces() {
    sortPixelsByY();
    fillMissingPixels();
}


void ScanLine::fillMissingPixels() {
    unsigned int minimumY = pixelsToDraw[0]->getRasterY();
    unsigned int maximumY = pixelsToDraw[pixelsToDraw.size() - 1]->getRasterY();
    unsigned int currentYStartingIndex = 0;
    for(unsigned int currentY = minimumY; currentY < maximumY + 1; currentY++) {
        vector<PixelWithData *> pixelsWithCurrentY;
        //Move to a external function
        for(int j = currentYStartingIndex; j < pixelsToDraw.size(); j++) {
            PixelWithData *currentPixel = pixelsToDraw[j];
            if(currentPixel->getRasterY() == currentY)
                pixelsWithCurrentY.push_back(currentPixel);
            if(currentPixel->getRasterY() > currentY)
                break;
            currentYStartingIndex++;
        }
        if(pixelsWithCurrentY.size() == 0)
            continue;
        //We sort by x
        sortPixelsByX(&pixelsWithCurrentY);
        //We get the maximum and the minimum
        unsigned int minimumX = pixelsWithCurrentY[0]->getRasterX();
        unsigned int maximumX = pixelsWithCurrentY[pixelsWithCurrentY.size() - 1]->getRasterX();
        //PixelWithData filling
        for(int x = minimumX + 1; x < maximumX; x++)
            raster->setPixel(x, currentY, r, g, b);
    }
}


void ScanLine::sortPixelsByY() {
    sort(pixelsToDraw.begin(), pixelsToDraw.end(), comparePixelYCoordinate); 
}

//Auxiliars

void sortPixelsByX(vector<PixelWithData *> *pixels) {
    sort(pixels->begin(), pixels->end(), comparePixelXCoordinate);
}

bool comparePixelYCoordinate(PixelWithData *p1, PixelWithData *p2) { 
    return (p1->getRasterY() < p2->getRasterY()); 
} 

bool comparePixelXCoordinate(PixelWithData *p1, PixelWithData *p2) { 
    return (p1->getRasterX() < p2->getRasterX()); 
} 


