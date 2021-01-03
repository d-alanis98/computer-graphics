#ifndef BRESENHAM_ALGORITHM_H
#define BRESENHAM_ALGORITHM_H

#include <iostream>
#include <set>
#include <vector>
#include "../FHDRaster/FHDRaster.hpp"
#include "../../utils/PixelWithData/PixelWithData.hpp"

using namespace std;

typedef pair<unsigned int, unsigned int> Pixel;

class BresenhamAlgorithm: public FHDRaster {
    private:
        //List of pixels
        set<Pixel> pixelsToDraw;
        vector<PixelWithData *> pixelsWithData;
        vector<Pixel> pixelsVector;
        //Data about vertices pixels
        PixelWithData *firstPixelData, *secondPixelData;
        //Secondary raster for z buffer
        vector<vector<PixelWithData *>> secondaryRaster;
    public:
        void drawLine(
            unsigned int,
            unsigned int,
            unsigned int,
            unsigned int,
            PixelWithData *,
            PixelWithData *
        );
        void drawLine( 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char
        );
        void drawLine( 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char,
            PixelWithData *,
            PixelWithData *
        );
        //Getters and setters
        void setFirstPixelData(PixelWithData *);
        set<Pixel> getPixelsToDraw();
        PixelWithData *getFirstPixelData();
        void setSecondPixelData(PixelWithData *);
        PixelWithData *getSecondPixelData();
        vector<PixelWithData *> getPixelsWithData();
        vector<Pixel> getPixelsToDrawVector();
        //Set addition
        void addPixelToDraw(unsigned int, unsigned int);
        void insertPixelWithDataToTheSet(double, double, double);
        //Z buffer
        void applyZBuffer(vector<PixelWithData *> );
        void setZCoordinateForEachPixel();
        //Secondary raster for Z buffer
        void initializeSecondaryRaster();
        void setRasterDataFromSecondaryRaster();
        //Miscelaneous
        void initializePixelsToDraw();
        void initializePixelsWithDataVector(unsigned int); 
};

#endif