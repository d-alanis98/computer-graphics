#ifndef PARALLEL_BRESENHAM_ALGORITHM_H
#define PARALLEL_BRESENHAM_ALGORITHM_H

#include "../FHDRaster/FHDRaster.hpp"
#include "../BresenhamAlgorithm/BresenhamAlgorithm.hpp"

class ParallelBresenham: public FHDRaster {
    private:
        unsigned int lineSegmentX[3];
        unsigned int lineSegmentY[3];
        BresenhamAlgorithm *raster;
    public:
        ParallelBresenham(void);
        void drawLine( 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char
        );
        void divideLine(
            unsigned int,
            unsigned int,
            unsigned int,
            unsigned int
        );
        BresenhamAlgorithm *getRaster();
    
};

#endif