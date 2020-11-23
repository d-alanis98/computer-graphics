#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "OBJReader.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Face/Face.hpp"
#include "../utils/Utils/Utils.hpp"

using namespace std;

int OBJReader::getDataFromFile(string &filePath) {
    string line;
    unsigned int vertexCount = 1, facesCount = 1;
    //We open the file
    ifstream objFile(filePath);
    if(!objFile.is_open())
        return -1;

    //We extract data from the file
    while(getline(objFile, line)) {
        if(line[0] == '\n') 
            continue;
        //We split by spaces
        vector<string> coordinates = Utils::split(line, ' ');
        //If the current line does not starts with 'v' (for the vertex coordinates) or f (for face definition), we go to the other line

        if(coordinates[0] == "v") {
            //We extract the coordinates
            double x = stod(coordinates[1]);
            double y = stod(coordinates[2]);
            double z = stod(coordinates[3]);
            Vertex *vertex = new Vertex(x, y, z);
            //We insert the vertex in the list of vertices
            listOfVertices.insert(pair<unsigned int, Vertex*>(vertexCount, vertex));
            vertexCount++;
        } else if(coordinates[0] == "f") { //Faces
            vector<int> verticesKeysList = getVerticesKeysList(line);
            //With the vertices keys we can set the faces list
            vector<Vertex*> faceVertices;
            for(int vertexKey: verticesKeysList) {
                unsigned int vertexIndex = vertexKey > 0 ? vertexKey : listOfVertices.size() + vertexKey - 1;
                if(listOfVertices.find(vertexIndex) == listOfVertices.end()) {
                    cout << "[ERROR]: Vertex " << vertexIndex << " does not exist, aborting." << endl;
                    return -1;
                }
                Vertex *faceVertex = listOfVertices[vertexIndex];
                faceVertices.push_back(faceVertex);
            }
            Face *polygonalFace = new Face(faceVertices);
            //We insert the face in the list of faces
            listOfFaces.insert(pair<unsigned int, Face*>(facesCount, polygonalFace));
            facesCount++;
        }
        
    }
    //Because the OBJ files does not contain edge data, we need to generate it
    getEdgesFromFaceVertices();
    return 0;
}


vector<int> OBJReader::getVerticesKeysList(string faceDefinitionLine) {
    int vertexKey;
    vector<int> verticesKeysList;
    //We split by spaces to get the vertices
    vector<string> faceVertices = Utils::split(faceDefinitionLine, ' ');
    //We delete the first entry, because it is the "f" character, that indicates us that this line is a face definition
    faceVertices.erase(faceVertices.begin()); 
    //We iterate through the faces vertices
    for(string faceVertice : faceVertices) {
        //A face is defined in the following format: v/vt/vn, where vt is texture vertex and vn is normal vertex, we only care about the vertex (v)
        vector<string> verticesComponents = Utils::split(faceVertice, '/');
        //Other vertices might or not be present, so we need to validate that
        vertexKey = verticesComponents.size() > 0 ? stoi(verticesComponents[0]) : stoi(faceVertice);
        //We add it to the vertices key list
        verticesKeysList.push_back(vertexKey);
    }
    return verticesKeysList;
}

void OBJReader::createEdge(int firstVertexIndex, int secondVertexIndex, vector<Vertex *> faceVertices, unsigned int *edgesCount) {
    Vertex *firstVertex = faceVertices[firstVertexIndex];
    Vertex *secondVertex = faceVertices[secondVertexIndex];
    Edge *edgeToAdd = new Edge(firstVertex, secondVertex);
    //We verify if the edge already exists
    int edgeIndex = indexOfEdge(edgeToAdd);
    //If the edge already exists we won't add it again
    if(edgeIndex != -1)
        return;
    //Otherwise, we add it and increase the edge count (which as well is the edge id)
    listOfEdges.insert(pair<unsigned int, Edge*>(*edgesCount, edgeToAdd));
    (*edgesCount)++;
}


void OBJReader::getEdgesFromFaceVertices() {
    unsigned int edgesCount = 1;
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        //We get the face from the iterator, and obtain the vertices of it
        Face *currentFace = it->second;
        vector<Vertex *> faceVertices = currentFace->getVertices();
        //We get the number of vertices, which will also 
        int numberOfVertices = faceVertices.size();
        //Edge creation loop
        int localVertices = edgesCount;
        for(int i = 0, j = 1; j < numberOfVertices; i++, j++)
            createEdge(i, j, faceVertices, &edgesCount);
        //The closing edge
        createEdge(numberOfVertices - 1, 0, faceVertices, &edgesCount);
    }
}