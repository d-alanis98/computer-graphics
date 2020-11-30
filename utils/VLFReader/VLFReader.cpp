#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "VLFReader.hpp"
#include "../Vertex/Vertex.hpp"
#include "../Edge/Edge.hpp"
#include "../Face/Face.hpp"
#include "../Utils/Utils.hpp"

using namespace std;


int VLFReader::getDataFromFileWithKeys(string &filePath) {
    return getDataFromFile(filePath, true);
}

//To read the VLF file without preserving the keys (vertex or edge key), but the full instance
int VLFReader::getDataFromFile(string &filePath) {
    return getDataFromFile(filePath, false);
}

int VLFReader::getDataFromFile(string &filePath, bool preserveKeys) {
    unsigned int totalVertices;
    unsigned int totalEdges;
    unsigned int totalFaces;
    ifstream binaryFile(filePath, ios::out|ios::binary);
    //Header: vertices, edges, faces (without separator, it is in binary form)
    binaryFile.read(reinterpret_cast<char*>(&totalVertices), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalEdges), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalFaces), sizeof(unsigned int));
    readListOfVertices(&binaryFile, totalVertices);
    readListOfEdges(&binaryFile, totalEdges, preserveKeys);
    readListOfFaces(&binaryFile, totalFaces, preserveKeys);
    binaryFile.close();
    return 0;
}

void VLFReader::addVertexToTheList(Vertex *vertexToAdd) {
    unsigned int verticesCount = listOfVertices.size() + 1;
    listOfVertices.insert(pair<unsigned int, Vertex*>(verticesCount, vertexToAdd));
}

void VLFReader::addEdgeToTheList(Edge *edgeToAdd) {
    unsigned int edgesCount = listOfEdges.size() + 1;
    listOfEdges.insert(pair<unsigned int, Edge*>(edgesCount, edgeToAdd));
}

void VLFReader::addFaceToTheList(Face *faceToAdd) {
    unsigned int facesCount = listOfFaces.size() + 1;
    listOfFaces.insert(pair<unsigned int, Face*>(facesCount, faceToAdd));
}

void VLFReader::readListOfVertices(ifstream *binaryFile, unsigned int totalVertices) {
    for(int i = 1; i <= totalVertices; i++) {
        double x, y, z;
        binaryFile->read(reinterpret_cast<char*>(&x), sizeof(double));
        binaryFile->read(reinterpret_cast<char*>(&y), sizeof(double));
        binaryFile->read(reinterpret_cast<char*>(&z), sizeof(double));
        //We create a vertex
        Vertex *vertexToAdd = new Vertex(x, y, z);
        addVertexToTheList(vertexToAdd);
    }
} 

void VLFReader::readListOfEdges(ifstream *binaryFile, unsigned int totalEdges, bool preserveKeys = false) {
    for(int i = 1; i <= totalEdges; i++) {
        unsigned int firstVertex, secondVertex;
        binaryFile->read(reinterpret_cast<char*>(&firstVertex), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&secondVertex), sizeof(unsigned int));
        //We create the edge to add
        Edge *edgeToAdd = new Edge(listOfVertices[firstVertex], listOfVertices[secondVertex]);
        //An instance with the vertices keys instead of the full object's data
        Edge *edgeWithVerticesKey = new Edge(firstVertex, secondVertex);
        //We define the edge to add, the full one or the one with just the keys, based on the preserveKeys value
        if(!preserveKeys)
            addEdgeToTheList(edgeToAdd);
        else addEdgeToTheList(edgeWithVerticesKey);
    }
} 

void VLFReader::readListOfFaces(ifstream *binaryFile, unsigned int totalFaces, bool preserveKeys = false) {
    for(int i = 1; i <= totalFaces; i++) {
        unsigned int firstEdgeKey, secondEdgeKey, thirdEdgeKey;
        vector<Edge*> faceEdges;
        //We get the edges keys
        binaryFile->read(reinterpret_cast<char*>(&firstEdgeKey), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&secondEdgeKey), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&thirdEdgeKey), sizeof(unsigned int));
        //We get the full edges (with all properties, not just the vertexKey, but the actual vertex reference)
        faceEdges.push_back(listOfEdges[firstEdgeKey]);
        faceEdges.push_back(listOfEdges[secondEdgeKey]);
        faceEdges.push_back(listOfEdges[thirdEdgeKey]);
        //We create the face to add
        Face *faceToAdd = new Face(faceEdges);
        //An instance with the edges keys instead of the full object's data
        Face *faceWithEdgesKey = new Face(firstEdgeKey, secondEdgeKey, thirdEdgeKey);
        //We define the edge to add, the full one or the one with just the keys, based on the preserveKeys value
        if(!preserveKeys)
            addFaceToTheList(faceToAdd);
        else addFaceToTheList(faceWithEdgesKey);
    }
} 
