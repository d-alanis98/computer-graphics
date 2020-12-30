#include <iostream>
#include <string>
#include <map>

#include "VLFToPPM.hpp"
#include "../VLFReader/VLFReader.hpp"
#include "../Edge/Edge.hpp"
#include "../Vertex/Vertex.hpp"
#include "../Vector/Vector.hpp"
#include "../Transformations/Transformations.hpp"
#include "../../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"

#define PADDING       50
#define RASTER_WIDTH  1920
#define RASTER_HEIGHT 1080

using namespace std;


VLFToPPM::VLFToPPM() {
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

void VLFToPPM::setDataFromFile(string filePath) {
    //We create an VLFReader instance
    VLFReader *reader = new VLFReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFileWithKeys(filePath) == -1)
        exit(1);
    //We set the object dimensions in state
    reader->calculateObjectDimensionsOfListsWithKeys();
    //We set the relevant data obtained previously in the state
    modelWidth = reader->getObjectWidth();
    modelHeight = reader->getObjectHeight();
    minimumPointInX = reader->getMinimumPointInX();
    minimumPointInY = reader->getMinimumPointInY();
    //We set the list of 
    listOfVertices = reader->getListOfVertices();
    listOfEdges = reader->getListOfEdges();
    listOfFaces = reader->getListOfFaces();
    //We set the optimal transformation parameters with the obtained data
    setOptimalTransformationParameters();
    
    return;
}

Vector *VLFToPPM::getFaceNormal(Face *currentFace) {
    //We get the face's edges
    Edge *firstEdge = listOfEdges[currentFace->getFirstEdgeKey()];
    Edge *secondEdge = listOfEdges[currentFace->getSecondEdgeKey()];
    Edge *thirdEdge = listOfEdges[currentFace->getThirdEdgeKey()];
    //We get the face vertices
    Vertex *firstVertex = listOfVertices[firstEdge->getFirstVertexKey()];
    Vertex *secondVertex = listOfVertices[secondEdge->getFirstVertexKey()];
    Vertex *thirdVertex = listOfVertices[thirdEdge->getFirstVertexKey()];
    //We operate with vectors
    Vector *v1 = new Vector(firstVertex->getX(), firstVertex->getY(), firstVertex->getZ());
    Vector *v2 = new Vector(secondVertex->getX(), secondVertex->getY(), secondVertex->getZ());
    Vector *v3 = new Vector(thirdVertex->getX(), thirdVertex->getY(), thirdVertex->getZ());
    //We create new verteices (now representing vectors)
    Vector *e1 = v1->substract(v2);
    Vector *e2 = v2->substract(v3);
    //We make the cross product
    Vector *crossProductResult = e1->crossProduct(e2);
    return crossProductResult->normalize();
}

void VLFToPPM::setOnlyTheFacesToShow(Vector *cameraVector) {
    map<unsigned int, Face*> listOfFacesToShow;
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        unsigned int faceKey = it->first;
        Face *currentFace = it->second;
        //We get the normal and the angle between the face normal and the camera
        Vector *faceNormal = getFaceNormal(currentFace);
        double angle = faceNormal->getAngleBetween(cameraVector);
        //We are only going to show the faces whose angle between their normal and the camera vector is bigger than 90° and smaller than 270°
        if(angle < 90 || angle > 270)
            continue;
        listOfFacesToShow.insert(pair<unsigned int, Face *>(faceKey, currentFace));
    } 
    //We set the new faces to show
    this->listOfFaces = listOfFacesToShow;
    this->setOnlyTheEdgesToShow();
}

void VLFToPPM::setOnlyTheEdgesToShow() {
    map<unsigned int, Edge*> listOfEdgesToShow;
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        Face *currentFace = it->second;
        //Edges data
        unsigned int firstEdgeKey = currentFace->getFirstEdgeKey();
        unsigned int secondEdgeKey = currentFace->getSecondEdgeKey();
        unsigned int thirdEdgeKey = currentFace->getThirdEdgeKey();
        Edge *firstEdge = listOfEdges[firstEdgeKey];
        Edge *secondEdge = listOfEdges[secondEdgeKey];
        Edge *thirdEdge = listOfEdges[thirdEdgeKey];
        //We insert the edges in the new list
        listOfEdgesToShow.insert(pair<unsigned int, Edge*>(firstEdgeKey, firstEdge));
        listOfEdgesToShow.insert(pair<unsigned int, Edge*>(secondEdgeKey, secondEdge));
        listOfEdgesToShow.insert(pair<unsigned int, Edge*>(thirdEdgeKey, thirdEdge));
    }
    //We set the edges to show
    this->listOfEdges = listOfEdgesToShow;
}


void VLFToPPM::setOptimalTransformationParameters() {
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


void VLFToPPM::setPixelsToDraw() {
    //Only sets the pixels in the raster's local state, we don't want to keep them in the local list
    //It makes the process a little bit faster
    setPixelsToDraw(false);
}

void VLFToPPM::setPixelsToDraw(bool keepTrackInState) {
    unsigned char r = 255, g = 255, b = 255;
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        unsigned int x1, y1, x2, y2;
        //We get the current edge from the iterator
        Edge *currentEdge = it->second;
        //We get the vertices
        Vertex *firstVertex = listOfVertices[currentEdge->getFirstVertexKey()];
        Vertex *secondVertex = listOfVertices[currentEdge->getSecondVertexKey()];
        //And apply the transformations to them
        applyTransformationsToVertex(firstVertex, &x1, &y1);
        applyTransformationsToVertex(secondVertex, &x2, &y2);
        //Finally, we set the pixels to draw
        raster->drawLine(x1, y1, x2, y2, r, g, b);
        //And, if specified, we add those pixels to the state (because the other ones lives in the raster instance and they are generated for every line, so we need a global list of all pixels) 
        if(keepTrackInState)
            addPixelsToDraw(raster->getPixelsToDraw());
    }
}

void VLFToPPM::setTotalPixelsToDraw() {
    //In this case, we want to create the global set of pixels (all the pixels that are required to recreate the figure in the raster, for algorithms like ScanLine or Zbuffer)
    setPixelsToDraw(true);
}

void VLFToPPM::addPixelsToDraw(set<Pixel> edgePixels) {
    for(Pixel pix : edgePixels)
        pixelsToDraw.insert(pix);
}

void VLFToPPM::drawVLFToRaster() {
    setPixelsToDraw();
    raster->write();
}

void VLFToPPM::applyTransformationsToAllVertices() {
    unsigned int transformedVerticesCount = 1;
    for(map<unsigned int, Vertex*>::iterator it = listOfVertices.begin(); it != listOfVertices.end(); it++) {
        Vertex *transformedVertex = it->second;
        applyTransformationsToVertex(transformedVertex, 0, 0);
        listOfTransformedVertices.insert(pair<unsigned int, Vertex*>(transformedVerticesCount, transformedVertex));
        transformedVerticesCount++;
    }
}

void VLFToPPM::applyTransformationsToVertex(Vertex *vertexToTransform, unsigned int *resultX = 0, unsigned int *resultY = 0) {
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
    //We make the projection
    vertexTransformation->makeProjection(500);
    //We get the final X and Y (the result of the transformation to fit in the raster)
    double x = vertexTransformation->getX();
    double y = vertexTransformation->getY();
    //If the pointer to the result integers is supplied, we set the values in resultX and resultY
    if(resultX != 0 && resultY != 0) {
        *resultX = x;
        *resultY = y;
    } else { //Otherwise, we set them in the vertex directly, via its setCoordinates method
        vertexToTransform->setCoordinates(x, y, 0);
    }
    return;
}

double VLFToPPM::getScaleToApplyInX() {
    return (double)(raster->rasterWidth - PADDING) / (double) modelWidth;
}

double VLFToPPM::getScaleToApplyInY() {
    return (double)(raster->rasterHeight - PADDING) / (double) modelHeight;
}

double VLFToPPM::getOptimalScale(double scaleInX, double scaleInY) {
    //In this case, the raster dimensions are 1920x1080, so the scale to fit in X will always be larger than the scale to fit the model in Y
    //and we want the highest scale possible, but we need to verify that applying the bigger scale to the Y axis won't cause overflow, in that case
    //we will need to use the scaleInY, to get the complete model in the projection, and not cropped in Y.
    return (scaleInX * modelHeight) <= (raster->rasterHeight - PADDING) ? scaleInX : scaleInY;
}

double VLFToPPM::getTranslationPointInX() {
    return -1 * optimalScale * minimumPointInX;
}

double VLFToPPM::getTranslationPointInY() {
    return -1 * optimalScale * minimumPointInY;
}

void VLFToPPM::setDegreesToRotate(double degreesToRotate) {
    this->degreesToRotate = degreesToRotate;
}

BresenhamAlgorithm *VLFToPPM::getRaster() {
    return raster;
}

set<Pixel> VLFToPPM::getPixelsToDraw() {
    return pixelsToDraw;
}

map<unsigned int, Vertex*> VLFToPPM::getListOfVertices() {
     return listOfVertices;
}

map<unsigned int, Edge*> VLFToPPM::getListOfEdges() {
    return listOfEdges;
}

map<unsigned int, Face*> VLFToPPM::getListOfFaces() {
    return listOfFaces;
}

map<unsigned int, Vertex*> VLFToPPM::getListOfTransformedVertices() {
    return listOfTransformedVertices;
}
