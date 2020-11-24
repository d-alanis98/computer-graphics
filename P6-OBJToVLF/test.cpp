#include <iostream>
#include "OBJToVLF.hpp"


using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        cout << "[ERROR]: Usage mode: ./test pathToOBJ pathToVLF" << endl;
        exit(1);
    }

    string filePath = argv[1];
    string vlfPath = argv[2];

    OBJToVLF *transformer = new OBJToVLF();
    transformer->readOBJFile(filePath);
    transformer->printRetrievedDataFromOBJ();
    transformer->createVLFFile(vlfPath);
    transformer->printResults();
    transformer->printVLFFileInformation(vlfPath);
    return 0;
}