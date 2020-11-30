#include <iostream>
#include <string>
#include "VLFToVLFFaceOriented.hpp"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        cout << "Usage mode: ./test pathToVLFFile resultVLFFileName" << endl;
        exit(1);
    }

    string pathToFile = argv[1];
    string resultVLFFileName = argv[2];
    //We create a new VLFToVLFFaceOriented instance
    VLFToVLFFaceOriented *reader = new VLFToVLFFaceOriented();
    reader->setInitialDataFromFile(pathToFile);
    
    return 0;
}