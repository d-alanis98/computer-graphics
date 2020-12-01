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
        //Bad orientation flag
        bool badOriented;
    public:
        //Constructor
        VLFToVLFFaceOriented();
        //File creation
        void setInitialDataFromFile(string);
        void writeListOfVertices(ofstream *);
        void writeListOfEdges(ofstream *);
        void writeListOfFaces(ofstream *);
        void fixBadEdgeOrientation(pair<unsigned int, Face*>, Edge *);
        bool areFacesCorrectlyOriented();
        void createVLFFaceOrientedFile(string);
        void setEdgesAndFacesWithCorrectedOrientation();
        void verifyCommonEdgeAndFixIfNecessary(pair<unsigned int, Face*>, pair<unsigned int, Face*>);
        //Calculations
        Vertex* getFaceNormal(Face *);
        //VLF lists creation
        void addEdgeToTheVLFFaceOrientedList(Edge *); 
        void replaceFaceInTheVLFFaceOrientedList(pair<unsigned int, Face*>);
        //Utils
        Edge *getCommonEdge(Face *, Face *); 
        unsigned int keyOfEdge(Edge *);
        vector<Edge*> getFaceEdges(Face *);
        vector<Vertex*> getFaceVertices(Face *);
        map<unsigned int, Face *> getFaceNeighboors(Face *, unsigned int); 
};


#endif

