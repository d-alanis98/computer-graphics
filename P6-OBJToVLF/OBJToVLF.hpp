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
        //File creation
        void readOBJFile(string);
        void createVLFFile(string);
        void writeListOfVertices(ofstream *);
        void writeListOfEdges(ofstream *);
        void writeListOfFaces(ofstream *);
        //TEMP (REFERENCE)
        void readListOfVertices(ifstream *, unsigned int); 
        void readListOfEdges(ifstream *, unsigned int); 
        void readListOfFaces(ifstream *, unsigned int);
        //END TEMP 
        //VLF lists creation
        void setVLFEdgesList(); 
        void setVLFFacesList();
        void addEdgeToTheList(Edge *); 
        void addFaceToTheList(Face *);
        //Face conditioning
        void createTriangularFace(vector<Vertex *>); 
        void generateTriangularFaces(vector<Vertex*>);
        //Getters
        map<unsigned int, Vertex*> getListOfVertices();
        map<unsigned int, Edge*> getListOfEdges();
        map<unsigned int, Face*> getListOfFaces();
        //Search
        unsigned int keyOfVertex(Vertex *);
        unsigned int keyOfEdge(Edge *);
        //Utils
        void printResults();
        void printRetrievedDataFromOBJ();
        void printVLFFileInformation(string);
        
};

#endif