#include <iostream>
#include "./Pixel.hpp"
#include "../Vector/Vector.hpp"

using namespace std;

//Constructor
Pixel::Pixel() { };

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) {
    this->setColor(r, g, b);
};

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b, Vector *tridimensionalSpaceCoordinates) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b, double x, double y, double z) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

//Setters and getters
void Pixel::setColor(unsigned int r, unsigned int g, unsigned int b) {
    this->r = r;
    this->g = g;
    this->b = b;
};

void Pixel::setRedColor(unsigned int r) {
    this->r = r;
}

void Pixel::setGreenColor(unsigned int g) {
    this->g = g;
}

void Pixel::setBlueColor(unsigned int b) {
    this->b = b;
}

void Pixel::set3DSpaceCoordinates(Vector *tridimensionalSpaceCoordinates) {
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

void Pixel::set3DSpaceCoordinates(double x, double y, double z) {
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

unsigned int Pixel::getRedColor() {
    return this->r;
};

unsigned int Pixel::getGreenColor() {
    return this->g;
};  

unsigned int Pixel::getBlueColor() {
    return this->b;
};

Vector *Pixel::get3DSpaceCoordinates() {
    return this->tridimensionalSpaceCoordinates;
};
