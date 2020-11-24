#include <iostream>
#include <fstream>
#include <map>
#include "OBJToVLF.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Face/Face.hpp"
#include "../P2-ReadOBJ/OBJReader.hpp"

using namespace std;



OBJToVLF::OBJToVLF() { };

void OBJToVLF::readOBJFile(string filePath) {
    //We create an OBJReader instance
    OBJReader *reader = new OBJReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFile(filePath) == -1)
        exit(1);
    //We set the list of vertices, edges and faces obtained from the reader
    listOfVertices = reader->getListOfVertices();
    listOfEdges = reader->getListOfEdges();
    listOfFaces = reader->getListOfFaces();
    //At this point we can conform the VLF list of vertices, because we are not going to add new vertices, only edges and faces
    vlfListOfVertices = listOfVertices;
}

void OBJToVLF::printRetrievedDataFromOBJ() {
    cout << "\nTotal vertices in OBJ: " << listOfVertices.size() << endl;
    cout << "Total generated edges in OBJ: " << listOfEdges.size() << endl;
    cout << "Total faces in OBJ: " << listOfFaces.size() << endl;
    cout << "\n*******************************" << endl;
}

void OBJToVLF::createVLFFile(string vlfPath) {
    
    unsigned int totalVertices = vlfListOfVertices.size();
    unsigned int totalEdges = vlfListOfEdges.size();
    unsigned int totalFaces = vlfListOfFaces.size();

    ofstream binaryFile(vlfPath, ios::binary);
    //Header: vertices, edges, faces (without separator, it is in binary form)
    binaryFile.write(reinterpret_cast<char*>(&totalVertices), sizeof(unsigned int));
    binaryFile.write(reinterpret_cast<char*>(&totalEdges), sizeof(unsigned int));
    binaryFile.write(reinterpret_cast<char*>(&totalFaces), sizeof(unsigned int));
    //List of vertices
    writeListOfVertices(&binaryFile);
    binaryFile.close();

}

void OBJToVLF::writeListOfVertices(ofstream *binaryFile) {
    for(int i = 1; i <= vlfListOfVertices.size(); i++) {
        //We get the current vertex and it's coordinates
        Vertex *vertex = vlfListOfVertices[i];
        double x = vertex->getX();
        double y = vertex->getY();
        double z = vertex->getZ();
        //We write the data to the binary file
        binaryFile->write(reinterpret_cast<char*>(&x), sizeof(double));
        binaryFile->write(reinterpret_cast<char*>(&y), sizeof(double));
        binaryFile->write(reinterpret_cast<char*>(&z), sizeof(double));
    }
}

void OBJToVLF::writeListOfEdges(ofstream *binaryFile) {
    for(int i = 1; i <= vlfListOfEdges.size(); i++) {
        //We get the current vertex and it's coordinates
        Edge *edge = vlfListOfEdges[i];
        unsigned int firstVertexKey = edge->getFirstVertexKey();
        unsigned int secondVertexKey = edge->getSecondVertexKey();
        //We write the data to the binary file
        binaryFile->write(reinterpret_cast<char*>(&firstVertexKey), sizeof(unsigned int));
        binaryFile->write(reinterpret_cast<char*>(&secondVertexKey), sizeof(unsigned int));
    }
}

void OBJToVLF::writeListOfFaces(ofstream *binaryFile) {

}

/*
TEMP
*/
void OBJToVLF::readVLFFile(string vlfPath) {
    unsigned int totalVertices;
    unsigned int totalEdges;
    unsigned int totalFaces;
    ifstream binaryFile(vlfPath, ios::out|ios::binary);
    //Header: vertices, edges, faces (without separator, it is in binary form)
    binaryFile.read(reinterpret_cast<char*>(&totalVertices), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalEdges), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalFaces), sizeof(unsigned int));
    cout << "Reading VLF File..." << endl;
    cout << "\n**************************\nVLF file content:\n**************************" << endl;
    cout << "Number of vertices = " << totalVertices << endl;
    cout << "Number of edges = " << totalEdges << endl;
    cout << "Numer of faces = " << totalFaces << endl;
    //List of vertices
    readListOfVertices(&binaryFile, totalVertices);
    binaryFile.close();

}

void  OBJToVLF::readListOfVertices(ifstream *binaryFile, unsigned int totalVertices) {
    cout << "\nVERTICES:" << endl;
    for(int i = 1; i <= totalVertices; i++) {
        double x, y, z;
        binaryFile->read(reinterpret_cast<char*>(&x), sizeof(double));
        binaryFile->read(reinterpret_cast<char*>(&y), sizeof(double));
        binaryFile->read(reinterpret_cast<char*>(&z), sizeof(double));
        cout << "Vertex " << i << " = (" << x << ", " << y << ", " << z << ")\n";
    }
} 

void  OBJToVLF::readListOfEdges(ifstream *binaryFile, unsigned int totalEdges) {
    cout << "\nEDGES:" << endl;
    for(int i = 1; i <= totalEdges; i++) {
        unsigned int firstVertex, secondVertex;
        binaryFile->read(reinterpret_cast<char*>(&firstVertex), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&secondVertex), sizeof(unsigned int));
        cout << "Edge " << i << " = (" << firstVertex << ", " << secondVertex << ")\n";
    }
} 

void  OBJToVLF::readListOfFaces(ifstream *binaryFile, unsigned int totalFaces) {
    cout << "\nFACES:" << endl;
    for(int i = 1; i <= totalFaces; i++) {
        unsigned int firstEdge, secondEdge, thirdEdge;
        binaryFile->read(reinterpret_cast<char*>(&firstEdge), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&secondEdge), sizeof(unsigned int));
        binaryFile->read(reinterpret_cast<char*>(&thirdEdge), sizeof(unsigned int));
        cout << "Edge " << i << " = (" << firstEdge << ", " << secondEdge << ", " << thirdEdge << ")\n";
    }
} 

/* END OF TEMP */



void OBJToVLF::generateTriangularFaces() {

}

map<unsigned int, Vertex*> OBJToVLF::getListOfVertices() {
    return listOfVertices;
}

map<unsigned int, Edge*> OBJToVLF::getListOfEdges() {
    return listOfEdges;
}

map<unsigned int, Face*> OBJToVLF::getListOfFaces() {
    return listOfFaces;
}
