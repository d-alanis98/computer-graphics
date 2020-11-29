#ifndef VLF_TO_VLF_FACE_ORIENTED_H
#define VLF_TO_VLF_FACE_ORIENTED_H

#include <iostream>
#include <map>
#include <string>
#include "../utils/Edge/Edge.hpp"
#include "../utils/Vertex/Vertex.hpp"
#include "../utils/Face/Face.hpp"

using namespace std;

class VLFToVLFFaceOriented {

    public:
        //List of edges
        map<unsigned int, Edge*> listOfEdges;
        //List of the raw vertices and the transformed vertices (the ones that fit in the raster)
        map<unsigned int, Vertex*> listOfVertices, listOfTransformedVertices;
        //List of faces
        map<unsigned int, Face*> listOfFaces;
        VLFToVLFFaceOriented();
        void setInitialDataFromFile(string);
};


#endif

