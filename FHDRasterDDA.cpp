#include <cstring>
#include <iostream>
#include <random>

using namespace std;

class FHDRaster {
    unsigned char data[1920][1080][3];

public:
    FHDRaster(void) {
        memset(data, 0, 1920 * 1080 * 3);
    }
    void setPixel(
        unsigned int x, 
        unsigned int y,
        unsigned char r,
        unsigned char g,
        unsigned char b
    ) {
        if(x >= 1920 || y >= 1080) 
            return;
        
        data[x][y][0] = r;
        data[x][y][1] = g;
        data[x][y][2] = b;
    }


    void write(void) {
        int x = 0;
        int y = 0;
        //PPM Header
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
        unsigned int x1, 
        unsigned int y1,
        unsigned int x2, 
        unsigned int y2,
        unsigned char r,
        unsigned char g,
        unsigned char b
    ) {

        double m = (double)(y2 - y1) / (double)(x2 - x1); //slope
        double be = (double)y1 - (m * x1);
        unsigned int x = 0;
        unsigned int y = 0;

        // iteration:    x1 < x2
        setPixel(x1, y1, r, g, b);
        setPixel(x2, y2, r, g, b);

        //Starting value
        y = m * x1 + be;

        for (x = x1 + 1; x < x2; x++) {
            setPixel(x, y, r, g, b);

            y = y + m; 
        }
    }
};


int main(int argc, char **argv) {
    //Raster instance
    FHDRaster *raster = new FHDRaster();

    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;

    //Arguments validation
    if(!(argc == 5))
        exit(1);

    //Points
    int x1 = atoi(argv[1]);
    int y1 = atoi(argv[2]);
    int x2 = atoi(argv[3]);
    int y2 = atoi(argv[4]);

    raster->drawLine(x1, y1, x2, y2, r, g, b);

    raster->write();

    return 0;
}