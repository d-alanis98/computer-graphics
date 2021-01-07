#include <iostream>
#include "Color.hpp"

using namespace std;

int main() {
    Color color1(255, 0, 122);
    Color color2(133, 0, 200);
    Color color3 = color1 + color2;
    cout << "Color de salida = (" << (unsigned int)color3.getRedColor() << ", " << (unsigned int )color3.getGreenColor() << ", " << (unsigned int)color3.getBlueColor() << ")\n";
    double att = 0.54;
    cout << "Attenuation factor = " << att << endl;
    Color color4 = color2 * att;
    cout << "Output color (color3 * attenuationFactor) = (" << (unsigned int)color4.getRedColor() << ", " << (unsigned int )color4.getGreenColor() << ", " << (unsigned int)color4.getBlueColor() << ")\n";
    return 0;
}