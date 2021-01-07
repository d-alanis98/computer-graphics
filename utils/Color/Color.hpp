#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

#define MAX_COLOR_VALUE 255

class Color {
    private:
        unsigned char r, g, b;
        static const unsigned char maximumColorValue = MAX_COLOR_VALUE;
    public:
        //Constructors
        Color() { };
        Color(unsigned char r, unsigned char g, unsigned char b) {
            this->setColor(r, g, b);
        };
        //Setters and getters
        void setColor(unsigned char r, unsigned char g, unsigned char b) {
            this->r = r;
            this->g = g;
            this->b = b;
        };
        void setRedColor(unsigned char r) {
            this->r = r;
        };
        void setGreenColor(unsigned char g) {
            this->g = g;
        };
        void setBlueColor(unsigned char b){
            this->b = b;
        };
        unsigned char getRedColor() {
            return r;
        };
        unsigned char getGreenColor() {
            return g;
        };
        unsigned char getBlueColor() {
            return b;
        };
        //Operators
        Color operator+(const Color &secondColor) {
            Color color(
                cropColorToMaximumValue(this->r + secondColor.r),
                cropColorToMaximumValue(this->g + secondColor.g),
                cropColorToMaximumValue(this->b + secondColor.b)
            );
            return color;
        };

        Color operator*(const double &factor) {
            Color color(
                cropColorToMaximumValue((double)this->r * factor),
                cropColorToMaximumValue((double)this->g * factor),
                cropColorToMaximumValue((double)this->b * factor)
            );
            return color;
        }
        //Utils
        unsigned char cropColorToMaximumValue(int color) {
            return color > this->maximumColorValue ? this->maximumColorValue : color;
        };

        void printColors() {
            cout << "(" << (int)r << ", " << (int)g << ", " << (int)b << ")\n";
        }

};

#endif