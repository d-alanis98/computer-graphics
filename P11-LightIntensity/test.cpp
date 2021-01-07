#include <iostream>
#include <vector>
#include "../utils/Scene/Scene.hpp"
#include "../utils/Color/Color.hpp"
#include "../utils/Camera/Camera.hpp"
#include "../utils/Light/Light.hpp"
#include "../utils/Vector/Vector.hpp"
#include "../utils/Light/DirectedLight/DirectedLight.hpp"
#include "../utils/PixelWithData/PixelWithData.hpp"
#include "../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"
#include "../utils/PixelWithData/PixelWithData.hpp"
#include "../utils/Vector/Vector.hpp"
#include "../utils/VLFToPPM/VLFToPPM.hpp"
#include "../utils/ScanLine/ScanLine.hpp"

using namespace std;

void addLightsToTheScene(Scene *tridimensionalScene);

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
    drawer->setEdgeColor(Color(0, 120, 0));
    //We create the scene
    Scene *tridimensionalScene = new Scene();
    //We add the camera
    Camera camera;
    //The camera is located at (0,0,-1)
    camera.setPosition(new Vector(0.0, 0.0, -1.0));
    tridimensionalScene->setCamera(camera);
    //We set ambient light color
    tridimensionalScene->setAmbientLightColor(Color(10, 10, 10));
    //We add lights to the scene
    addLightsToTheScene(tridimensionalScene);
    //We get only the camera position for the face hidding algorithm
    Vector *cameraVector = camera.getPosition();
    drawer->setOnlyTheFacesToShow(cameraVector);
    drawer->setPixelsWithDataToDraw();
    //ScanLine
    ScanLine *scanLineDrawer = new ScanLine(drawer->getRaster(), drawer->getPixelsWithData());
    scanLineDrawer->fillFaces();
    //We draw to the raster
    drawer->drawVLFToRasterWithZBuffer(tridimensionalScene);
    
    return 0;
}

void addLightsToTheScene(Scene *tridimensionalScene) {
    //Directed lights
    DirectedLight directedLight1;
    directedLight1.setLightColor(Color(255, 0, 255));
    directedLight1.setPosition(new Vector(0.0, 0.0, 5.0));
    tridimensionalScene->addDirectedLight(directedLight1);
    DirectedLight directedLight2;
    directedLight2.setLightColor(Color(22, 30, 16));
    directedLight2.setPosition(new Vector(-1.5, 0.5, -10.0));
    tridimensionalScene->addDirectedLight(directedLight2);
}