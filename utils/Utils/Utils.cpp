#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Utils.hpp"

using namespace std;

vector<string> Utils::split(const string &input, char delimiter) {
    vector<string> result;
    stringstream searchString(input);
    string item;

    while(getline(searchString, item, delimiter))
        result.push_back (item);

    return result;
}