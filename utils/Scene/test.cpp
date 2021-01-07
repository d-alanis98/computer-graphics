#include <iostream>
#include <vector>
#include "Scene.hpp"
#include "../Color/Color.hpp"
#include "../Camera/Camera.hpp"
#include "../Light/Light.hpp"
#include "../Vector/Vector.hpp"
#include "../Light/DirectedLight/DirectedLight.hpp"
#include "../PixelWithData/PixelWithData.hpp"

using namespace std;


int main() {
    //We create the scene
    Scene *tridimensionalScene = new Scene();
    //We add the camera
    Camera camera;
    camera.setPosition(new Vector(0.0, 0.0, -1.0));
    tridimensionalScene->setCamera(camera);
    //We set ambient light color
    tridimensionalScene->setAmbientLightColor(Color(20, 20, 20));
    cout << "Ambient light = ";
    tridimensionalScene->getAmbienLight().printLightColor();
    //We create and add two directed lights
    //Directed light 1
    DirectedLight directedLight1;
    directedLight1.setLightColor(Color(15, 12, 18));
    directedLight1.setPosition(new Vector(1.5, 3.5, -4.1));
    cout << "Directed light 1 = ";
    directedLight1.printLightColor();
    tridimensionalScene->addDirectedLight(directedLight1);
    //Directed light 2
    DirectedLight directedLight2;
    directedLight2.setLightColor(Color(22, 30, 16));
    directedLight2.setPosition(new Vector(-2.1, 2.78, 3.25));
    cout << "Directed light 2 = ";
    directedLight2.printLightColor();
    tridimensionalScene->addDirectedLight(directedLight2);
    //We create fake pixels
    Color pixel1InitialColor(134, 67, 23);
    Color pixel2InitialColor(14, 19, 113);
    cout << "Pixel 1 initial color = ";
    pixel1InitialColor.printColors();
    cout << "Pixel 2 initial color = ";
    pixel2InitialColor.printColors();
    PixelWithData *pixel1 = new PixelWithData(pixel1InitialColor, new Vector(0, 2.5, -1.3));
    PixelWithData *pixel2 = new PixelWithData(pixel2InitialColor, new Vector(-1.5, 4.2, 11.3));
    vector<PixelWithData *> pixels;
    pixels.push_back(pixel1);
    pixels.push_back(pixel2);
    tridimensionalScene->setPixelsToDraw(pixels);
    tridimensionalScene->computePixelsColors();
    pixels = tridimensionalScene->getPixelsToDraw();
    cout << "Pixel 1 final color = ";
    pixels[0]->getPixelColor().printColors();
    cout << "Pixel 2 final color = ";
    pixels[1]->getPixelColor().printColors();
    return 0;
}