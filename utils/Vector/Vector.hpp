#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <iostream>
#include <vector>

using namespace std;

class Vector {
    private:
        double x, y, z;
    public:
        //Constructor
        Vector();
        Vector(double, double, double);
        //Setters and getters
        void setX(double);
        void setY(double);
        void setZ(double);
        void setCoordinates(double, double, double);
        double getX();
        double getY();
        double getZ();
        const vector<double> getCoordinates();
        //Vector operations
        Vector *sum(Vector *);
        double getModule();
        Vector *multiply(Vector *);
        Vector *normalize();
        Vector *substract(Vector *);
        double dotProduct(Vector *);
        Vector *crossProduct(Vector *);
        double getAngleBetween(Vector *);
        //Utils
        void printVector(); 
};


#endif