#include <iostream>
#include "./Pixel.hpp"
#include "../Vector/Vector.hpp"

using namespace std;

//Constructor
Pixel::Pixel() { };

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    this->setColor(r, g, b);
};

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, Vector *tridimensionalSpaceCoordinates) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, double x, double y, double z) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

//Setters and getters
void Pixel::setColor(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
};

void Pixel::setRedColor(unsigned char r) {
    this->r = r;
}

void Pixel::setGreenColor(unsigned char g) {
    this->g = g;
}

void Pixel::setBlueColor(unsigned char b) {
    this->b = b;
}

void Pixel::set3DSpaceCoordinates(Vector *tridimensionalSpaceCoordinates) {
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

void Pixel::set3DSpaceCoordinates(double x, double y, double z) {
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

unsigned char Pixel::getRedColor() {
    return this->r;
};

unsigned char Pixel::getGreenColor() {
    return this->g;
};  

unsigned char Pixel::getBlueColor() {
    return this->b;
};

Vector *Pixel::get3DSpaceCoordinates() {
    return this->tridimensionalSpaceCoordinates;
};
