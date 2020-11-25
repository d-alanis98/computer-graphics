#include <iostream>
#include <string>
#include "ScanLine/ScanLine.hpp"
#include "../utils/VLFToPPM/VLFToPPM.hpp"

using namespace std;

int main(int argc, char **argv){

    if(argc != 2) {
        cout << "Usage: ./test pathToVLFFile" << endl;
        exit(1);
    }

    string filePath = argv[1];
    //We create a new VLFToPPM instance and initialize the process of drawing the VLF to the raster
    VLFToPPM *drawer = new VLFToPPM();
    drawer->setDegreesToRotate(190);
    drawer->setDataFromFile(filePath);
    drawer->setTotalPixelsToDraw();
    //We fill the faces
    ScanLine *scanLineDrawer = new ScanLine(drawer->getRaster(), drawer->getPixelsToDraw());
    scanLineDrawer->fillFaces();
    //We draw the "structure" (edges) and generate the PPM output
    drawer->drawVLFToRaster();
    
    return 0;
}