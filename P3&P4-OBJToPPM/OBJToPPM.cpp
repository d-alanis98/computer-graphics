#include <iostream>
#include <string>
#include <map>
#include "../P2-ReadOBJ/OBJReader.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Transformations/Transformations.hpp"
#include "../P1-LineDrawingAlgorithms/BresenhamAlgorithm/BresenhamAlgorithm.hpp"


using namespace std;

int main(int argc, char **argv) {
    unsigned char r = 255, g = 255, b = 255;
    if(argc != 2) {
        cout << "Usage: ./test pathToOBJFile" << endl;
        exit(1);
    }
    //We create an OBJ reader and start getting the data from the file (getting the filePath from arguments)
    string filePath = argv[1];
    OBJReader *reader = new OBJReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFile(filePath) == -1) {
        cout << "[ERROR]: There was an error trying to obtain the data, aborting." << endl;
        exit(1);
    }
    //We set the object dimensions in state
    reader->calculateObjectDimensions();
    //Relevant data
    double pointToTranslateInX = -1 * reader->getMinimumPointInX();
    double pointToTranslateInY = -1 * reader->getMinimumPointInY();
    double pointToTranslateInZ = -1 * reader->getMinimumPointInZ();
    map<unsigned int, Edge*> listOfEdges = reader->getListOfEdges();

    BresenhamAlgorithm *raster = new BresenhamAlgorithm();

    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        Edge *currentEdge = it->second;
        //First vertex
        double firstVertexX = currentEdge->getFirstVertex()->getX();
        double firstVertexY = currentEdge->getFirstVertex()->getY();
        double firstVertexZ = currentEdge->getFirstVertex()->getZ();
        Transformations *firstVertexTransformation = new Transformations();
        firstVertexTransformation->setInitialValues(firstVertexX, firstVertexY, firstVertexZ);
        firstVertexTransformation->scale(4, 4, 4);
        firstVertexTransformation->translateTo(80, 80, 80);
        //firstVertexTransformation->rotateX(90);
        firstVertexTransformation->makeProjection(500);
        
        unsigned int x1 = firstVertexTransformation->getX();
        unsigned int y1 = firstVertexTransformation->getY();
        //Second vertex
        double secondVertexX = currentEdge->getSecondVertex()->getX();
        double secondVertexY = currentEdge->getSecondVertex()->getY();
        double secondVertexZ = currentEdge->getSecondVertex()->getZ();
        Transformations *secondVertexTransformation = new Transformations();
        secondVertexTransformation->setInitialValues(secondVertexX, secondVertexY, secondVertexZ);
        secondVertexTransformation->scale(4, 4, 4);
        secondVertexTransformation->translateTo(80, 80, 80);
        //secondVertexTransformation->rotateX(90);
        secondVertexTransformation->makeProjection(500);
        unsigned int x2 = secondVertexTransformation->getX();
        unsigned int y2 = secondVertexTransformation->getY();
        //We draw the line (the edge)
        raster->drawLine(x1, y1, x2, y2, r, g, b);
    }
    raster->write();
    return 0;
}