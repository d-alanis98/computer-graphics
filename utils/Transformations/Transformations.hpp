#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "../Matrix/Matrix.hpp"

class Transformations {
    private:
        double values[4];
        unsigned int x;
        unsigned int y;
    public:
        Transformations();
        //Getters and setters
        unsigned int getX();
        unsigned int getY();
        void setInitialValues(double, double, double);
        Matrix<double> getCoordinatesMatrix();
        //Tranformations
        //Scale
        void scale(double, double, double); 
        //Rotation
        void rotateX(double);
        void rotateY(double);
        void rotateZ(double);
        //Translation
        void translateTo(double, double, double);
        //Projection
        void makeProjection(double);
};

#endif