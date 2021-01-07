#include <iostream>
#include <vector>
#include <math.h> 
#include "./Vector.hpp"

#define PI 3.14159265358979323846

using namespace std;

//Constructor
Vector::Vector() { };

Vector::Vector(double x, double y, double z) {
    this->setCoordinates(x, y, z);
};

//Setters and getters
void Vector::setX(double x) {
    this->x = x;
};

void Vector::setY(double y) {
    this->y = y;
};

void Vector::setZ(double z) {
    this->z = z;
};

void Vector::setCoordinates(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
};

double Vector::getX() {
    return x;
};

double Vector::getY() {
    return y;
};

double Vector::getZ() {
    return z;
};

const vector<double> Vector::getCoordinates() {
    vector<double> coordinates;
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
    return coordinates;
}

//Vector operations
Vector *Vector::sum(Vector *other) {
    return new Vector(
        this->getX() + other->getX(),
        this->getY() + other->getY(),
        this->getZ() + other->getZ()
    );
}

double Vector::getModule() {
    return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
}

Vector *Vector::multiply(Vector *other) {
    Vector *result = new Vector(0, 0, 0);
    vector<double> resultVectorCoordinates = result->getCoordinates();
    vector<double> currentVectorCoordinates = this->getCoordinates();
    vector<double> secondVectorCoordinates = other->getCoordinates();

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            resultVectorCoordinates[i] += currentVectorCoordinates[i] * secondVectorCoordinates[j];

    result->setCoordinates(resultVectorCoordinates[0], resultVectorCoordinates[1], resultVectorCoordinates[2]);
    return result;
}

Vector *Vector::normalize() {
    double module = this->getModule();
    return new Vector(
        this->getX() / module,
        this->getY() / module,
        this->getZ() / module
    );
}

Vector *Vector::substract(Vector *other) {
    return new Vector(
        this->getX() - other->getX(),
        this->getY() - other->getY(),
        this->getZ() - other->getZ()
    );
}

double Vector::dotProduct(Vector *other) {
    return (this->getX() * other->getX()) + (this->getY() * other->getY()) + (this->getZ() * other->getZ());
}

Vector *Vector::crossProduct(Vector *other) {
    return new Vector(
        (this->getY() * other->getZ()) - (this->getZ() * other->getY()),
        (this->getZ() * other->getX()) - (this->getX() * other->getZ()),
        (this->getX() * other->getY()) - (this->getY() * other->getX())
    );
}

double Vector::getDistanceTo(Vector *other) {
    return sqrt(pow(this->x - other->getX(), 2) + pow(this->y - other->getY(), 2) + pow(this->z - other->getZ(), 2));
}

double Vector::getAngleBetween(Vector *other) {
    return acos(this->dotProduct(other) / ( this->getModule() * other->getModule())) * 180 / PI;
}


//Utils
void Vector::printVector() {
    cout << "(" << this->getX() << ", " << this->getY() << ", " << this->getZ() << ")" << endl;
}