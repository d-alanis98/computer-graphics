#ifndef VLF_TO_PPM_H
#define VLF_TO_PPM_H

#include <iostream>
#include <map>
#include "../Edge/Edge.hpp"
#include "../Vertex/Vertex.hpp"
#include "../../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"

using namespace std;

class VLFToPPM {
    private:
        double modelWidth, modelHeight;
        double minimumPointInX, minimumPointInY;
        //Transformations
        double optimalScale, degreesToRotate, pointToTranslateInX, pointToTranslateInY;
        //List of edges
        map<unsigned int, Edge*> listOfEdges;
        //The raster
        BresenhamAlgorithm *raster;
    public:
        VLFToPPM();
        void setDataFromFile(string);
        void drawVLFToRaster();
        double getOptimalScale(double, double);
        void setDegreesToRotate(double);
        double getScaleToApplyInX();
        double getScaleToApplyInY();
        double getTranslationPointInX();
        double getTranslationPointInY();
        void applyTransformationsToVertex(Vertex *, unsigned int *, unsigned int *);
        void setOptimalTransformationParameters();
};


#endif