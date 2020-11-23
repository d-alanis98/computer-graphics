#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
    private:
        double x;
        double y;
        double z;
    public:
        //Constructors
        Vertex();
        Vertex(double, double, double);
        //Getters
        double getX();
        double getY();
        double getZ();
        //Setter
        void setCoordinates(double, double, double);
};


#endif