#include <iostream>
#include "DDAAlgorithm.hpp"

using namespace std;



void DDAAlgorithm::drawLine( 
    unsigned int x1, 
    unsigned int y1, 
    unsigned int x2, 
    unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b
){
    double m = (double)((double)y2 - (double)y1) / (double)((double)x2 - (double)x1); //Line segment slope
    double be = (double)y1 - (m * (double)x1);
    //X and Y for the pixel status
    unsigned int x = x1 + 1;
    double y = 0;
    //Maximum value in x, initialized with x2, later it will be updated if necessary
    unsigned int maximumInX = x2;
    unsigned int minimumInX = x1;

    //Initial points
    setPixel(x1, y1, r, g, b);
    setPixel(x2, y2, r, g, b);

    //x2 - x1 cannot be 0, in that case, we need to draw a vertical line
    if((x2 - x1) == 0) {
        unsigned int maximumInY = y2 > y1 ? y2 : y1;
        x = x1;
        y = y2 > y1 ? y1 : y2;
        for (y; y < maximumInY; y++)
            setPixel(x1, (int)y, r, g, b);
    }
    //We check if it is necessary to swap the maximum in X and the initial x value
    else if(x2 < x1) { 
        maximumInX = x1;
        minimumInX = x2;
        x = x2 + 1;
    }
    
    //Initial Y for DDA algorithm
    y = (m * (double)minimumInX) + be;
    
    for (x; x < maximumInX; x++) {
        y = y + m;
        setPixel(x, (int)y, r, g, b);
    } 
}

