#ifndef CAMERA_H
#define CAMERA_H

#include "../Vector/Vector.hpp"

#define DEFAULT_FOCAL_LENGTH 1000.0

class Camera {
    private:
        //Camera position
        Vector *position;
        //Focal length
        double focalLength;
    public:
        Camera() {
            position = new Vector(0.0, 0.0, 0.0);
            focalLength = DEFAULT_FOCAL_LENGTH;
        };
        Camera(Vector *position, double focalLength) {
            setPosition(position);
            setFocalLength(focalLength);
        };
        //Setters and getters
        void setPosition(Vector *position) {
            this->position = position;
        };
        void setFocalLength(double focalLength) {
            this->focalLength = focalLength;
        };
        Vector *getPosition() {
            return position;
        };
        double getFocalLength() {
            return focalLength;
        };
};

#endif