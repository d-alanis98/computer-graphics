#ifndef DIRECTED_LIGHT_H
#define DIRECTED_LIGHT_H

#include <iostream>
#include "../Light.hpp"
#include "../../Color/Color.hpp"
#include "../../Vector/Vector.hpp"

#define DEFAULT_A 0.03
#define DEFAULT_B 0.2
#define DEFAULT_C 1.0

using namespace std;

class DirectedLight: public Light {
    private:
        //Attenuation model coefficients
        double a, b, c;
    public:
        //Constructors
        DirectedLight():
            Light() { 
            a = DEFAULT_A;
            b = DEFAULT_B;
            c = DEFAULT_C;
        };
        DirectedLight(Color lightColor, Vector *position, double a, double b, double c):
            Light(lightColor, position) {
                this->a = a;
                this->b = b;
                this->c = c;
        };
        //Setters and getters
        void setAttenuationModelCoefficients(double a, double b, double c) {
            this->a = a;
            this->b = b;
            this->c = c;
        };
        //Attenuation
        double getLightIntensity(double distance) {
            return 1.0 / (double) (a * distance * distance + b * distance + c);
        }
};

#endif