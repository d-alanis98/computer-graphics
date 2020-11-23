#ifndef FACE_H
#define FACE_H

#include <vector>
#include "../Vertex/Vertex.hpp"
#include "../Edge/Edge.hpp"

using namespace std;

class Face {
    private:
        vector<Edge*> edges;
        vector<Vertex*> vertices;
        double faceNormal;
    public:
        //Constructors
        Face(vector<Edge*>);
        Face(vector<Vertex*>);
        //Setters and getters
        void setEdges(vector<Edge*>);
        void setVertices(vector<Vertex*>);
        vector<Edge*> getEdges();
        vector<Vertex*> getVertices();
        //Utils
        double getFaceNormal();
        void fixFaceNormal();
};

#endif
