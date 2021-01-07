#include <iostream>
#include "DirectedLight.hpp"

using namespace std;

int main() {
    DirectedLight *light1 = new DirectedLight();
    light1->setAttenuationModelCoefficients(0.03, 0.2, 1.0);
    light1->setLightColor(120, 120, 120);
    cout << "Light intensity at 0u of distance = " << light1->getLightIntensity(0.0) << endl;
    cout << "Light intensity at 1u of distance = " << light1->getLightIntensity(1.0) << endl;
    cout << "Light intensity at 10u of distance = " << light1->getLightIntensity(10.0) << endl;
    cout << "Light intensity at 100u of distance = " << light1->getLightIntensity(100.0) << endl;
    cout << "Light intensity at 1000u of distance = " << light1->getLightIntensity(1000.0) << endl;
    cout << "Light intensity at 10000u of distance = " << light1->getLightIntensity(10000.0) << endl;
    //Light color
    cout << "\n\nOriginal light color: ";
    light1->printLightColor();
    cout << "Light color at 1u of distance: ";
    Light *light2 = light1->multiply(light1->getLightIntensity(1.0));
    light2->printLightColor();
    cout << "Light color at 10u of distance: ";
    Light *light3 = light1->multiply(light1->getLightIntensity(10.0));
    light3->printLightColor();
    return 0;
}