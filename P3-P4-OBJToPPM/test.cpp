#include <iostream>
#include "OBJToPPM.hpp"

int main(int argc, char **argv) {
    unsigned char r = 255, g = 255, b = 255;

    if(argc != 2) {
        cout << "Usage: ./test pathToOBJFile" << endl;
        exit(1);
    }

    string filePath = argv[1];
    //We create a new OBJToPPM instance and initialize the process of drawing the OBJ to the raster
    OBJToPPM *drawer = new OBJToPPM();
    drawer->setDataFromFile(filePath);
    drawer->drawOBJToRaster();
    
    return 0;
}