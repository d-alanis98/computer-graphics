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

Face::Face(unsigned int firstEdgeKey, unsigned int secondEdgeKey, unsigned int thirdEdgeKey) {
    this->firstEdgeKey = firstEdgeKey;
    this->secondEdgeKey = secondEdgeKey;
    this->thirdEdgeKey = thirdEdgeKey;
}

void Face::setEdges(vector<Edge*> edges) {
    this->edges = edges;
}

void Face::setEdgesKeys(unsigned int firstEdgeKey, unsigned int secondEdgeKey, unsigned int thirdEdgeKey) {
    this->firstEdgeKey = firstEdgeKey;
    this->secondEdgeKey = secondEdgeKey;
    this->thirdEdgeKey = thirdEdgeKey;
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

unsigned int Face::getFirstEdgeKey() {
    return firstEdgeKey;
}

unsigned int Face::getSecondEdgeKey() {
    return secondEdgeKey;
}

unsigned int Face::getThirdEdgeKey() {
    return thirdEdgeKey;
}

double Face::getFaceNormal() {
    return 1.0;
}

void Face::fixFaceNormal() {
    return;
}