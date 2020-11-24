#include <iostream>
#include <string>
#include "VLFReader.hpp"

using namespace std;

int main(int argc, char **argv) {
    string vlfPath = argv[1];
    VLFReader *reader = new VLFReader();
        //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFile(vlfPath) == -1) {
        cout << "[ERROR]: There was an error trying to obtain the data, aborting." << endl;
        exit(1);
    }
    //We set the object dimensions in state
    reader->calculateObjectDimensions();
    //Printing the obtained data
    //Elements 
    cout << "Number of vertices = " << reader->getListOfVertices().size() << endl;
    cout << "Number of edges = " << reader->getListOfEdges().size() << endl;
    cout << "Number of faces = " << reader->getListOfFaces().size() << endl;
    //Maximum and minimum points
    cout << "Max point in X = " << reader->getMaximumPointInX() << endl;
    cout << "Min point in X = " << reader->getMinimumPointInX() << endl;
    cout << "Max point in Y = " << reader->getMaximumPointInY() << endl;
    cout << "Min point in Y = " << reader->getMinimumPointInY() << endl;
    cout << "Max point in Z = " << reader->getMaximumPointInZ() << endl;
    cout << "Min point in Z = " << reader->getMinimumPointInZ() << endl;
    //Dimensions
    cout << "Width = " << reader->getObjectWidth() << endl;
    cout << "Height = " << reader->getObjectHeight() << endl;
    cout << "Depth = " << reader->getObjectDepth() << endl;
}