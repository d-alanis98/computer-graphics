/**
@author Damián Alanís Ramírez
@version 2.1.0
*/

#include <cstring>
#include <iostream>
#include <stdlib.h>


#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
#define abs(x) ((x < 0) ? -1 * x : x)

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
            cout<<"P6\n1920 1080 255\n";
            //Data
            for(y=0;y<1080;y++) {
                for(x=0;x<1920;x++) {
                    cout<<data[x][y][0];
                    cout<<data[x][y][1];
                    cout<<data[x][y][2];
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



int main(int argc, char **argv) {

    //Arguments validation
    if(argc != 5) 
        exit(1);
    

    FHDRaster * raster = new FHDRaster();


    unsigned int x1 = atoi(argv[1]);
    unsigned int y1 = atoi(argv[2]);
    unsigned int x2 = atoi(argv[3]);
    unsigned int y2 = atoi(argv[4]);


        
    raster->drawLine(x1,y1,x2,y2, 255,255,255);
    
    
    raster->write();

    return 0;
}