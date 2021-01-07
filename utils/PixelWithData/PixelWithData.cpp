#include <iostream>
#include "./PixelWithData.hpp"
#include "../Color/Color.hpp"
#include "../Vector/Vector.hpp"

using namespace std;

//Constructor
PixelWithData::PixelWithData() { };

PixelWithData::PixelWithData(Color pixelColor, Vector *tridimensionalSpaceCoordinates) {
    this->setColor(pixelColor.getRedColor(), pixelColor.getGreenColor(), pixelColor.getBlueColor());
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
}

PixelWithData::PixelWithData(unsigned char r, unsigned char g, unsigned char b) {
    this->setColor(r, g, b);
};

PixelWithData::PixelWithData(unsigned char r, unsigned char g, unsigned char b, Vector *tridimensionalSpaceCoordinates) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

PixelWithData::PixelWithData(unsigned char r, unsigned char g, unsigned char b, double x, double y, double z) {
    this->setColor(r, g, b);
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

//Setters and getters
void PixelWithData::setColor(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
};

void PixelWithData::setRedColor(unsigned char r) {
    this->r = r;
}

void PixelWithData::setGreenColor(unsigned char g) {
    this->g = g;
}

void PixelWithData::setBlueColor(unsigned char b) {
    this->b = b;
}

void PixelWithData::setRasterCoordinates(double rasterX, double rasterY) {
    this->rasterX = rasterX;
    this->rasterY = rasterY;
}

void PixelWithData::set3DSpaceCoordinates(Vector *tridimensionalSpaceCoordinates) {
    this->tridimensionalSpaceCoordinates = tridimensionalSpaceCoordinates;
};

void PixelWithData::set3DSpaceCoordinates(double x, double y, double z) {
    this->tridimensionalSpaceCoordinates = new Vector(x, y, z);
};

double PixelWithData::getRasterX() {
    return rasterX;
}

double PixelWithData::getRasterY() {
    return rasterY;
}

unsigned char PixelWithData::getRedColor() {
    return this->r;
};

unsigned char PixelWithData::getGreenColor() {
    return this->g;
};  

unsigned char PixelWithData::getBlueColor() {
    return this->b;
};

Vector *PixelWithData::get3DSpaceCoordinates() {
    return this->tridimensionalSpaceCoordinates;
};
