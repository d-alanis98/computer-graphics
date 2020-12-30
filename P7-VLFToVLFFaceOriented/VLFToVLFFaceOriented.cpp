#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h> 
#include "../utils/VLFReader/VLFReader.hpp"
#include "VLFToVLFFaceOriented.hpp"

using namespace std;

//Utils
Vertex *normalize(Vertex *);
double getFaceArea(vector<Vertex*>);
bool isTheSameEdge(Edge *, Edge *);
bool hasSharedEdge(vector<Vertex*>, vector<Vertex*>);
Vertex *crossProduct(Vertex *, Vertex *);
double getSemiperimeter(vector<double>);
vector<double> getSides(vector<Vertex*>);
Vertex *getCentroidCoordinate(vector<Vertex*>);
void printVLFOrientationResult(bool);
void printBadOrientationWarning(unsigned int, unsigned int);

VLFToVLFFaceOriented::VLFToVLFFaceOriented() { 
    badOriented = false;
};

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
    //The faces can change (but the number of faces will always remain the same)
    vlfListOfFaces = listOfFaces;
    //The edges can change (more edges could be added)
    vlfListOfEdges = listOfEdges;
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
    for(map<unsigned int, Face*>::iterator it = vlfListOfFaces.begin(); it != vlfListOfFaces.end(); it++) {
        Face *currentFace = it->second;
        map<unsigned int, Face*> faceNeighboors = getFaceNeighboors(currentFace, it->first);
        for(map<unsigned int, Face*>::iterator neighborIt = faceNeighboors.begin(); neighborIt != faceNeighboors.end(); neighborIt++) {
            Face *neighboorFace = neighborIt->second;
            verifyCommonEdgeAndFixIfNecessary(
                pair<unsigned int, Face*>(it->first, currentFace), 
                pair<unsigned int, Face*>(neighborIt->first, neighboorFace)
            );
        }
    }
    //We let the user know if the VLF was correctly oriented or not
    printVLFOrientationResult(badOriented);

    //TODO handle inward pointing (all edges need to be flipped)
    if(!areFacesCorrectlyOriented())
        cout << "TODO: hanlde this case, all faces are pointing inward" << endl;
}

void VLFToVLFFaceOriented::verifyCommonEdgeAndFixIfNecessary(pair<unsigned int, Face*> referencePair, pair<unsigned int, Face*> faceToVerifyPair) {
    Face *reference = referencePair.second;
    Face *faceToVerify = faceToVerifyPair.second;
    //We get the common edge
    Edge *commonEdge = getCommonEdge(reference, faceToVerify);
    //If there is no common edge (ie: when the 2 edges have the vertices in the same order) we won't do any change, because it is not required
    if(commonEdge == NULL)
        return;
    //We raise the bad orientation flag in state
    badOriented = true;
    //Otherwise, we fix the order of the vertices of the face to verify edge
    printBadOrientationWarning(referencePair.first, faceToVerifyPair.first);
    fixBadEdgeOrientation(
        pair<unsigned int, Face*>(faceToVerifyPair.first, faceToVerify), 
        commonEdge
    );
}

void VLFToVLFFaceOriented::fixBadEdgeOrientation(pair<unsigned int, Face*> faceToVerifyPair, Edge *commonEdge) {
    unsigned int correctedEdgeIndex = 0;
    //We get the data from the pair
    Face *faceToVerify = faceToVerifyPair.second;
    unsigned int faceToVerifyKey = faceToVerifyPair.first;
    //We get the face edges
    vector<Edge*> faceEdges = getFaceEdges(faceToVerify);
    //To fix the vertices order of the face, we reverse the vertices
    Edge *fixedOrderEdge = new Edge(commonEdge->getSecondVertexKey(), commonEdge->getFirstVertexKey());
    int correctedEdgeKey = keyOfEdge(fixedOrderEdge);
    //If the edge already exists in the list, we use the existing key
    if(correctedEdgeKey != -1)
        correctedEdgeIndex = correctedEdgeKey; 
    else { //Otherwise, we add it to the list
        addEdgeToTheVLFFaceOrientedList(fixedOrderEdge); 
        correctedEdgeIndex = vlfListOfEdges.size();
    }
    //We update the corresponding edge
    map<unsigned int, unsigned int> faceEdgesKeys;

    for(int i = 0; i < 3; i++) {
        unsigned int previousEdgeIndex = i - 1, nextEdgeIndex = i + 1;      
        if(isTheSameEdge(faceEdges[i], commonEdge)) {
            faceEdgesKeys[i] = correctedEdgeIndex;
            //Special cases
            if(i == 0)
                previousEdgeIndex = 2;
            if(i == 2)
                nextEdgeIndex = 0;
            //We update the edges (because we moved the starting and ending vertex of an edge, so the others were affected, we only need to apply a correction)
            //where the second vertex of the previous edge will be the first vertex of the recently reversed edge, and the first vertex of the next vertex will
            //be the second vertex of the recently reverted edge
            //Starting from the previous
            Edge *fixedPreviousEdge = new Edge(
                faceEdges[previousEdgeIndex]->getFirstVertexKey(),
                fixedOrderEdge->getFirstVertexKey()
            );
            int correctedPreviousEdgeKey = keyOfEdge(fixedPreviousEdge);
            //If the edge already exists in the list, we use the existing key
            if(correctedPreviousEdgeKey == -1){ //If it didn't exist, we add it to the list
                addEdgeToTheVLFFaceOrientedList(fixedPreviousEdge); 
                correctedPreviousEdgeKey = vlfListOfEdges.size();
            }
            faceEdgesKeys[previousEdgeIndex] = correctedPreviousEdgeKey;
            //And the next edge
            Edge *fixedNextEdge = new Edge(
                fixedOrderEdge->getSecondVertexKey(),
                faceEdges[nextEdgeIndex]->getSecondVertexKey()
            );
            int correctedNextEdgeKey = keyOfEdge(fixedNextEdge);
            //If the edge already exists in the list, we use the existing key
            if(correctedNextEdgeKey == -1){ //If it didn't exist, we add it to the list
                addEdgeToTheVLFFaceOrientedList(fixedNextEdge); 
                correctedNextEdgeKey = vlfListOfEdges.size();
            }
            faceEdgesKeys[nextEdgeIndex] = correctedNextEdgeKey;
            break;
        }
    }
    //We create the new face
    Face *correctlyOrientedFace = new Face(
        faceEdgesKeys[0],
        faceEdgesKeys[1],
        faceEdgesKeys[2]
    );
    //We replace the face with the new correctly oriented face
    replaceFaceInTheVLFFaceOrientedList(pair<unsigned int, Face*>(faceToVerifyKey, correctlyOrientedFace));
}



Vertex *getVectorialDifference(Vertex *origin, Vertex *end) {
    return new Vertex(
        origin->getX() - end->getX(),
        origin->getY() - end->getY(),
        origin->getZ() - end->getZ()
    );
}



Vertex *VLFToVLFFaceOriented::getFaceNormal(Face *currentFace) {
    //We get the face's edges
    Edge *firstEdge = vlfListOfEdges[currentFace->getFirstEdgeKey()];
    Edge *secondEdge = vlfListOfEdges[currentFace->getSecondEdgeKey()];
    Edge *thirdEdge = vlfListOfEdges[currentFace->getThirdEdgeKey()];
    //We get the face vertices
    Vertex *firstVertex = listOfVertices[firstEdge->getFirstVertexKey()];
    Vertex *secondVertex = listOfVertices[secondEdge->getFirstVertexKey()];
    Vertex *thirdVertex = listOfVertices[thirdEdge->getFirstVertexKey()];
    //We create new verteices (now representing vectors)
    Vertex *e1 = getVectorialDifference(firstVertex, secondVertex);
    Vertex *e2 = getVectorialDifference(secondVertex, thirdVertex);
    //We make the cross product
    Vertex *crossProductResult = crossProduct(e1, e2);
    return normalize(crossProductResult);
}

void VLFToVLFFaceOriented::addEdgeToTheVLFFaceOrientedList(Edge *edgeToAdd) {
    unsigned int edgesCount = vlfListOfEdges.size() + 1;
    vlfListOfEdges.insert(pair<unsigned int, Edge*>(edgesCount, edgeToAdd));
}

void VLFToVLFFaceOriented::replaceFaceInTheVLFFaceOrientedList(pair<unsigned int, Face*> updatedFacePair) {
    vlfListOfFaces[updatedFacePair.first] = updatedFacePair.second;
}


/*
Now that all faces are correctly aligned across their neighboors, we need to verify that all faces now point to the outside.
For that porpouse, we are going to use the following property:

        Nfaces
    I = Sum( Cx[i] * Nx[i] * Area[i])
        i = 1

    Where:
        Cx = X coordinate of current face's midpoint (centroid)
        Nx = X coordinate of current face's normal
        Area = the current face's area
    
    Based on the I value, we can conclude the following:
        I >= 0 => The normals point outward
        I < 0  => The normals point inward

    Which comes from the following volume property that is only true - a positive volume (the volume cannot be negative) - only
    when the normals point outward:

        Int(CxNx)dA = Int(CyNy)dA = Int(CzNz)dA = Volume 
    
    So, for instance, this method also gives us the volume of the polymesh.
    

*/
bool VLFToVLFFaceOriented::areFacesCorrectlyOriented() {
    double criterion = 0;
    for(map<unsigned int, Face*>::iterator it = vlfListOfFaces.begin(); it != vlfListOfFaces.end(); it++) {
        Face *currentFace = it->second;
        //We get the normal
        Vertex *faceNormal = getFaceNormal(currentFace);
        vector<Vertex*> faceVertices = getFaceVertices(currentFace);
        //The local criterion is going to be Cx * Nx * FaceArea
        double area = getFaceArea(faceVertices);
        Vertex *centroid = getCentroidCoordinate(faceVertices);
        criterion += centroid->getX() * faceNormal->getX() * area;
    }
    return criterion >= 0;
}

unsigned int VLFToVLFFaceOriented::keyOfEdge(Edge *target) {
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

Edge *VLFToVLFFaceOriented::getCommonEdge(Face *reference, Face *faceToVerify) {
    int edgeKey = -1;
    //We get the vertices
    vector<Edge*> referenceEdges = getFaceEdges(reference);
    vector<Edge*> faceToVerifyEdges = getFaceEdges(faceToVerify);
    //We validate the shared edge, it must never be the in the same order, ie:
    //If Face X has and edge, which consists in the vertices A and B, then its neighboor Face Y that shares the same vertices, must have its edge
    //in the order: B and A
    for(int i = 0; i < 3; i++) {
        Edge *referenceEdge = referenceEdges[i];
        Edge *edgeToVerify = faceToVerifyEdges[i];
        if(
            referenceEdge->getFirstVertexKey() == edgeToVerify->getFirstVertexKey() &&
            referenceEdge->getSecondVertexKey() == edgeToVerify->getSecondVertexKey()
        )
            return edgeToVerify;
    }
    return NULL;
}

vector<Vertex*> VLFToVLFFaceOriented::getFaceVertices(Face *currentFace) {
    vector<Vertex*> result;
    //We get the face's edges
    Edge *firstEdge = vlfListOfEdges[currentFace->getFirstEdgeKey()];
    Edge *secondEdge = vlfListOfEdges[currentFace->getSecondEdgeKey()];
    Edge *thirdEdge = vlfListOfEdges[currentFace->getThirdEdgeKey()];
    //We get the face vertices
    result.push_back(listOfVertices[firstEdge->getFirstVertexKey()]); //First vertex
    result.push_back(listOfVertices[secondEdge->getFirstVertexKey()]); //Second vertex
    result.push_back(listOfVertices[thirdEdge->getFirstVertexKey()]); //Third vertex
    return result;
}

vector<Edge*> VLFToVLFFaceOriented::getFaceEdges(Face *currentFace) {
    vector<Edge*> result;
    result.push_back(vlfListOfEdges[currentFace->getFirstEdgeKey()]);
    result.push_back(vlfListOfEdges[currentFace->getSecondEdgeKey()]);
    result.push_back(vlfListOfEdges[currentFace->getThirdEdgeKey()]);
    return result;
}

map<unsigned int, Face *> VLFToVLFFaceOriented::getFaceNeighboors(Face *currentFace, unsigned int faceKey) {
    map<unsigned int, Face *> faceNeighboors;
    vector<Vertex*> faceVertices = getFaceVertices(currentFace);
    for(map<unsigned int, Face*>::iterator it = vlfListOfFaces.begin(); it != vlfListOfFaces.end(); it++) {
        //We skip verification for own face
        if(faceKey == it->first)
            continue;
        Face *faceToVerify = it->second;
        vector<Vertex *> faceToVerifyVertices = getFaceVertices(faceToVerify);
        //If the face has shared edge (2 same vertices) we add it to the nieghboors vector
        if(hasSharedEdge(faceVertices, faceToVerifyVertices)) 
            faceNeighboors.insert(pair<unsigned int, Face*>(it->first, faceToVerify));
    }

    return faceNeighboors;

}



//Utils

Vertex *crossProduct(Vertex *e1, Vertex *e2) {
    Vertex *result = new Vertex();
    result->setCoordinates(
        (e1->getY() * e2->getZ()) - (e1->getZ() * e2->getY()), //i
        -((e1->getX() * e2->getZ()) - (e1->getZ() * e2->getX())), //j
        (e1->getX() * e2->getY()) - (e1->getY() * e2->getX()) //k
    );
    return result;
}

Vertex *normalize(Vertex *crossProductResult) {
    Vertex *result = new Vertex();
    //We get the vector magnitude
    double module = sqrt((pow(crossProductResult->getX(), 2) + pow(crossProductResult->getY(), 2) + pow(crossProductResult->getZ(), 2)));
    result->setCoordinates(
        crossProductResult->getX() / module,
        crossProductResult->getY() / module,
        crossProductResult->getZ() / module
    );
    return result;
}

vector<double> getSides(vector<Vertex*> faceVertices) {
    vector<double> edgeSizes;
    for(int i = 0; i < 3; i++) {
        int firstVertexIndex = i, secondVertexIndex = i + 1;
        if(i == 2)
            secondVertexIndex = 0;
        //First we get the points difference (the edge vector)
        Vertex *edgeVector = new Vertex(
            faceVertices[firstVertexIndex]->getX() - faceVertices[secondVertexIndex]->getX(),
            faceVertices[firstVertexIndex]->getY() - faceVertices[secondVertexIndex]->getY(),
            faceVertices[firstVertexIndex]->getZ() - faceVertices[secondVertexIndex]->getZ()
        );
        //Then, we get the edge size sqrt(X² + Y² + Z²), where X, Y and Z are contained in the edgeVector, and are equal to X = x2 - x1, Y = y2 - y1, Z = z2 - z1
        double edgeSize = sqrt(pow(edgeVector->getX(), 2) + pow(edgeVector->getY(), 2) + pow(edgeVector->getZ(), 2));
        //We add it to the sizes list
        edgeSizes.push_back(edgeSize);
    }
    return edgeSizes;
}

double getSemiperimeter(vector<double> sides) {
    double sidesSum = 0;
    for(double sideLength : sides)
        sidesSum += sideLength;
    return sidesSum / 2;
}

double getFaceArea(vector<Vertex*> faceVertices) {
    vector<double> sides = getSides(faceVertices);
    double semiperimeter = getSemiperimeter(sides);
    //We are going to apply the Heron's formula, A = sqrt(s(s-a)(s-b)(s-c)) where s is the semiperimeter and a, b, c are the sides
    return sqrt(semiperimeter * (semiperimeter - sides[0]) * (semiperimeter - sides[1]) * (semiperimeter - sides[2]));
}

bool hasVertex(vector<Vertex*> verticesToVerify, Vertex *target) {
    return (find(verticesToVerify.begin(), verticesToVerify.end(), target) != verticesToVerify.end());
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

bool hasSharedEdge(vector<Vertex*> targetVertices, vector<Vertex*> verticesToVerify) {
    for(int i = 0; i < 3; i++) {
        int firstVertexIndex = i, secondVertexIndex = i + 1;
        if(i == 2)
            secondVertexIndex = 0;
        if(hasVertex(verticesToVerify, targetVertices[firstVertexIndex]) && hasVertex(verticesToVerify, targetVertices[secondVertexIndex]))
            return true;
        
        
    }
    return false;
}

Vertex *getCentroidCoordinate(vector<Vertex*> faceVertices) {
    double sumInX = 0, sumInY = 0, sumInZ = 0;
    for(int i = 0; i < 3; i++) {
        sumInX += faceVertices[i]->getX();
        sumInY += faceVertices[i]->getY();
        sumInZ += faceVertices[i]->getZ();
    }

    return new Vertex(
        sumInX / 3,
        sumInY / 3,
        sumInZ / 3
    );
}

void printBadOrientationWarning(unsigned int referenceFaceKey, unsigned int faceToVerifyKey) {
    cout << "BAD ORIENTATION: Faces " << referenceFaceKey << " and " << faceToVerifyKey << " share vertices and their edges have them in the same order. Proceeding to fix..." << endl;
}

void printVLFOrientationResult(bool badOriented) {
    cout << "\n\n****************************************" << endl;
    if(badOriented) {
        cout << "*  The VLF had bad oriented faces      *" << endl;
        cout << "*  But they were fixed successfully :) *" << endl;
    }
    else {
        cout << "* The VLF faces orientation is correct *" << endl;
        cout << "* No change was required :)            *" << endl;
    }
    cout << "****************************************" << endl;
}
