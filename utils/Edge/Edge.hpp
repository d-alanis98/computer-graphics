#ifndef EDGE_H
#define EDGE_H

#include "../Vertex/Vertex.hpp"

class Edge {
    private:
        Vertex *firstVertex;
        Vertex *secondVertex;
        unsigned int firstVertexKey;
        unsigned int secondVertexKey;
    public:
        Edge(Vertex *, Vertex *);
        Edge(unsigned int, unsigned int);
        Vertex *getFirstVertex();
        Vertex *getSecondVertex();
        unsigned int getFirstVertexKey();
        unsigned int getSecondVertexKey();
        double getSizeInX();
        double getSizeInY();
        double getSizeInZ();
        void setVertices(Vertex *, Vertex *);
        void setVertices(unsigned int, unsigned int);
};

#endif