#include <iostream>
#include <string>
#include <iterator> 
#include <cstdlib>
#include <map>
#include "FileReader.hpp"
#include "../Vertex/Vertex.hpp"
#include "../Edge/Edge.hpp"
#include "../Face/Face.hpp"

using namespace std;



FileReader::FileReader() {
    this->filePath = "";
}

void FileReader::calculateObjectDimensions() {
    //We set the maximum and minimum values in the state
    setMaximumAndMinimumValues();
    //Now we can compute the width, height, and depth of the object
    objectWidth = abs(maximumPointInX - minimumPointInX);
    objectHeight = abs(maximumPointInY - minimumPointInY);
    objectDepth = abs(maximumPointInZ - minimumPointInZ);
}

void FileReader::calculateObjectDimensionsOfListsWithKeys() {
    //We set the maximum and minimum values in the state
    setMaximumAndMinimumValuesOfListsWithKeys();
    //Now we can compute the width, height, and depth of the object
    objectWidth = abs(maximumPointInX - minimumPointInX);
    objectHeight = abs(maximumPointInY - minimumPointInY);
    objectDepth = abs(maximumPointInZ - minimumPointInZ);
}

double FileReader::getMaximumPointInX() {
    return maximumPointInX;
}

double FileReader::getMaximumPointInY() {
    return maximumPointInY;
}

double FileReader::getMaximumPointInZ() {
    return maximumPointInZ;
}

double FileReader::getMinimumPointInX() {
    return minimumPointInX;
}

double FileReader::getMinimumPointInY() {
    return minimumPointInY;
}

double FileReader::getMinimumPointInZ() {
    return minimumPointInZ;
}

double FileReader::getObjectWidth() {
    return objectWidth;
}

double FileReader::getObjectHeight() {
    return objectHeight;
}

double FileReader::getObjectDepth() {
    return objectDepth;
}

//Get maximum points (each method returns an updated maximum one or return the same)
double getMaximumX(Edge *current, double currentMaxValue) {
    double maximumPointInX = currentMaxValue;
    if(current->getFirstVertex()->getX() > maximumPointInX)
        maximumPointInX = current->getFirstVertex()->getX();
    if(current->getSecondVertex()->getX() > maximumPointInX)
        maximumPointInX = current->getSecondVertex()->getX();
    return maximumPointInX;
}

double getMaximumY(Edge *current, double currentMaxValue) {
    double maximumPointInY = currentMaxValue;
    if(current->getFirstVertex()->getY() > maximumPointInY)
        maximumPointInY = current->getFirstVertex()->getY();
    if(current->getSecondVertex()->getY() > maximumPointInY)
        maximumPointInY = current->getSecondVertex()->getY();
    return maximumPointInY;
}

double getMaximumZ(Edge *current, double currentMaxValue) {
    double maximumPointInZ = currentMaxValue;
    if(current->getFirstVertex()->getZ() > maximumPointInZ)
        maximumPointInZ = current->getFirstVertex()->getZ();
    if(current->getSecondVertex()->getZ() > maximumPointInZ)
        maximumPointInZ = current->getSecondVertex()->getZ();
    return maximumPointInZ;
}

//Get minimum points (each method returns an updated minimum one or return the same)
double getMinimumX(Edge *current, double currentMinValue) {
    double minimumPointInX = currentMinValue;
    if(current->getFirstVertex()->getX() < minimumPointInX)
        minimumPointInX = current->getFirstVertex()->getX();
    if(current->getSecondVertex()->getX() < minimumPointInX)
        minimumPointInX = current->getSecondVertex()->getX();
    return minimumPointInX;
}

double getMinimumY(Edge *current, double currentMinValue) {
    double minimumPointInY = currentMinValue;
    if(current->getFirstVertex()->getY() < minimumPointInY)
        minimumPointInY = current->getFirstVertex()->getY();
    if(current->getSecondVertex()->getY() < minimumPointInY)
        minimumPointInY = current->getSecondVertex()->getY();
    return minimumPointInY;
}

double getMinimumZ(Edge *current, double currentMinValue) {
    double minimumPointInZ = currentMinValue;
    if(current->getFirstVertex()->getZ() < minimumPointInZ)
        minimumPointInZ = current->getFirstVertex()->getZ();
    if(current->getSecondVertex()->getZ() < minimumPointInZ)
        minimumPointInZ = current->getSecondVertex()->getZ();
    return minimumPointInZ;
}

void FileReader::setMaximumAndMinimumValues() {
    //Maximum and minimum initial values
    maximumPointInX = minimumPointInX = 0;
    maximumPointInY = minimumPointInY = 0;
    maximumPointInZ = minimumPointInZ = 0;
    //Iteration through the map to get the maximum and minimum in a greedy approach
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        Edge *current = it->second;
        //Maximum points
        maximumPointInX = getMaximumX(current, maximumPointInX);
        maximumPointInY = getMaximumY(current, maximumPointInY);
        maximumPointInZ = getMaximumZ(current, maximumPointInZ);
        //Minimum points
        minimumPointInX = getMinimumX(current, minimumPointInX);
        minimumPointInY = getMinimumY(current, minimumPointInY);
        minimumPointInZ = getMinimumZ(current, minimumPointInZ);
    }
}

void FileReader::setMaximumAndMinimumValuesOfListsWithKeys() {
    //Maximum and minimum initial values
    maximumPointInX = minimumPointInX = 0;
    maximumPointInY = minimumPointInY = 0;
    maximumPointInZ = minimumPointInZ = 0;
    //Iteration through the map to get the maximum and minimum in a greedy approach
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        Edge *current = it->second;
        Edge *currentWithFullVertexData = new Edge(
            listOfVertices[current->getFirstVertexKey()],
            listOfVertices[current->getSecondVertexKey()]
        );
        //Maximum points
        maximumPointInX = getMaximumX(currentWithFullVertexData, maximumPointInX);
        maximumPointInY = getMaximumY(currentWithFullVertexData, maximumPointInY);
        maximumPointInZ = getMaximumZ(currentWithFullVertexData, maximumPointInZ);
        //Minimum points
        minimumPointInX = getMinimumX(currentWithFullVertexData, minimumPointInX);
        minimumPointInY = getMinimumY(currentWithFullVertexData, minimumPointInY);
        minimumPointInZ = getMinimumZ(currentWithFullVertexData, minimumPointInZ);
    }
}



map<unsigned int, Vertex*> FileReader::getListOfVertices() {
    return listOfVertices;
}
        
map<unsigned int, Edge*> FileReader::getListOfEdges() {
    return listOfEdges;
}
        
map<unsigned int, Face*> FileReader::getListOfFaces() {
    return listOfFaces;
}

bool FileReader::isTheSameEdge(Edge *current, Edge *target) {
    bool isTheSame = true;
    //We check the first vertex
    if(target->getFirstVertex()->getX() != current->getFirstVertex()->getX())
        isTheSame = false;
    if(target->getFirstVertex()->getY() != current->getFirstVertex()->getY())
        isTheSame = false;
    if(target->getFirstVertex()->getZ() != current->getFirstVertex()->getZ())
        isTheSame = false;
    //We check the second vertex
    if(target->getSecondVertex()->getX() != current->getSecondVertex()->getX())
        isTheSame = false;
    if(target->getSecondVertex()->getY() != current->getSecondVertex()->getY())
        isTheSame = false;
    if(target->getSecondVertex()->getZ() != current->getSecondVertex()->getZ())
        isTheSame = false;
    return isTheSame;
}

int FileReader::indexOfEdge(Edge *target) {
    int edgeIndex = -1;
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        Edge *current = it->second;
        if(isTheSameEdge(current, target)) {
            edgeIndex = it->first;
            break;
        }
    }
    return edgeIndex;

}


