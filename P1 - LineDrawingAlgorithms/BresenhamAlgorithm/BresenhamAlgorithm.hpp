#ifndef BRESENHAM_ALGORITHM_H
#define BRESENHAM_ALGORITHM_H

#include "../FHDRaster/FHDRaster.hpp"

class BresenhamAlgorithm: public FHDRaster {
    public:
        static const int rasterWidth = RASTER_WIDTH;
        static const int rasterHeight = RASTER_HEIGHT;
        void drawLine( 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char
        );
};

#endif