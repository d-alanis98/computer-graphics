/**
@author Damián Alanís Ramírez
@version 0.1.0
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "Matrix.h"


#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
#define abs(x) ((x < 0) ? -1 * x : x)
#define natural(x) ((x < 0) ? 0 : x)

#define PI 3.14159265

using namespace std;


class FHDRaster {

    unsigned char data[1920][1080][3];
    public:
        FHDRaster(void) {
            memset(data, 0, 1920*1080*3); 
            for(int i = 0; i < 1920; i++)
                for(int j = 0; j < 1080; j++)
                    setPixel(i, j, 120, 120, 120);
        }

        void setPixel(
            unsigned int x, 
            unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b
        ) {
            if( x >= 1920 || y >= 1080)
                return;
            data[x][y][0] = r;
            data[x][y][1] = g;
            data[x][y][2] = b;
        }


        void write(void) {
            int x = 0;
            int y = 0;
            //PPM header
            cout << "P6\n1920 1080 255\n";
            //Data
            for(y = 0; y < 1080; y++) {
                for(x = 0; x < 1920; x++) {
                    cout << data[x][y][0];
                    cout << data[x][y][1];
                    cout << data[x][y][2];
                } 
            }
        }
        void drawLine( 
            unsigned int x, 
            unsigned int y, 
            unsigned int x2, 
            unsigned int y2, 
            unsigned char r,
            unsigned char g,
            unsigned char b
        ) { 
            int width = x2 - x;
            int heigth = y2 - y;
            int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

            /*
                Increments in X axis
                x2 - x < 0 in 5th, 6th, 7th and 8th octant, and x2 - x > 0 in 1st, 2nd, 3rd and 4th octant
                In 5th, 6th, 7th and 8th octant we are going "backwards" in X, thats why dx1 = -1, othwerwise we go forward, if 0 we won't move in X
            */
            dx1 = (width < 0) ? -1 : (width > 0) ? 1 : 0;
            dx2 = (width < 0) ? -1 : (width > 0) ? 1 : 0;
            /*
                Increments in Y axis
                y2 - y < 0 in 1st, 2nd, 7th and 8th octant, and y2 - y > 0 in 3rd, 4th, 5th and 6th octant
                In 1st, 2nd, 7th and 8th octant we are going "backwards" (up) in Y, thats why dy1 = -1, othwerwise we go forward (down), if 0 we won't move in Y
            */
            dy1 = (heigth < 0) ? -1 : (heigth > 0) ? 1 : 0;

            //We start assuming that the longest magnitude is the width (x2 - x) (this will be verified later)
            int longest = abs(width);
            int shortest = abs(heigth);

            //If height > width we "swap" the direction of the drawing, we are going to do increments or decrements in Y while X remains the same
            if(shortest > longest) {
                //We update with the correct value
                longest = abs(heigth);
                shortest = abs(width);
                dx2 = 0;      
                //The same logic as dy1: In 1st, 2nd, 7th and 8th octant we are going "backwards" (up) in Y, thats why dy2 = -1, othwerwise we go forward (down) dy2 = 1, if 0 we won't move in Y
                dy2 = (heigth < 0) ? -1 : (heigth > 0) ? 1 : 0;    
            }
            
            //To get the half of the number but without performing an expensive division and rounding we use bit operations
            int half = longest >> 1;
            bool criterion;

            //We start from 0 (the origin of the octants) to the biggest dimension (width or height)
            for(int i = 0; i <= longest; i++) {
                setPixel(x, y, r, g, b);
                //We sum the shortest dimension value to the half variable
                half += shortest;
                // If the new half is bigger than the longest value, this mean that we have surpased the limit, so we need to move in the required direction (backward or forward in X or Y)
                criterion = half > longest;
                //If the criterion condition is met, we need to perform the movement along the other axis (the one of the shortest dimension) to get the correct line slope in the final image
                if(criterion) {
                    half -= longest;
                    x += dx1;
                    y += dy1;
                } 
                //Otherwise, we move normally over the longest dimension axis without moving up or down in the other axis, i.e we keep in a straight line wether in X or Y
                else {
                    //If the width is the largest dimension, we go backward or forward in X, Y = 0
                    x += dx2;
                    //If the height is the largest dimension we go backward or forward in Y, X = 0
                    y += dy2;
                }
            }
        }
};

class Transformation {
    private:
        double values[4];
        unsigned int x;
        unsigned int y;
    public:
        Transformation() {
            memset(values, 1, 4);
        }

        void setInitialValues(double x, double y, double z) {
            values[0] = x;
            values[1] = y;
            values[2] = z;
            //The value of w, for the homogeneous space
            values[3] = 1.0;
            this->x = (unsigned int) natural(x);
            this->y = (unsigned int) natural(y);
        }

        unsigned int getX() {
            return x;
        }

        unsigned int getY() {
            return y;
        }

        Matrix<double> getCoordinatesMatrix() {
            Matrix<double> coordinatesMatrix(4, 1, 1);
            for(int i = 0; i < 3; i++)
                coordinatesMatrix(i, 0) = values[i];
            coordinatesMatrix(3, 0) = 1;
            return coordinatesMatrix;
        }

        //SCALE
        void scale(double scaleInX = 1, double scaleInY = 1, double scaleInZ = 1) {
            Matrix<double> scaleMatrix(4, 4, 0);
            scaleMatrix(0, 0) = scaleInX;
            scaleMatrix(1, 1) = scaleInY;
            scaleMatrix(2, 2) = scaleInZ;
            scaleMatrix(3, 3) = 1; //w
            Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
            Matrix <double> result = scaleMatrix * coordinatesMatrix;
            for(int i = 0; i < 3; i++)
                this->values[i] = result(i, 0);
        }

        //ROTATION

        void rotateX(double degrees) {
            Matrix<double> rotationMatrix(4, 4, 0);
            rotationMatrix(0, 0) = 1;
            rotationMatrix(1, 1) = cos(degrees * PI / 180);
            rotationMatrix(1, 2) = -1 * sin(degrees * PI / 180);
            rotationMatrix(2, 1) = sin(degrees * PI / 180);
            rotationMatrix(2, 2) = cos(degrees * PI / 180);
            rotationMatrix(3, 3) = 1;
            Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
            Matrix <double> result = rotationMatrix * coordinatesMatrix;
            for(int i = 0; i < 3; i++)
                this->values[i] = result(i, 0);
        }

        void rotateY(double degrees) {
            Matrix<double> rotationMatrix(4, 4, 0);
            rotationMatrix(0, 0) = cos(degrees * PI / 180);
            rotationMatrix(0, 2) = -1 * sin(degrees * PI / 180);
            rotationMatrix(1, 1) = 1;
            rotationMatrix(2, 0) = sin(degrees * PI / 180);
            rotationMatrix(2, 2) = cos(degrees * PI / 180);
            rotationMatrix(3, 3) = 1;
            Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
            Matrix <double> result = rotationMatrix * coordinatesMatrix;
            for(int i = 0; i < 3; i++)
                this->values[i] = (unsigned int) natural(result(i, 0));
        }

        void rotateZ(double degrees) {
            Matrix<double> rotationMatrix(4, 4, 0);
            rotationMatrix(0, 0) = cos(degrees * PI / 180);
            rotationMatrix(0, 1) = -1 * sin(degrees * PI / 180);
            rotationMatrix(1, 0) = sin(degrees * PI / 180);
            rotationMatrix(1, 1) = cos(degrees * PI / 180);
            rotationMatrix(2, 2) = 1;
            rotationMatrix(3, 3) = 1;
            Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
            Matrix <double> result = rotationMatrix * coordinatesMatrix;
            for(int i = 0; i < 3; i++)
                this->values[i] = result(i, 0);
        }

        //TRANSLATION
        void translateTo(double tx, double ty, double tz) {
            Matrix<double> translationMatrix(4, 4, 0);
            //We fill the diagonal with 1's
            for(int i = 0; i < 4; i++)
                translationMatrix(i, i) = 1;
            translationMatrix(0, 3) = tx;
            translationMatrix(1, 3) = ty;
            translationMatrix(2, 3) = tz;
            Matrix <double> coordinatesMatrix = getCoordinatesMatrix();
            Matrix <double> result = translationMatrix * coordinatesMatrix;
            for(int i = 0; i < 3; i++)
                this->values[i] = result(i, 0);
        }

        //PROJECTION
        void makeProjection(double focalLength) {
            Matrix<double> projectionMatrix(4, 4, 0);
            Matrix<double> coordinatesMatrix = getCoordinatesMatrix();
            //We set the projection matrix
            for(int i = 0; i < 3; i++)
                projectionMatrix(i, i) = focalLength;
            projectionMatrix(3, 0) = 1;
            //We make the operation
            Matrix<double> result = projectionMatrix * coordinatesMatrix;
            //We return from the homogeneous space and update the values of (x, y, z , w)
            for(int i = 0; i < 3; i++)
                this->values[i] = result(i, 0) / result(3, 0); //Value / w

            this->x = (unsigned int)values[1];
            this->y = (unsigned int)values[2];
        }

};



vector<string> split(const string &input, char delimiter) {
    vector<string> result;
    stringstream searchString(input);
    string item;

    while(getline(searchString, item, delimiter))
        result.push_back (item);

    return result;
}

int main(int argc, char **argv) {

    //3D Model coordinates
    double x, y, z;
    unsigned int x1, y1, x2, y2;
    bool firstIteration = true;
    if(argc != 2)
        exit(1);
    
    FHDRaster * raster = new FHDRaster();
    string filePath = argv[1], line;
    ifstream objFile(filePath);
    if(!objFile.is_open())
        exit(1);

    while(getline(objFile, line)) {
        //We get the data from the file
        vector<string> coordinates = split(line, ' ');
        //If the current line does not starts with 'v' (for the vertex coordinates), we go to the other line
        if(coordinates[0] != "v")
            continue;
        //We extract the coordinates
        x = stod(coordinates[1]);
        y = stod(coordinates[2]);
        z = stod(coordinates[3]);
        Transformation * transformation = new Transformation();
        transformation->setInitialValues(x, y, z);
        transformation->scale(10, 10, 10);
        transformation->translateTo(50, 50, 50);
        
        transformation->makeProjection(500);
        //transformation->translateTo(500, 500, 500);
        //Line drawing in PPM, in first iteration we set the initial points as the obtained from the files -> transformations
        if(firstIteration) {
            x1 = transformation->getX();
            y1 = transformation->getY();
            firstIteration = false;
            continue;
        }
        //In following iterations, the initial point will be the last of the previous iteration
        x2 = transformation->getX();
        y2 = transformation->getY();
        //We draw the line
        raster->drawLine(x1,y1,x2,y2, 255,255,255);
        //We set the initial points for the upcoming line
        x1 = x2;
        y1 = y2;
        
    }
    
    raster->write();
    objFile.close();
    return 0;
}