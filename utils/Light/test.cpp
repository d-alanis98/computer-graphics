#include <iostream>
#include "Light.hpp"

using namespace std;

int main() {
    Light light1;
    light1.setLightColor(34, 26, 35);
    Light light2;
    light2.setLightColor(200, 240, 120);
    Light light3 = light1 + light2;
    cout << "Light colors sum: ";
    light3.printLightColor();
    Light attenuatedLight = light3 * 0.4;
    cout << "Attenuated light color: ";
    attenuatedLight.printLightColor();
    //Pointers
    Light *light4 = new Light();
    light4->setLightColor(120, 0, 10);
    Light *light5 = new Light();
    light5->setLightColor(135, 255, 149);
    Light *light6 = light4->sum(light5);
    cout << "Pointer light colors sum: ";
    light6->printLightColor();
    Light *attenuatedPointerLight = light6->multiply(0.05);
    cout << "Attenuated light color: ";
    attenuatedPointerLight->printLightColor();

}