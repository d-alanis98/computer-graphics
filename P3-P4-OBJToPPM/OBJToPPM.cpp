#include <iostream>
#include <string>
#include <map>

#include "OBJToPPM.hpp"
#include "../P2-ReadOBJ/OBJReader.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Transformations/Transformations.hpp"
#include "../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"

#define PADDING       50
#define RASTER_WIDTH  1920
#define RASTER_HEIGHT 1080

using namespace std;


OBJToPPM::OBJToPPM() {
    //Dimensions
    modelWidth = modelHeight = 0;
    minimumPointInX = minimumPointInY = 0;
    //Parameters for transformations
    optimalScale = 1;
    pointToTranslateInX = pointToTranslateInY = 0;
    degreesToRotate = 180;
    //We create an instance of the raster
    raster = new BresenhamAlgorithm();
}

void OBJToPPM::setDataFromFile(string filePath) {
    //We create an OBJReader instance
    OBJReader *reader = new OBJReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFile(filePath) == -1)
        exit(1);
    //We set the object dimensions in state
    reader->calculateObjectDimensions();
    //We set the relevant data obtained previously in the state
    modelWidth = reader->getObjectWidth();
    modelHeight = reader->getObjectHeight();
    minimumPointInX = reader->getMinimumPointInX();
    minimumPointInY = reader->getMinimumPointInY();
    //We set the list of edges
    listOfEdges = reader->getListOfEdges();
    //We set the optimal transformation parameters with the obtained data
    setOptimalTransformationParameters();
    return;
}


void OBJToPPM::setOptimalTransformationParameters() {
    double scaleInX = getScaleToApplyInX();
    double scaleInY = getScaleToApplyInY();
    //We get the global optimal scale (the same will be applied to X and Y to avoid distortion)
    optimalScale = getOptimalScale(scaleInX, scaleInY);
    //Translation
    pointToTranslateInX = getTranslationPointInX();
    pointToTranslateInY = getTranslationPointInY();

    pointToTranslateInX += (raster->rasterWidth - 2 * pointToTranslateInX) / 2;
    pointToTranslateInY += (raster->rasterHeight - 2 * pointToTranslateInY) / 2;
}


void OBJToPPM::drawOBJToRaster() {
    unsigned char r = 255, g = 255, b = 255;
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        unsigned int x1, y1, x2, y2;
        //We get the current edge from the iterator
        Edge *currentEdge = it->second;
        //We get the vertices
        Vertex *firstVertex = currentEdge->getFirstVertex();
        Vertex *secondVertex = currentEdge->getSecondVertex();
        //And apply the transformations to them
        applyTransformationsToVertex(firstVertex, &x1, &y1);
        applyTransformationsToVertex(secondVertex, &x2, &y2);
        //Finally, we draw the edge
        raster->drawLine(x1, y1, x2, y2, r, g, b);
    }
    //We generate the PPM output
    raster->write();
}

void OBJToPPM::applyTransformationsToVertex(Vertex *vertexToTransform, unsigned int *resultX, unsigned int *resultY) {
    //We get the vertex coordinates
    double vertexX = vertexToTransform->getX();
    double vertexY = vertexToTransform->getY();
    double vertexZ = vertexToTransform->getZ();
    //We apply the transformations
    Transformations *vertexTransformation = new Transformations();
    vertexTransformation->setInitialValues(vertexX, vertexY, vertexZ);
    vertexTransformation->scale(optimalScale, optimalScale, optimalScale);
    //To get the model in correct orientation
    vertexTransformation->rotateX(degreesToRotate);
    vertexTransformation->translateTo(pointToTranslateInX, pointToTranslateInY, 0);

    vertexTransformation->makeProjection(500);
    //We set the values in resultX and resultY
    *resultX = vertexTransformation->getX();
    *resultY = vertexTransformation->getY();
    return;
}

double OBJToPPM::getScaleToApplyInX() {
    return (double)(raster->rasterWidth - PADDING) / (double) modelWidth;
}

double OBJToPPM::getScaleToApplyInY() {
    return (double)(raster->rasterHeight - PADDING) / (double) modelHeight;
}

double OBJToPPM::getOptimalScale(double scaleInX, double scaleInY) {
    //In this case, the raster dimensions are 1920x1080, so the scale to fit in X will always be larger than the scale to fit the model in Y
    //and we want the highest scale possible, but we need to verify that applying the bigger scale to the Y axis won't cause overflow, in that case
    //we will need to use the scaleInY, to get the complete model in the projection, and not cropped in Y.
    return (scaleInX * modelHeight) <= (raster->rasterHeight - PADDING) ? scaleInX : scaleInY;
}

double OBJToPPM::getTranslationPointInX() {
    return -1 * optimalScale * minimumPointInX;
}

double OBJToPPM::getTranslationPointInY() {
    return -1 * optimalScale * minimumPointInY;
}

void OBJToPPM::setDegreesToRotate(double degreesToRotate) {
    this->degreesToRotate = degreesToRotate;
}

