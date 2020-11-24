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
    //To get the VLF list of edges we need to process the retrieved list from the OBJ
    setVLFEdgesList();
    //The same applies for the faces
    setVLFFacesList();
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
    writeListOfEdges(&binaryFile);
    writeListOfFaces(&binaryFile);
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

/*
TEMP
*/
void OBJToVLF::printVLFFileInformation(string vlfPath) {
    unsigned int totalVertices;
    unsigned int totalEdges;
    unsigned int totalFaces;
    ifstream binaryFile(vlfPath, ios::out|ios::binary);
    //Header: vertices, edges, faces (without separator, it is in binary form)
    binaryFile.read(reinterpret_cast<char*>(&totalVertices), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalEdges), sizeof(unsigned int));
    binaryFile.read(reinterpret_cast<char*>(&totalFaces), sizeof(unsigned int));
    cout << "\n*********************\n* VLF file content: *\n*********************" << endl;
    cout << "Number of vertices = " << totalVertices << endl;
    cout << "Number of edges = " << totalEdges << endl;
    cout << "Numer of faces (triangles) = " << totalFaces << endl;
    //List of vertices
    /*
    readListOfVertices(&binaryFile, totalVertices);
    readListOfEdges(&binaryFile, totalEdges);
    readListOfFaces(&binaryFile, totalFaces);
    */
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
        cout << "Face " << i << " = (" << firstEdge << ", " << secondEdge << ", " << thirdEdge << ")\n";
    }
} 

/* END OF TEMP */

void OBJToVLF::setVLFEdgesList() {
    for(map<unsigned int, Edge*>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++) {
        Edge *currentEdge = it->second;
        Vertex *firstVertex = currentEdge->getFirstVertex();
        Vertex *secondVertex = currentEdge->getSecondVertex();
        //We get the key of the vertices in the list, because in VLF we will store the vertices key instead of the actual vertices coordinates
        unsigned int firstVertexKey = keyOfVertex(firstVertex);
        unsigned int secondVertexKey = keyOfVertex(secondVertex);
        //We validate the vertices existance
        if(firstVertexKey == -1 || secondVertexKey == -1) {
            cout << "[ERROR]: Vertex not found, aborting." << endl;
            exit(1);
        }
        //We create a new Edge with the overloaded constructor that receives the vertices key, instead of a reference to Vertex class instances
        Edge *edgeToAdd = new Edge(firstVertexKey, secondVertexKey);
        //We add the edge to the vlf list of edges
        addEdgeToTheList(edgeToAdd);
    }
}

void OBJToVLF::setVLFFacesList() {
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        Face *currentFace = it->second;
        vector<Vertex*> faceVertices = currentFace->getVertices();
        generateTriangularFaces(faceVertices);
    }
}

void OBJToVLF::addEdgeToTheList(Edge *edgeToAdd) {
    unsigned int edgesCount = vlfListOfEdges.size() + 1;
    vlfListOfEdges.insert(pair<unsigned int, Edge*>(edgesCount, edgeToAdd));
}

void OBJToVLF::addFaceToTheList(Face *faceToAdd) {
    unsigned int facesCount = vlfListOfFaces.size() + 1;
    vlfListOfFaces.insert(pair<unsigned int, Face*>(facesCount, faceToAdd));
}

void OBJToVLF::createTriangularFace(vector<Vertex *> triangleVertices) {
    vector<unsigned int> faceEdgesKeys;
    for(int i = 0; i < 3; i++) {
        int firstVertexIndex = i, secondVertexIndex = i + 1;
        //The last edge will be the closing one, from the last to the first
        if(i == 2){
            firstVertexIndex = 2;
            secondVertexIndex = 0;
        }
        unsigned int firstVertexKey = keyOfVertex(triangleVertices[firstVertexIndex]);
        unsigned int secondVertexKey = keyOfVertex(triangleVertices[secondVertexIndex]);
        Edge *triangleEdge = new Edge(firstVertexKey, secondVertexKey);
        unsigned int edgeKey = keyOfEdge(triangleEdge);
        if(edgeKey == -1) {
            addEdgeToTheList(triangleEdge);
            edgeKey = vlfListOfEdges.size();
        }
        faceEdgesKeys.push_back(edgeKey);
    }
    Face *triangularFace = new Face(faceEdgesKeys[0], faceEdgesKeys[1], faceEdgesKeys[2]);
    addFaceToTheList(triangularFace);
}

vector<vector<Vertex*>> polygonsToTriangleVertices(vector<Vertex*> faceVertices) {
    vector<vector<Vertex*>> triangleVertices;

    int lastVertexVisited = 0;
    for(int i = 0; i < faceVertices.size() - 2; i++) {
        vector<Vertex*> currentTriangularFaceVertices;
        int firstVertex = lastVertexVisited, secondVertex = lastVertexVisited + 1, thirdVertex = 0; 
        //Special case, in all other cases the third vertex is the return to the first one (0), except for the first iteration
        //In the first iteration, the third vertex will be exactly the third vertex in the list
        if(i == 0) 
            thirdVertex = lastVertexVisited + 2;
        //We add the vertices indexes to the vector
        currentTriangularFaceVertices.push_back(faceVertices[firstVertex]);
        currentTriangularFaceVertices.push_back(faceVertices[secondVertex]);
        currentTriangularFaceVertices.push_back(faceVertices[thirdVertex]);
        //We put ourselves in the next vertex for the next iteration
        lastVertexVisited = secondVertex + 1;
        //We push the triangular vertices that we got in this iteration
        triangleVertices.push_back(currentTriangularFaceVertices);
    }
    
    
    return triangleVertices;
}


void OBJToVLF::generateTriangularFaces(vector<Vertex*> faceVertices) {
    vector<vector<Vertex*>> facesToAdd;
    if(faceVertices.size() == 3) {
        facesToAdd.push_back(faceVertices);
    } else {
        facesToAdd = polygonsToTriangleVertices(faceVertices);
    } 
    for(int i = 0; i < facesToAdd.size(); i++)
        createTriangularFace(facesToAdd[i]);
}

unsigned int OBJToVLF::keyOfVertex(Vertex *targetVertex) {
    unsigned int key = -1;
    double x = targetVertex->getX();
    double y = targetVertex->getY();
    double z = targetVertex->getZ();
    for (auto &it : listOfVertices) {
        Vertex *currentVertex = it.second;
        double currentTargetX = currentVertex->getX();
        double currentTargetY = currentVertex->getY();
        double currentTargetZ = currentVertex->getZ();
        if (x == currentTargetX && y == currentTargetY && z == currentTargetZ) {
            key = it.first;
            break;
        }
    }
    return key;
}

bool isTheSameEdge(Edge *current, Edge *target) {
    bool isTheSame = true;
    //We check the first vertex
    if(target->getFirstVertexKey() != current->getFirstVertexKey())
        isTheSame = false;
    //We check the second vertex
    if(target->getSecondVertexKey() != current->getSecondVertexKey())
        isTheSame = false;
    return isTheSame;
}

unsigned int OBJToVLF::keyOfEdge(Edge *target) {
    unsigned int edgeIndex = -1;
    for(map<unsigned int, Edge*>::iterator it = vlfListOfEdges.begin(); it != vlfListOfEdges.end(); it++) {
        Edge *current = it->second;
        if(isTheSameEdge(current, target)) {
            edgeIndex = it->first;
            break;
        }
    }
    return edgeIndex;
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

void OBJToVLF::printRetrievedDataFromOBJ() {
    cout << "\n*********************\n* OBJ file content: *\n*********************" << endl;
    cout << "\nTotal vertices in OBJ: " << listOfVertices.size() << endl;
    cout << "Total generated edges in OBJ: " << listOfEdges.size() << endl;
    cout << "Total faces in OBJ: " << listOfFaces.size() << endl;
}

void OBJToVLF::printResults() {
    cout << "\n************************************" << endl;
    cout << "* VLF file generated successfully! *" << endl;
    cout << "************************************" << endl;
}
