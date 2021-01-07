#ifndef LIGHT_H
#define LIGHT_H

#include "../Vector/Vector.hpp"
#include "../Color/Color.hpp"

class Light {
    protected:
        Color lightColor;
        Vector *position;
    public:
        //Constructors
        Light() { 
            lightColor = Color(0, 0, 0); 
            position  = new Vector(0.0, 0.0, 0.0);
        };
        Light(Color lightColor, Vector *position) {
            this->setLightColor(lightColor);
            this->setPosition(position);
        };
        Light(unsigned char r, unsigned char g, unsigned char b) {
            this->setLightColor(r, g, b);
        };
        Light(unsigned char r, unsigned char g, unsigned char b, Vector *position) {
            this->setLightColor(r, g, b);
            this->setPosition(position);
        };
        //Setters and getters
        void setLightColor(Color lightColor) {
            this->lightColor = lightColor;
        };
        void setLightColor(unsigned char r, unsigned char g, unsigned char b) {
            lightColor = Color(r, g, b);
        };
        void setPosition(Vector *position) {
            this->position = position;
        };
        void setPosition(double x, double y, double z) {
            this->position = new Vector(x, y, z);
        }
        Vector *getPosition() {
            return position;
        }
        Color getLightColor() {
            return lightColor;
        }
        //Operators
        Light operator+(const Light &secondLight) {
            Color currentLightColor = lightColor;
            Color secondLightColor = secondLight.lightColor;
            Light result = Light();
            result.setLightColor(currentLightColor + secondLightColor);
            return result;
        }
        Light operator*(const double &attenuationFactor) {
            Color currentLightColor = lightColor;
            Light result = Light();
            result.setLightColor(currentLightColor * attenuationFactor);
            return result;
        }
        //Operations (for pointers)
        virtual Light *sum(Light *secondLight) {
            Color currentLightColor = this->getLightColor();
            Color secondLightColor = secondLight->getLightColor();
            Light *result = new  Light();
            result->setLightColor(currentLightColor + secondLightColor);
            return result;
        }
        virtual Light *multiply(double attenuationFactor) {
            Color currentLightColor = this->getLightColor();
            Light *result = new Light();
            result->setLightColor(currentLightColor * attenuationFactor);
            return result;
        }
        //Utils
        void printLightColor() {
            lightColor.printColors();
        };
        void printLightPosition() {
            position->printVector();
        };
        virtual void printLightData(string lightIdentifier) {
            cout << "Light [" << lightIdentifier << "] data:" << endl; 
            cout << "\tLight color = ";
            printLightColor();
            cout << "\tLight position = ";
            printLightPosition();
        }
        virtual void printLightData() {
            printLightData("");
        }



};

#endif