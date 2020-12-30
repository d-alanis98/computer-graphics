#include <iostream>
#include "Pixel.hpp"
#include "../Vector/Vector.hpp"

void printPixelData(Pixel *);

int main() {
    Vector *coordinates = new Vector(10.5, 14.3, -5.4);
    //Methods test
    //Constructor
    Pixel *emptyPixel = new Pixel();
    Pixel *pixelOnlyWithColorData = new Pixel(125, 125, 125);
    Pixel *pixelWithNumericCoordinates = new Pixel(255, 255, 255, 10, 20, 30);
    Pixel *pixelWithVector = new Pixel(212, 125, 10, coordinates);
    //Setters
    emptyPixel->setColor(10, 10, 10);
    emptyPixel->setRedColor(20);
    emptyPixel->set3DSpaceCoordinates(20, 30, 40);
    pixelOnlyWithColorData->set3DSpaceCoordinates(new Vector(100, 200, 300));
    //Presentation
    cout << "Empty pixel (with setted data): " << endl;
    printPixelData(emptyPixel);
    cout << "Pixel with only color data (with setted coordinates): " << endl;
    printPixelData(pixelOnlyWithColorData);
    cout << "Pixel with numeric coordinates: " << endl;
    printPixelData(pixelWithNumericCoordinates);
    cout << "Pixel with coordinates as Vector instance: " << endl;
    printPixelData(pixelWithVector);
    return 0;
}

void printPixelData(Pixel *pixel) {
    //Colors
    cout << "R = " << pixel->getRedColor() << endl;
    cout << "G = " << pixel->getGreenColor() << endl;
    cout << "B = " << pixel->getBlueColor() << endl;
    //3D space coordinates
    Vector *tridimensionalSpaceCoordinates = pixel->get3DSpaceCoordinates();
    cout << "3D space coordinates = ";
    tridimensionalSpaceCoordinates->printVector();
}