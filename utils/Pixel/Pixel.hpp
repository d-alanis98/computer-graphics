#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include "../Vector/Vector.hpp"

using namespace std;

class Pixel {
    private:
        unsigned char r, g, b;
        Vector *tridimensionalSpaceCoordinates;
    public:
        //Constructor
        Pixel();
        Pixel(unsigned char, unsigned char, unsigned char);
        Pixel(unsigned char, unsigned char, unsigned char, Vector *);
        Pixel(unsigned char, unsigned char, unsigned char, double, double, double);
        //Setters and getters
        void setColor(unsigned char, unsigned char, unsigned char);
        void set3DSpaceCoordinates(Vector *);
        void set3DSpaceCoordinates(double, double, double);
        unsigned char getRedColor();
        unsigned char getGreenColor();
        unsigned char getBlueColor();
        Vector *get3DSpaceCoordinates();
};

#endif