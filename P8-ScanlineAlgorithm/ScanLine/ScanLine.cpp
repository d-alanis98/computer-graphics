#include <iostream>
#include <set>
#include <vector>
#include <algorithm>    
#include "ScanLine.hpp"


using namespace std;

void sortPixelsByX(vector<Pixel> *); 
bool comparePixelXCoordinate(Pixel, Pixel);
bool comparePixelYCoordinate(Pixel, Pixel);  


//Constructors 

ScanLine::ScanLine() { };

ScanLine::ScanLine(BresenhamAlgorithm *raster) {
    this->raster = raster;
}

ScanLine::ScanLine(BresenhamAlgorithm *raster, set<Pixel> pixelsToDraw) {
    this->raster = raster;
    setPixelsToDraw(pixelsToDraw);
}

//Getters and setters

void ScanLine::setRaster(BresenhamAlgorithm *raster) {
    this->raster = raster;
}

void ScanLine::setPixelsToDraw(set<Pixel> pixelsToDraw) {;
    this->pixelsToDraw.assign(pixelsToDraw.begin(), pixelsToDraw.end());}

void ScanLine::setPixelsToDraw(vector<Pixel> pixelsToDraw) {
    this->pixelsToDraw = pixelsToDraw;
}

BresenhamAlgorithm *ScanLine::getRaster() {
    return raster;
}

vector<Pixel> ScanLine::getPixelsToDraw() {
    return pixelsToDraw;
}


//Facade
void ScanLine::fillFaces() {
    sortPixelsByY();
    fillMissingPixels();
}


void ScanLine::fillMissingPixels() {
    unsigned int minimumY = pixelsToDraw[0].second;
    unsigned int maximumY = pixelsToDraw[pixelsToDraw.size() - 1].second;
    unsigned int currentYStartingIndex = 0;
    for(unsigned int currentY = minimumY; currentY < maximumY + 1; currentY++) {
        vector<Pixel> pixelsWithCurrentY;
        //Move to a external function
        for(int j = currentYStartingIndex; j < pixelsToDraw.size(); j++) {
            Pixel currentPixel = pixelsToDraw[j];
            if(currentPixel.second == currentY)
                pixelsWithCurrentY.push_back(currentPixel);
            if(currentPixel.second > currentY)
                break;
            currentYStartingIndex++;
        }
        if(pixelsWithCurrentY.size() == 0)
            continue;
        //We sort by x
        sortPixelsByX(&pixelsWithCurrentY);
        //We get the maximum and the minimum
        unsigned int minimumX = pixelsWithCurrentY[0].first;
        unsigned int maximumX = pixelsWithCurrentY[pixelsWithCurrentY.size() - 1].first;
        //Pixel filling
        for(int x = minimumX + 1; x < maximumX; x++)
            raster->setPixel(x, currentY, r, g, b);
    }
}


void ScanLine::sortPixelsByY() {
    sort(pixelsToDraw.begin(), pixelsToDraw.end(), comparePixelYCoordinate); 
}

//Auxiliars

void sortPixelsByX(vector<Pixel> *pixels) {
    sort(pixels->begin(), pixels->end(), comparePixelXCoordinate);
}

bool comparePixelYCoordinate(Pixel p1, Pixel p2) { 
    return (p1.second < p2.second); 
} 

bool comparePixelXCoordinate(Pixel p1, Pixel p2) { 
    return (p1.first < p2.first); 
} 


