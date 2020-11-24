#include <iostream>
#include <map>
#include <vector>
#include "../utils/Vertex/Vertex.cpp"
#include "../utils/Edge/Edge.cpp"
#include "../utils/Face/Face.cpp"


using namespace std;


bool isTheSameEdge(Edge *current, Edge *target) {
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

int indexOfEdge(Edge *target, map<unsigned int, Edge*>listOfEdges) {
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

int main(int argc, char **argv) {
    map<unsigned int, Vertex*> listOfVertices;
    map<unsigned int, Edge*> listOfEdges;
    map<unsigned int, Face*> listOfFaces;

    listOfVertices.insert(pair<unsigned int, Vertex*>(1, new Vertex(0, 0, 0));
    listOfVertices.insert(pair<unsigned int, Vertex*>(2, new Vertex(3, -3, 0));
    listOfVertices.insert(pair<unsigned int, Vertex*>(3, new Vertex(4, -4, 0));
    listOfVertices.insert(pair<unsigned int, Vertex*>(4, new Vertex(-2, -6, 0));
    listOfVertices.insert(pair<unsigned int, Vertex*>(5, new Vertex(0, -6, 0));
    listOfVertices.insert(pair<unsigned int, Vertex*>(6, new Vertex(-3, -3, 0));

    listOfEdges.insert(pair<unsigned int, Edge*>(1, new Edge(listOfVertices[1], listOfVertices[2])));
    listOfEdges.insert(pair<unsigned int, Edge*>(2, new Edge(listOfVertices[2], listOfVertices[3])));
    listOfEdges.insert(pair<unsigned int, Edge*>(3, new Edge(listOfVertices[3], listOfVertices[4])));
    listOfEdges.insert(pair<unsigned int, Edge*>(4, new Edge(listOfVertices[4], listOfVertices[5])));
    listOfEdges.insert(pair<unsigned int, Edge*>(5, new Edge(listOfVertices[5], listOfVertices[6])));
    listOfEdges.insert(pair<unsigned int, Edge*>(6, new Edge(listOfVertices[6], listOfVertices[1])));
    listOfEdges.insert(pair<unsigned int, Edge*>(7, new Edge(listOfVertices[2], listOfVertices[6])));
    listOfEdges.insert(pair<unsigned int, Edge*>(8, new Edge(listOfVertices[2], listOfVertices[5])));
    //First face
    vector<Edge*> firstFaceEdges;
    firstFaceEdges.push_back(listOfEdges[1]);
    firstFaceEdges.push_back(listOfEdges[7]);
    firstFaceEdges.push_back(listOfEdges[6]);
    listOfFaces.insert(pair<unsigned int, Face*>(1, new Face(firstFaceEdges)));
    //Second face
    vector<Edge*> secondFaceEdges;
    secondFaceEdges.push_back(listOfEdges[8]);
    secondFaceEdges.push_back(listOfEdges[5]);
    secondFaceEdges.push_back(listOfEdges[7]);
    listOfFaces.insert(pair<unsigned int, Face*>(2, new Face(secondFaceEdges)));
    //Third face
    vector<Edge*> thirdFaceEdges;
    thirdFaceEdges.push_back(listOfEdges[2]);
    thirdFaceEdges.push_back(listOfEdges[3]);
    thirdFaceEdges.push_back(listOfEdges[4]);
    thirdFaceEdges.push_back(listOfEdges[8]);
    listOfFaces.insert(pair<unsigned int, Face*>(3, new Face(thirdFaceEdges)));
    

    //TRIANGULATION
    /** EXPECTED OUTPUT = 4 FACES
    F1 (0, 0, 0)->(3, -3, 0), (3, -3, 0)->(-3, -3, 0), (-3, -3, 0)->(0, 0, 0)
    F2 (3, -3, 0)->(0, -6, 0), (0, -6, 0)->(-3, -3, 0), (-3, -3, 0)->(3, -3, 0)
    F3 (3, -3, 0)->(4, -4, 0), (4, -4, 0)->(0, -6, 0), (0, -6, 0)->(3, -3, 0) 
    F4 (4, -4, 0)->(-2, -6, 0), (-2, -6, 0)->(0, -6, 0), (0, -6, 0)->(4, -4, 0)
    */
    map<unsigned int, Face*> newFacesList;
    for(map<unsigned int, Face*>::iterator it = listOfFaces.begin(); it != listOfFaces.end(); it++) {
        Face *currentFace = it->second;
        //If it is already a triangle we skip the ptriangulation process
        vector<Edge *> faceEdges = currentFace->getEdges();
        if(faceEdges.size() == 3)
            continue;
        for(int i = 0; i < faceEdges.size() - 1; i++) {
            Edge *firstEdge = new Edge(faceEdges[]);
            Edge *secondEdge = new Edge();
            Edge *thirdEdge = newEdge();

        }
        
    }

    return 0;
}

