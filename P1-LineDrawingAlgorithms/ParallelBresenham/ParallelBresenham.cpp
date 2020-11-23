#include <iostream>
#include <algorithm>
#include <thread> 
#include <pthread.h>
#include "ParallelBresenham.hpp"
#include "../BresenhamAlgorithm/BresenhamAlgorithm.hpp"

using namespace std;

ParallelBresenham::ParallelBresenham(void) {
    raster = new BresenhamAlgorithm();
}

void ParallelBresenham::drawLine( 
    unsigned int x1, 
    unsigned int y1, 
    unsigned int x2, 
    unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b
){
    //We set the line segments
    divideLine(x1, y1, x2, y2);

    //We use threads to draw the line segments
    thread thread1(&BresenhamAlgorithm::drawLine, raster, x1, y1, lineSegmentX[0], lineSegmentY[0], r, g, b);
    thread thread2(&BresenhamAlgorithm::drawLine, raster, lineSegmentX[0], lineSegmentY[0], lineSegmentX[1], lineSegmentY[1], r, g, b);
    thread thread3(&BresenhamAlgorithm::drawLine, raster, lineSegmentX[1], lineSegmentY[1], lineSegmentX[2], lineSegmentY[2], r, g, b);
    thread thread4(&BresenhamAlgorithm::drawLine, raster, lineSegmentX[2], lineSegmentY[2], x2, y2, r, g, b);
    
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    
}

void ParallelBresenham::divideLine(
    unsigned int x1, 
    unsigned int y1, 
    unsigned int x2, 
    unsigned int y2
) {
    unsigned int deltaX = (x2 > x1) ? x2 - x1 : x1 - x2;
    unsigned int deltaY = (y2 > y1) ? y2 - y1 : y1 - y2;

    unsigned int minimumInX = (x2 > x1) ? x1 : x2;
    unsigned int minimumInY = (y2 > y1) ? y1 : y2;
    //Line segments in X
    if(deltaX != 0) {
        lineSegmentX[0] = minimumInX + (deltaX / 4);
        lineSegmentX[1] = minimumInX + (deltaX / 2);
        lineSegmentX[2] = minimumInX + (3 * deltaX / 4);
    } else lineSegmentX[0] = lineSegmentX[1] = lineSegmentX[2] = x1;
    //Line segments in Y
    if(deltaY != 0) {
        lineSegmentY[0] = minimumInY + (deltaY / 4);
        lineSegmentY[1] = minimumInY + (deltaY / 2);
        lineSegmentY[2] = minimumInY + (3 * deltaY / 4);
    } else lineSegmentY[0] = lineSegmentY[1] = lineSegmentY[2] = y1;

    if(x2 < x1)
        reverse(lineSegmentX, lineSegmentX + 3);
    if(y2 < y1)
        reverse(lineSegmentY, lineSegmentY + 3);
}

BresenhamAlgorithm *ParallelBresenham::getRaster() {
    return raster;
}
