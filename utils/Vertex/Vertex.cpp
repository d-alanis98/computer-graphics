#include <iostream>
#include "Vertex.hpp"

using namespace std;

Vertex::Vertex() {
    x = 0;
    y = 0; 
    z = 0;
}

Vertex::Vertex(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vertex::getX() {
    return x;
}

double Vertex::getY() {
    return y;
}

double Vertex::getZ() {
    return z;
}

void Vertex::setCoordinates(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}