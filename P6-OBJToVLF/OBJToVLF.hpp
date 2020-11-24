#ifndef OBJ_TO_VLF_H
#define OBJ_TO_VLF_H

#include <iostream>
#include <map>
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Edge/Edge.hpp"
#include "../utils/Face/Face.hpp"

using namespace std;

class OBJToVLF {
    private: 
        //From OBJ
        map<unsigned int, Vertex*> listOfVertices;
        map<unsigned int, Edge*> listOfEdges;
        map<unsigned int, Face*> listOfFaces;
        //VLF lists
        map<unsigned int, Vertex*> vlfListOfVertices;
        map<unsigned int, Edge*> vlfListOfEdges;
        map<unsigned int, Face*> vlfListOfFaces;
    public:
        OBJToVLF();
        void readOBJFile(string);
        //TEMP
        void readVLFFile(string );
        //END TEMP
        void createVLFFile(string);
        void writeListOfVertices(ofstream *);
        void writeListOfEdges(ofstream *);
        void writeListOfFaces(ofstream *);
        //TEMP (REFERENCE)
        void readListOfVertices(ifstream *, unsigned int); 
        void readListOfEdges(ifstream *, unsigned int); 
        void readListOfFaces(ifstream *, unsigned int);
        //END TEMP 
        void generateTriangularFaces();
        void printRetrievedDataFromOBJ();
        //Getters
        map<unsigned int, Vertex*> getListOfVertices();
        map<unsigned int, Edge*> getListOfEdges();
        map<unsigned int, Face*> getListOfFaces();
};

#endif