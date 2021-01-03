#include <iostream>
#include "PixelWithData.hpp"
#include "../Vector/Vector.hpp"

void printPixelData(PixelWithData *);

int main() {
    Vector *coordinates = new Vector(10.5, 14.3, -5.4);
    //Methods test
    //Constructor
    PixelWithData *emptyPixel = new PixelWithData();
    PixelWithData *pixelOnlyWithColorData = new PixelWithData(125, 125, 125);
    PixelWithData *pixelWithNumericCoordinates = new PixelWithData(255, 255, 255, 10, 20, 30);
    PixelWithData *pixelWithVector = new PixelWithData(212, 125, 10, coordinates);
    //Setters
    emptyPixel->setColor(64, 64, 64);
    emptyPixel->setRedColor(65);
    emptyPixel->set3DSpaceCoordinates(20, 30, 40);
    pixelOnlyWithColorData->set3DSpaceCoordinates(new Vector(100, 200, 300));
    //Presentation
    cout << "Empty PixelWithData (with setted data): " << endl;
    printPixelData(emptyPixel);
    cout << "PixelWithData with only color data (with setted coordinates): " << endl;
    printPixelData(pixelOnlyWithColorData);
    cout << "PixelWithData with numeric coordinates: " << endl;
    printPixelData(pixelWithNumericCoordinates);
    cout << "PixelWithData with coordinates as Vector instance: " << endl;
    printPixelData(pixelWithVector);
    return 0;
}

void printPixelData(PixelWithData *PixelWithData) {
    //Colors
    cout << "R = " << PixelWithData->getRedColor() << endl;
    cout << "G = " << PixelWithData->getGreenColor() << endl;
    cout << "B = " << PixelWithData->getBlueColor() << endl;
    //3D space coordinates
    Vector *tridimensionalSpaceCoordinates = PixelWithData->get3DSpaceCoordinates();
    cout << "3D space coordinates = ";
    tridimensionalSpaceCoordinates->printVector();
}