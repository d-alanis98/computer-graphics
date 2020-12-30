#include <iostream>
#include "./Vector.hpp"

using namespace std;

int main() {
    Vector *firstVector = new Vector(3, 6, 1);
    Vector *secondVector = new Vector(-5, -9, 4);
    cout << "First vector = ";
    firstVector->printVector();
    cout << "Second vector = ";
    secondVector->printVector();
    //Operations test
    cout << "Sum = ";
    (firstVector->sum(secondVector))->printVector();
    cout << "Substract = ";
    (firstVector->substract(secondVector))->printVector();
    cout << "Multiplication = ";
    (firstVector->multiply(secondVector))->printVector();
    cout << "Angle between = " << firstVector->getAngleBetween(secondVector) << endl;

    return 0;
}