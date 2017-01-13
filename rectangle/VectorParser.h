//
// Created by matthias on 13.01.17.
//

#ifndef PROJECT_VECTORPARSER_H
#define PROJECT_VECTORPARSER_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class VectorParser {
public:
    VectorParser();

    virtual ~VectorParser();

    vector<pair<int, int>> splitAndParseToCoords(const string &s, char delim);

    vector<short> splitAndParseToLine(const string &s, char delim);

private:
    stringstream ss;

    string item;

};


#endif //PROJECT_VECTORPARSER_H
