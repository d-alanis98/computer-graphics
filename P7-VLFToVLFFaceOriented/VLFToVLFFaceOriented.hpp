#ifndef VLF_TO_VLF_FACE_ORIENTED_H
#define VLF_TO_VLF_FACE_ORIENTED_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "../utils/Edge/Edge.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Face/Face.hpp"

using namespace std;

class VLFToVLFFaceOriented {
    private:
        //From VLF
        map<unsigned int, Vertex*> listOfVertices;
        map<unsigned int, Edge*> listOfEdges;
        map<unsigned int, Face*> listOfFaces;
        //VLF Face oriented lists
        map<unsigned int, Vertex*> vlfListOfVertices;
        map<unsigned int, Edge*> vlfListOfEdges;
        map<unsigned int, Face*> vlfListOfFaces;
    public:
        //Constructor
        VLFToVLFFaceOriented();
        //File creation
        void setInitialDataFromFile(string);
        void writeListOfVertices(ofstream *);
        void writeListOfEdges(ofstream *);
        void writeListOfFaces(ofstream *);
        void createVLFFaceOrientedFile(string);
        void setEdgesAndFacesWithCorrectedOrientation();
        //Calculations
        vector<double> getFaceNormal(Face *);
        //VLF lists creation
        void addEdgeToTheVLFFaceOrientedList(Edge *); 
        void addFaceToTheVLFFaceOrientedList(Face *);
};


#endif

