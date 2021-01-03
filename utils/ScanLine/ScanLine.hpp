#ifndef SCANLINE_H
#define SCANLINE_H

#include <iostream>
#include <set>
#include <vector>
#include "../../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"
#include "../PixelWithData/PixelWithData.hpp"

using namespace std;

class ScanLine {
    private:
        //The raster instance
        BresenhamAlgorithm *raster;
        //The faces fill color will be slightly lighter than the raster background but darker than the line color
        const unsigned char r = 0, g = 130, b = 150;
        //The list of pixels (in vector, in order to be able to sort it)
        vector<PixelWithData *> pixelsToDraw;
    public:
        ScanLine();
        ScanLine(BresenhamAlgorithm *);
        ScanLine(BresenhamAlgorithm *, vector<PixelWithData *>);
        //Getters and setters
        void setRaster(BresenhamAlgorithm *);
        void setPixelsToDraw(vector<PixelWithData *>);
        BresenhamAlgorithm *getRaster();
        vector<PixelWithData *> getPixelsToDraw();
        //Facade
        void fillFaces();
        void fillMissingPixels();
        //Search
        //Utils
        void sortPixelsByY();

};

#endif