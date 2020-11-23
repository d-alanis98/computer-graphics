#include <iostream>
#include <cstring>
#include "FHDRaster.hpp"


using namespace std;

FHDRaster::FHDRaster() {
    //To get the RGB(80,80,80), HEX(#505050) a dark gray background to fill the raster
    memset(data, 80, 1920 * 1080 * 3); 
}

void FHDRaster::setPixel(
    unsigned int x, 
    unsigned int y, 
    unsigned char r, 
    unsigned char g, 
    unsigned char b
) {
    if (x >= 1920 || y >= 1080)
        return;
    data[x][y][0] = r;
    data[x][y][1] = g;
    data[x][y][2] = b;
}

void FHDRaster::write(void) {
    int x = 0; 
    int y = 0;
    //PPM header
    cout << "P6" << endl;
    cout << RASTER_WIDTH << " " << RASTER_HEIGHT <<  " 255\n";
    //Data
    for (y = 0; y < RASTER_HEIGHT; y++) {
        for (x = 0; x < RASTER_WIDTH; x++) {
            cout<<data[x][y][0];
            cout<<data[x][y][1];
            cout<<data[x][y][2];
        } 
    } 
}
