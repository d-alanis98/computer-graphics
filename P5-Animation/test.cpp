#include <iostream>
#include <string>
#include "../P3-P4-OBJToPPM/OBJToPPM.hpp"

using namespace std;

int main(int argc, char **argv) {
    unsigned char r = 255, g = 255, b = 255;

    if(argc != 3) {
        cout << "Usage: ./test pathToOBJFile degrees" << endl;
        exit(1);
    }

    string filePath = argv[1];
    double degreesToRotate = stod(argv[2]);
    //We create a new OBJToPPM instance and initialize the process of drawing the OBJ to the raster
    OBJToPPM *drawer = new OBJToPPM();
    drawer->setDataFromFile(filePath);
    drawer->setDegreesToRotate(degreesToRotate);
    drawer->drawOBJToRaster();
    
    return 0;
}