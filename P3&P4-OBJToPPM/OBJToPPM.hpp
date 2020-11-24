#ifndef OBJ_TO_PPM_H
#define OBJ_TO_PPM_H

#include <iostream>
#include <map>
#include "../utils/Edge/Edge.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"

using namespace std;

class OBJToPPM {
    private:
        double modelWidth, modelHeight;
        double minimumPointInX, minimumPointInY;
        //Transformations
        double optimalScale, pointToTranslateInX, pointToTranslateInY;
        //List of edges
        map<unsigned int, Edge*> listOfEdges;
        //The raster
        BresenhamAlgorithm *raster;
    public:
        OBJToPPM();
        void setDataFromFile(string);
        void drawOBJToRaster();
        double getOptimalScale(double, double);
        double getScaleToApplyInX();
        double getScaleToApplyInY();
        double getTranslationPointInX();
        double getTranslationPointInY();
        void applyTransformationsToVertex(Vertex *, unsigned int *, unsigned int *);
        void setOptimalTransformationParameters();
};


#endif