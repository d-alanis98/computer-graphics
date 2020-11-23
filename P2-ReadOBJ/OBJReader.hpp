#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <vector>
#include <string>
#include "../utils/FileReader/FileReader.hpp"

using namespace std;

class OBJReader: public FileReader {
    public:
        int getDataFromFile(string &);
        void getEdgesFromFaceVertices();
        vector<int> getVerticesKeysList(string);
        void createEdge(int, int, vector<Vertex *>, unsigned int *);
};

#endif