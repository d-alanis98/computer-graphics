#ifndef FILE_READER_H
#define FILE_READER_H

#include <map>
#include <string>

#include "../Vertex/Vertex.hpp"
#include "../Edge/Edge.hpp"
#include "../Face/Face.hpp"

using namespace std;

class FileReader {
    protected:
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
        double objectWidth;
        double objectHeight;
        double objectDepth;

    public:
        FileReader();
        virtual int getDataFromFile(string &) = 0;
        //Bounding box
        void calculateObjectDimensions();
        void calculateObjectDimensionsOfListsWithKeys();
        double getMaximumPointInX();
        double getMaximumPointInY();
        double getMaximumPointInZ();
        double getMinimumPointInX();
        double getMinimumPointInY();
        double getMinimumPointInZ();
        double getObjectWidth();
        double getObjectHeight();
        double getObjectDepth();
        void setMaximumAndMinimumValues();
        void setMaximumAndMinimumValuesOfListsWithKeys();
        //List getters
        map<unsigned int, Vertex*> getListOfVertices();
        map<unsigned int, Edge*> getListOfEdges();
        map<unsigned int, Face*> getListOfFaces();
        //Auxiliar methods
        int indexOfEdge(Edge *);
        bool isTheSameEdge(Edge *, Edge *);
};

#endif