#ifndef PIXEL_WITH_DATA_H
#define PIXEL_WITH_DATA_H

#include <iostream>
#include "../Color/Color.hpp"
#include "../Vector/Vector.hpp"

using namespace std;

class PixelWithData {
    private:
        unsigned char r, g, b;
        double rasterX, rasterY;
        Vector *tridimensionalSpaceCoordinates;
    public:
        //Constructor
        PixelWithData();
        PixelWithData(Color, Vector *);
        PixelWithData(unsigned char, unsigned char, unsigned char);
        PixelWithData(unsigned char, unsigned char, unsigned char, Vector *);
        PixelWithData(unsigned char, unsigned char, unsigned char, double, double, double);
        //Setters and getters
        void setColor(Color pixelColor) {
            r = pixelColor.getRedColor();
            g = pixelColor.getGreenColor();
            b = pixelColor.getBlueColor();
        }
        void setColor(unsigned char, unsigned char, unsigned char);
        void setRedColor(unsigned char);
        void setGreenColor(unsigned char);
        void setBlueColor(unsigned char);
        void setRasterCoordinates(double, double);
        void set3DSpaceCoordinates(Vector *);
        void set3DSpaceCoordinates(double, double, double);
        double getRasterX();
        double getRasterY();
        unsigned char getRedColor();
        unsigned char getGreenColor();
        unsigned char getBlueColor();
        Color getPixelColor() {
            return Color(r, g, b);
        };
        Vector *get3DSpaceCoordinates();
        void printPixelData() {
            cout << "\tRaster coordinates = (" << rasterX << ", " << rasterY << ")\n";
            cout << "\tColor = ";
            getPixelColor().printColors();
            cout << "\t3D Space coordinates = ";
            tridimensionalSpaceCoordinates->printVector();
        }
};

#endif