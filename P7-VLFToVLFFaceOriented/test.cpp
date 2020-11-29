#include <iostream>
#include <string>
#include "VLFToVLFFaceOriented.hpp"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "Usage mode: ./test pathToVLFFile" << endl;
        exit(1);
    }

    string pathToFile = argv[1];
    //We create a new VLFToVLFFaceOriented instance
    VLFToVLFFaceOriented *reader = new VLFToVLFFaceOriented();
    reader->setInitialDataFromFile(pathToFile);
    
    cout << "Number of vertices = " << reader->listOfVertices.size() << endl;
    cout << "Number of edges = " << reader->listOfEdges.size() << endl;
    cout << "Number of faces = " << reader->listOfFaces.size() << endl;
    return 0;
}