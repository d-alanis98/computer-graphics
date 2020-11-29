#include <iostream>
#include <string>
#include "../utils/VLFReader/VLFReader.hpp"
#include "VLFToVLFFaceOriented.hpp"

using namespace std;


VLFToVLFFaceOriented::VLFToVLFFaceOriented() { };

void VLFToVLFFaceOriented::setInitialDataFromFile(string filePath) {
    //We create an VLFReader instance
    VLFReader *reader = new VLFReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFile(filePath) == -1)
        exit(1);
    //We set the list of 
    listOfVertices = reader->getListOfVertices();
    listOfEdges = reader->getListOfEdges();
    listOfFaces = reader->getListOfFaces();
}