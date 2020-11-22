#ifndef FACE_H
#define FACE_H

#include <vector>
#include "../Edge/Edge.cpp"

class Face {
    private:
        vector<Edge> edges;
        double faceNormal;
    public:
        Face();
        Face(Edge, Edge, Edge);
        vector<Edge> getEdges();
        double getFaceNormal();
        void fixFaceNormal();
};

#endif
