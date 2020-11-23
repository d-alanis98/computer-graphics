#ifndef EDGE_H
#define EDGE_H

#include "../Vertex/Vertex.hpp"

class Edge {
    private:
        Vertex *firstVertex;
        Vertex *secondVertex;
    public:
        Edge(Vertex *, Vertex *);
        Vertex *getFirstVertex();
        Vertex *getSecondVertex();
        double getSizeInX();
        double getSizeInY();
        double getSizeInZ();
        void setVertices(Vertex *, Vertex *);
};

#endif