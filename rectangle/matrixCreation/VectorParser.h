#ifndef PROJECT_VECTORPARSER_H
#define PROJECT_VECTORPARSER_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class VectorParser {
public:
    static vector<pair<int, int>> splitAndParseToCoords(const string &s, char delim);

    static vector<int> splitAndParseToLine(const string &s, char delim);

};


#endif //PROJECT_VECTORPARSER_H
