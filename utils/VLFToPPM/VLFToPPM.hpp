#ifndef VLF_TO_PPM_H
#define VLF_TO_PPM_H

#include <iostream>
#include <map>
#include <set>
#include "../Edge/Edge.hpp"
#include "../Vertex/Vertex.hpp"
#include "../Vector/Vector.hpp"
#include "../Face/Face.hpp"
#include "../PixelWithData/PixelWithData.hpp"
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
        //List of the raw vertices and the transformed vertices (the ones that fit in the raster)
        map<unsigned int, Vertex*> listOfVertices, listOfTransformedVertices;
        //List of faces and the list of faces
        map<unsigned int, Face*> listOfFaces;
        //The raster
        BresenhamAlgorithm *raster;
        //The pixels to draw, it is a set because we don't want repeated values
        set<Pixel> pixelsToDraw;
        //The pixels to draw with data (such as color, raster coordinates, 3D space coordinates)
        vector<PixelWithData *> pixelsWithData;
    public:
        VLFToPPM();
        //Data exctraction from file
        void setDataFromFile(string);
        void setOnlyTheEdgesToShow();
        void setOnlyTheFacesToShow(Vector *);
        //Transformation of the vertices to fit the raster
        double getOptimalScale(double, double);
        void setDegreesToRotate(double);
        double getScaleToApplyInX();
        double getScaleToApplyInY();
        double getTranslationPointInX();
        double getTranslationPointInY();
        void applyTransformationsToVertex(Vertex *, unsigned int *, unsigned int *);
        void applyTransformationsToAllVertices();
        void setOptimalTransformationParameters();
        //Setting the raster data and/or storing the list of pixels locally
        void setPixelsToDraw();
        void setPixelsToDraw(bool);
        void addPixelsToDraw(set<Pixel>);
        void setTotalPixelsToDraw(); 
        void setPixelsWithDataToDraw();
        void addPixelsWithDataToDraw(vector<PixelWithData *>);
        //Drawing to the raster
        void drawVLFToRaster();
        void drawVLFToRasterWithZBuffer();
        //Getters for the lists
        map<unsigned int, Vertex*> getListOfVertices();
        map<unsigned int, Edge*> getListOfEdges();
        map<unsigned int, Face*> getListOfFaces();
        map<unsigned int, Vertex*> getListOfTransformedVertices();
        //Getter for the raster instance
        BresenhamAlgorithm *getRaster();
        //Getter for the list of pixels to draw
        set<Pixel> getPixelsToDraw();
        vector<PixelWithData *> getPixelsWithData(); 
        //Utils
        Vector *getFaceNormal(Face *);
};


#endif