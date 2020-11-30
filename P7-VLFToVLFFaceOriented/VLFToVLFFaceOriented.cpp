#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <math.h> 
#include "../utils/VLFReader/VLFReader.hpp"
#include "VLFToVLFFaceOriented.hpp"

using namespace std;


VLFToVLFFaceOriented::VLFToVLFFaceOriented() { };

void VLFToVLFFaceOriented::setInitialDataFromFile(string filePath) {
    //We create an VLFToVLFFaceOriented instance
    VLFReader *reader = new VLFReader();
    //We validate the status of the process of getting data from the file (0 = OK, -1 = ERROR)
    if(reader->getDataFromFileWithKeys(filePath) == -1)
        exit(1);
    //We set the list of VLF data
    listOfVertices = reader->getListOfVertices();
    listOfEdges = reader->getListOfEdges();
    listOfFaces = reader->getListOfFaces();
    //We generate the VLF Face oriented lists
    //The vertices are always the same
    vlfListOfVertices = listOfVertices;
    //We set the edges and faces with the face orientation correction
    setEdgesAndFacesWithCorrectedOrientation();

}

void VLFToVLFFaceOriented::createVLFFaceOrientedFile(string vlfPath) {
    
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
    writeListOfEdges(&binaryFile);
    writeListOfFaces(&binaryFile);
    binaryFile.close(); 
}

void VLFToVLFFaceOriented::writeListOfVertices(ofstream *binaryFile) {
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

void VLFToVLFFaceOriented::writeListOfEdges(ofstream *binaryFile) {
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

void VLFToVLFFaceOriented::writeListOfFaces(ofstream *binaryFile) {
    for(int i = 1; i <= vlfListOfFaces.size(); i++) {
        //We get the current vertex and it's coordinates
        Face *face = vlfListOfFaces[i];
        unsigned int firstEdgeKey = face->getFirstEdgeKey();
        unsigned int secondEdgeKey = face->getSecondEdgeKey();
        unsigned int thirdEdgeKey = face->getThirdEdgeKey();
        //We write the data to the binary file
        binaryFile->write(reinterpret_cast<char*>(&firstEdgeKey), sizeof(unsigned int));
        binaryFile->write(reinterpret_cast<char*>(&secondEdgeKey), sizeof(unsigned int));
        binaryFile->write(reinterpret_cast<char*>(&thirdEdgeKey), sizeof(unsigned int));
    }
}

void VLFToVLFFaceOriented::setEdgesAndFacesWithCorrectedOrientation() {
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        Face *currentFace = it->second;
        vector<double> faceNormal = getFaceNormal(currentFace);
        //cout << "Face normal = (" << faceNormal[0] << ", " << faceNormal[1] << ", " << faceNormal[2] << ")\n";
        double normal = faceNormal[2];
        cout << "Face normal mine = " << normal << endl;
        /*
        if(normal == 0)
            cout << "NO NORMAL" << endl;
        if(normal < 0)
            cout << "NEGATIVE NORMAL, WRONG ORIENTATION" << endl;
        if(normal > 0)
            cout << "CORRECT NORMAL" << endl;
            */

    }
}


Vertex *getVectorialDifference(Vertex *origin, Vertex *end) {
    return new Vertex(
        origin->getX() - end->getX(),
        origin->getY() - end->getY(),
        origin->getZ() - end->getZ()
    );
}

vector<double> crossProduct(Vertex *e1, Vertex *e2) {
    vector<double> result;
    result.push_back((e1->getY() * e2->getZ()) - (e1->getZ() * e2->getY())); //i
    result.push_back((e1->getX() * e2->getZ()) - (e1->getZ() * e2->getX())); //j
    result.push_back((e1->getX() * e2->getY()) - (e1->getY() * e2->getX())); //k
    return result;
}

vector<double> normalize(vector<double> crossProductResult) {
    vector<double> result;
    double module = sqrt((pow(crossProductResult[0], 2) + pow(crossProductResult[1], 2) + pow(crossProductResult[2], 2)));
    result.push_back(crossProductResult[0] / module);
    result.push_back(crossProductResult[1] / module);
    result.push_back(crossProductResult[2] / module);
    return result;
}

vector<double> VLFToVLFFaceOriented::getFaceNormal(Face *currentFace) {
    //We get the face's edges
    Edge *firstEdge = listOfEdges[currentFace->getFirstEdgeKey()];
    Edge *secondEdge = listOfEdges[currentFace->getSecondEdgeKey()];
    Edge *thirdEdge = listOfEdges[currentFace->getThirdEdgeKey()];
    //We get the face vertices
    Vertex *firstVertex = listOfVertices[firstEdge->getFirstVertexKey()];
    Vertex *secondVertex = listOfVertices[secondEdge->getFirstVertexKey()];
    Vertex *thirdVertex = listOfVertices[thirdEdge->getFirstVertexKey()];
    //We create new verteices (now representing vectors)
    Vertex *e1 = getVectorialDifference(firstVertex, secondVertex);
    Vertex *e2 = getVectorialDifference(secondVertex, thirdVertex);
    //We make the cross product
    vector<double> crossProductResult = crossProduct(e1, e2);
    return normalize(crossProductResult);
}

void VLFToVLFFaceOriented::addEdgeToTheVLFFaceOrientedList(Edge *edgeToAdd) {
    unsigned int edgesCount = vlfListOfEdges.size() + 1;
    listOfEdges.insert(pair<unsigned int, Edge*>(edgesCount, edgeToAdd));
}

void VLFToVLFFaceOriented::addFaceToTheVLFFaceOrientedList(Face *faceToAdd) {
    unsigned int facesCount = vlfListOfFaces.size() + 1;
    listOfFaces.insert(pair<unsigned int, Face*>(facesCount, faceToAdd));
}
