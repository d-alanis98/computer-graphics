#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
    private:
        double x;
        double y;
        double z;
    private:
        Vertex();
        Vertex(double, double, double);
        double getX();
        double getY();
        double getZ();
        void setCoordinates(double, double, double);
};


#endif