#include "VectorParser.h"

vector<pair<int, int>> VectorParser::splitAndParseToCoords(const string &s, char delim) {
    vector<pair<int, int>> elems;
    stringstream ss(s);
    string item;
    int i = 0;
    int tmp = -1;
    while (getline(ss, item, delim)) {
        if (i % 2 == 1) {//2 elems collected
            pair<int, int> coord(tmp, atoi(item.c_str()));
            elems.push_back(coord);
        }
        tmp = atoi(item.c_str());
        i++;
    }
    return elems;
}

vector<int> VectorParser::splitAndParseToLine(const string &s, char delim) {
    vector<int> elems;
    stringstream ss(s);
    int parsedElem = 0;
    string item;
    while (getline(ss, item, delim)) {
        parsedElem = atoi(item.c_str()) % 2;
        elems.push_back(parsedElem);
    }
    return elems;
}
