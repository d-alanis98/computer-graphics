#include<cstring>
#include<iostream>
#include<random>

using namespace std;

class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
    memset(data, 0, 1920*1080*3);  
  }
  void
  setPixel(unsigned int x, unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b) {
      if( x >= 1920 || y >= 1080) {
        return;
      }
      data[x][y][0] = r;
      data[x][y][1] = g;
      data[x][y][2] = b;
  }
  void
  write(void) {
   int x = 0;
   int y = 0;
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      cout<<data[x][y][0];
      cout<<data[x][y][1];
      cout<<data[x][y][2];
     } 
   }
  }
 void drawLine( 
  unsigned int x1, unsigned int y1, 
   unsigned int x2, unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b) {
      /* Line drawing algorithm: Bresenham (middle point) */
     
      //    y = m*x + b    line eq. -> DDA -> Bresenham 

      // Bresenham: integer operations
      //  observation: the decision is binary
      /// decision is made using the distance between:
      ///     next pixel and the middle point.
      ////   two distances: d1 and d2
      //    d1 from the upper option and middle point
      //    d2 from the lower option and middle point.
      // d2 == d1?   choose the lower, deltaY = 0
      // d2  > d1     choose the upper, 
      // d2  < d1     choose the lower.
      //  (d1 - d2) >= 0, lower option
      //  (d1 - d2) < 0, upper option
      //  just need to check the sign of (d1-d2)
      //  using 'improvements' he reach:  C*(d1-d2)
      //     ->>>  result is:   just integer operation, and does not 
      //                        change the sign. 

      double m = (double)(y2-y1)/(double)(x2-x1); //slope
      double be = (double)y1 - (m*x1) ;
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;  /// change 2* using bit operation.
      int updateUp    = 2*dy;          // -
      int updateRight = 2*dy-2*dx;     // +

 // (0,0) -> (1000,  500) 
 // dx = 1000,   dy = 500
 // Up = 1000 - 2000 = -1000 (-)
 // Ri =             =  1000 (+)

      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);    //            ***  
                                    ///        ***
      y = m*x1 + be;                ///y1-> ***
      for( x = x1 + 1 ; x < x2 ; x++ ) {   // deltaX = 1
                                    // deltaY = 0 or 1
        /// p = 0
        if( p < 0 ) { // < decision parameter
          y++;
          p += updateUp;    // < update
        } else {
          p += updateRight; // < update
        }   // p = -++-++---+++-+++---  /// <<< goal
            // p = +++++++++++++++++++  /// <<< wrong
        setPixel(x, y, r, g, b); /// raster space array[0][0];
                                 /// image space: -y
      } 
   }
};

/* testing */
int main(void) {
 FHDRaster * raster = new FHDRaster();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;

 raster->drawLine(0,0, 100, 100, 255, 255, 255);

 raster->write();

 return 0;
}