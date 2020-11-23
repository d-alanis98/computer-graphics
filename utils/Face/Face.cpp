#include <iostream>
#include <vector>
#include "Face.hpp"
#include "../Vertex/Vertex.hpp"
#include "../Edge/Edge.hpp"


using namespace std;


Face::Face(vector<Edge*> edges) {
    this->edges = edges;
}

Face::Face(vector<Vertex*> vertices) {
    this->vertices = vertices;
}

void Face::setEdges(vector<Edge*> edges) {
    this->edges = edges;
}

void Face::setVertices(vector<Vertex*> vertices) {
    this->vertices = vertices;
}

vector<Edge*> Face::getEdges() {
    return edges;
}

vector<Vertex*> Face::getVertices() {
    return vertices;
}

double Face::getFaceNormal() {
    return 1.0;
}

void Face::fixFaceNormal() {
    return;
}