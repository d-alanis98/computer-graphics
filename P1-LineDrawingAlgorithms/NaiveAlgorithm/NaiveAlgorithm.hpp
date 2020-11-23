#ifndef NAIVE_ALGORITHM_H
#define NAIVE_ALGORITHM_H

#include "../FHDRaster/FHDRaster.hpp"

class NaiveAlgorithm: public FHDRaster {
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