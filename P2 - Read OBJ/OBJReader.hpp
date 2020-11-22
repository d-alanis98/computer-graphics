#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <map>
#include <string>

#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Face/Face.hpp"

class OBJReader {
    private:
        string filePath;
        map<unsigned int, Vertex*> listOfVertices;
        map<unsigned int, Edge*> listOfEdges;
        map<unsigned int, Face*> listOfFaces;
        double maximumPointInX;
        double maximumPointInY;
        double maximumPointInZ;
        double minimumPointInX;
        double minimumPointInY;
        double minimumPointInZ;
    public:
        OBJReader(string);
        void readFile();
        //Bounding box
        void computeBoundingBox();
        double getMaximumPointInX();
        double getMaximumPointInY();
        double getMaximumPointInZ();
        double getMinimumPointInX();
        double getMaximumPointInY();
        double getMinimumPointInZ();
        //List getters
        map<unsigned int, Vertex*> getListOfVertexes();
        map<unsigned int, Edge*> getListOfEdges();
        map<unsigned int, Face*> getListOfFaces();

};

#endif