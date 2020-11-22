#ifndef DDA_ALGORITHM_H
#define DDA_ALGORITHM_H

#include "../FHDRaster/FHDRaster.hpp"

class DDAAlgorithm: public FHDRaster {
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