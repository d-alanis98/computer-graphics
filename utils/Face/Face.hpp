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
        unsigned int firstEdgeKey, secondEdgeKey, thirdEdgeKey;
    public:
        //Constructors
        Face(vector<Edge*>);
        Face(vector<Vertex*>);
        Face(unsigned int, unsigned int, unsigned int);
        //Setters and getters
        void setEdges(vector<Edge*>);
        void setVertices(vector<Vertex*>);
        void setEdgesKeys(unsigned int, unsigned int, unsigned int);
        vector<Edge*> getEdges();
        vector<Vertex*> getVertices();
        unsigned int getFirstEdgeKey();
        unsigned int getSecondEdgeKey();
        unsigned int getThirdEdgeKey();
        //Utils
        double getFaceNormal();
        void fixFaceNormal();
};

#endif
