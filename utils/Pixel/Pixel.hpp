#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include "../Vector/Vector.hpp"

using namespace std;

class Pixel {
    private:
        unsigned int r, g, b;
        Vector *tridimensionalSpaceCoordinates;
    public:
        //Constructor
        Pixel();
        Pixel(unsigned int, unsigned int, unsigned int);
        Pixel(unsigned int, unsigned int, unsigned int, Vector *);
        Pixel(unsigned int, unsigned int, unsigned int, double, double, double);
        //Setters and getters
        void setColor(unsigned int, unsigned int, unsigned int);
        void setRedColor(unsigned int);
        void setGreenColor(unsigned int);
        void setBlueColor(unsigned int);
        void set3DSpaceCoordinates(Vector *);
        void set3DSpaceCoordinates(double, double, double);
        unsigned int getRedColor();
        unsigned int getGreenColor();
        unsigned int getBlueColor();
        Vector *get3DSpaceCoordinates();
};

#endif