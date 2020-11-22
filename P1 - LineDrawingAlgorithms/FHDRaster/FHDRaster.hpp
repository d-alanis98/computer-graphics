#ifndef FHD_RASTER_H
#define FHD_RASTER_H

//Raster dimensions
#define RASTER_WIDTH    1920
#define RASTER_HEIGHT   1080
#define PRIMARY_COLORS  3


class FHDRaster {
    private:
        unsigned char data[RASTER_WIDTH][RASTER_HEIGHT][PRIMARY_COLORS];
    public:
        FHDRaster(void);
        void setPixel(
            unsigned int, 
            unsigned int, 
            unsigned char, 
            unsigned char, 
            unsigned char
        );
        void write(void);
        //Virtual method, to be implemented in other classes
        virtual void drawLine(
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned int, 
            unsigned char,
            unsigned char,
            unsigned char
        ) = 0;
};

#endif