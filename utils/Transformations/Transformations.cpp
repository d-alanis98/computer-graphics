#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "Transformations.hpp"
#include "../Matrix/Matrix.hpp"

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
#define abs(x) ((x < 0) ? -1 * x : x)
#define natural(x) ((x < 0) ? 0 : x)

#define PI 3.14159265

using namespace std;

Transformations::Transformations() {
    memset(values, 1, 4);
}

void Transformations::setInitialValues(double x, double y, double z) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
    //The value of w, for the homogeneous space
    values[3] = 1.0;
    this->x = (unsigned int) natural(x);
    this->y = (unsigned int) natural(y);
}

unsigned int Transformations::getX() {
    return x;
}

unsigned int Transformations::getY() {
    return y;
}

Matrix<double> Transformations::getCoordinatesMatrix() {
    Matrix<double> coordinatesMatrix(4, 1, 1);
    for(int i = 0; i < 3; i++)
        coordinatesMatrix(i, 0) = values[i];
    coordinatesMatrix(3, 0) = 1;
    return coordinatesMatrix;
}

//SCALE
void Transformations::scale(double scaleInX = 1, double scaleInY = 1, double scaleInZ = 1) {
    Matrix<double> scaleMatrix(4, 4, 0);
    scaleMatrix(0, 0) = scaleInX;
    scaleMatrix(1, 1) = scaleInY;
    scaleMatrix(2, 2) = scaleInZ;
    scaleMatrix(3, 3) = 1; //w
    Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
    Matrix <double> result = scaleMatrix * coordinatesMatrix;
    for(int i = 0; i < 3; i++)
        this->values[i] = result(i, 0);
}

//ROTATION
void Transformations::rotateX(double degrees) {
    Matrix<double> rotationMatrix(4, 4, 0);
    rotationMatrix(0, 0) = 1;
    rotationMatrix(1, 1) = cos(degrees * PI / 180);
    rotationMatrix(1, 2) = -1 * sin(degrees * PI / 180);
    rotationMatrix(2, 1) = sin(degrees * PI / 180);
    rotationMatrix(2, 2) = cos(degrees * PI / 180);
    rotationMatrix(3, 3) = 1;
    Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
    Matrix <double> result = rotationMatrix * coordinatesMatrix;
    for(int i = 0; i < 3; i++)
        this->values[i] = result(i, 0);
}

void Transformations::rotateY(double degrees) {
    Matrix<double> rotationMatrix(4, 4, 0);
    rotationMatrix(0, 0) = cos(degrees * PI / 180);
    rotationMatrix(0, 2) = -1 * sin(degrees * PI / 180);
    rotationMatrix(1, 1) = 1;
    rotationMatrix(2, 0) = sin(degrees * PI / 180);
    rotationMatrix(2, 2) = cos(degrees * PI / 180);
    rotationMatrix(3, 3) = 1;
    Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
    Matrix <double> result = rotationMatrix * coordinatesMatrix;
    for(int i = 0; i < 3; i++)
        this->values[i] = (unsigned int) natural(result(i, 0));
}

void Transformations::rotateZ(double degrees) {
    Matrix<double> rotationMatrix(4, 4, 0);
    rotationMatrix(0, 0) = cos(degrees * PI / 180);
    rotationMatrix(0, 1) = -1 * sin(degrees * PI / 180);
    rotationMatrix(1, 0) = sin(degrees * PI / 180);
    rotationMatrix(1, 1) = cos(degrees * PI / 180);
    rotationMatrix(2, 2) = 1;
    rotationMatrix(3, 3) = 1;
    Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
    Matrix <double> result = rotationMatrix * coordinatesMatrix;
    for(int i = 0; i < 3; i++)
        this->values[i] = result(i, 0);
}

//TRANSLATION
void Transformations::translateTo(double tx, double ty, double tz) {
    Matrix<double> translationMatrix(4, 4, 0);
    //We fill the diagonal with 1's
    for(int i = 0; i < 4; i++)
        translationMatrix(i, i) = 1;
    translationMatrix(0, 3) = tx;
    translationMatrix(1, 3) = ty;
    translationMatrix(2, 3) = tz;
    Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
    Matrix <double> result = translationMatrix * coordinatesMatrix;
    for(int i = 0; i < 3; i++)
        this->values[i] = result(i, 0);
}

//PROJECTION
void Transformations::makeProjection(double focalLength) {
    Matrix<double> projectionMatrix(4, 4, 0);
    Matrix<double> coordinatesMatrix = getCoordinatesMatrix();
    //We set the projection matrix
    for(int i = 0; i < 3; i++)
        projectionMatrix(i, i) = focalLength;
    projectionMatrix(3, 0) = 1;
    //We make the operation
    Matrix<double> result = projectionMatrix * coordinatesMatrix;
    //We return from the homogeneous space and update the values of (x, y, z , w)
    for(int i = 0; i < 3; i++)
        this->values[i] = result(i, 0) / result(3, 0); //Value / w
    //X now is Y, and Y is Z, because camera is pointing at (1, 0, 0)
    this->x = (unsigned int)values[1];
    this->y = (unsigned int)values[2];
}