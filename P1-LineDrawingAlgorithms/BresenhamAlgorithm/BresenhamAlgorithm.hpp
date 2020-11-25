#ifndef BRESENHAM_ALGORITHM_H
#define BRESENHAM_ALGORITHM_H

#include <iostream>
#include <set>
#include "../FHDRaster/FHDRaster.hpp"

using namespace std;

typedef pair<unsigned int, unsigned int> Pixel;

class BresenhamAlgorithm: public FHDRaster {
    private:
        set<Pixel> pixelsToDraw;
    public:
        void drawLine( 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char
        );
        void setPixelsToDraw(
            unsigned int,
            unsigned int,
            unsigned int,
            unsigned int
        );
        //Pixels to draw
        set<Pixel> getPixelsToDraw();
        void addPixelToDraw(unsigned int, unsigned int);
};

#endif