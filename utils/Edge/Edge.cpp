#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "../Vertex/Vertex.hpp"

using namespace std;

Edge::Edge(Vertex *firstVertex, Vertex *secondVertex) {
    this->firstVertex = firstVertex;
    this->secondVertex = secondVertex;
}

Vertex *Edge::getFirstVertex() {
    return firstVertex;
}

Vertex *Edge::getSecondVertex() {
    return secondVertex;
}

double Edge::getSizeInX() {
    double firstVertexValueInX = firstVertex->getX();
    double secondVertexValueInX = secondVertex->getX();
    return firstVertexValueInX > secondVertexValueInX ? firstVertexValueInX - secondVertexValueInX : secondVertexValueInX - firstVertexValueInX;
}

double Edge::getSizeInY() {
    double firstVertexValueInY = firstVertex->getY();
    double secondVertexValueInY = secondVertex->getY();
    return firstVertexValueInY > secondVertexValueInY ? firstVertexValueInY - secondVertexValueInY : secondVertexValueInY - firstVertexValueInY;
}

double Edge::getSizeInZ() {
    double firstVertexValueInZ = firstVertex->getZ();
    double secondVertexValueInZ = secondVertex->getZ();
    return firstVertexValueInZ > secondVertexValueInZ ? firstVertexValueInZ - secondVertexValueInZ : secondVertexValueInZ - firstVertexValueInZ;
}

void Edge::setVertices(Vertex *firstVertex, Vertex *secondVertex) {
    this->firstVertex = firstVertex;
    this->secondVertex = secondVertex;
}