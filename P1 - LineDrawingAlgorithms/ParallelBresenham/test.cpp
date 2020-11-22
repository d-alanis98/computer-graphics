#include <iostream>
#include "ParallelBresenham.hpp"

using namespace std;

int main() {
    unsigned char r = 255, g = 255, b = 255;
    ParallelBresenham *raster = new ParallelBresenham();
    //Relevant points
    int centerInX = ParallelBresenham::rasterWidth / 2;
    int centerInY = ParallelBresenham::rasterHeight / 2;
    int rasterWidth = ParallelBresenham::rasterWidth;
    int rasterHeight = ParallelBresenham::rasterHeight;
    //Line drawing algorithm test in all the octants
    
    //First octant
    for(int x = centerInX; x < rasterWidth; x += (centerInX / 10))
        raster->drawLine(centerInX, centerInY, x, 0, r, g, b);
    //Second octant
    for(int y = 0; y < centerInY; y += (centerInY / 10))
        raster->drawLine(centerInX, centerInY, rasterWidth, y, r, g, b);
    //Third octant
    for(int y = centerInY; y < rasterHeight; y += (centerInY / 10))
        raster->drawLine(centerInX, centerInY, rasterWidth, y, r, g, b);
    //Fourth octant
    for(int x = rasterWidth; x > centerInX; x -= (centerInX / 10))
        raster->drawLine(centerInX, centerInY, x, rasterHeight, r, g, b);
    //Fifth octant
    for(int x = centerInX; x > 0; x -= (centerInX / 10))
        raster->drawLine(centerInX, centerInY, x, rasterHeight, r, g, b);
    //Sixth octant
    for(int y = rasterHeight; y > centerInY; y -= (centerInY / 10))
        raster->drawLine(centerInX, centerInY, 0, y, r, g, b);
    //Seventh octant
    for(int y = centerInY; y > 0; y -= (centerInY / 10))
        raster->drawLine(centerInX, centerInY, 0, y, r, g, b);
    //Eight octant
    for(int x = 0; x < centerInX; x += (centerInX / 10))
        raster->drawLine(centerInX, centerInY, x, 0, r, g, b);
    raster->getRaster()->write();
}
