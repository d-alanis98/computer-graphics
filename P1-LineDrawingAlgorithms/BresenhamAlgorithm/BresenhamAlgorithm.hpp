#ifndef BRESENHAM_ALGORITHM_H
#define BRESENHAM_ALGORITHM_H

#include "../FHDRaster/FHDRaster.hpp"

class BresenhamAlgorithm: public FHDRaster {
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
};

#endif