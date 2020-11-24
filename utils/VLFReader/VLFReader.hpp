#ifndef VLF_READER_H
#define VLF_READER_H

#include <vector>
#include <string>
#include "../FileReader/FileReader.hpp"

class VLFReader: public FileReader {
    public:
        int getDataFromFile(string &);
        void addVertexToTheList(Vertex *); 
        void addEdgeToTheList(Edge *); 
        void addFaceToTheList(Face *);
        void readListOfVertices(ifstream *, unsigned int);
        void readListOfEdges(ifstream *, unsigned int);
        void readListOfFaces(ifstream *, unsigned int);
};

#endif