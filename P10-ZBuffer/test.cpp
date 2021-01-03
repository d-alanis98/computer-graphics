#include <iostream>
#include <set>
#include "../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"
#include "../utils/PixelWithData/PixelWithData.hpp"
#include "../utils/Vector/Vector.hpp"
#include "../utils/VLFToPPM/VLFToPPM.hpp"
#include "../utils/ScanLine/ScanLine.hpp"

using namespace std;

int main(int argc, char **argv) {
    unsigned char r = 255, g = 255, b = 255;

    if(argc != 2) {
        cout << "Usage: ./test pathToVLFFile" << endl;
        exit(1);
    }

    string filePath = argv[1];
    //We create a new VLFToPPM instance and initialize the process of drawing the VLF to the raster
    VLFToPPM *drawer = new VLFToPPM();
    drawer->setDataFromFile(filePath);
    //The camera is pointing at (0,0,-1)
    Vector *cameraVector = new Vector(0, 0, -1);
    drawer->setOnlyTheFacesToShow(cameraVector);
    drawer->setPixelsWithDataToDraw();
    //ScanLine
    ScanLine *scanLineDrawer = new ScanLine(drawer->getRaster(), drawer->getPixelsWithData());
    scanLineDrawer->fillFaces();
    //We draw to the raster
    drawer->drawVLFToRasterWithZBuffer();
    
    return 0;
}