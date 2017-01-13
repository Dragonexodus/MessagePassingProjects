//
// Created by matthias on 13.01.17.
//

#include "VectorParser.h"


vector<pair<int, int>> VectorParser::splitAndParseToCoords(const string &s, char delim) {
    vector<pair<int, int>> elems;
    ss.str(s);
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

vector<short> VectorParser::splitAndParseToLine(const string &s, char delim) {
    vector<short> elems;
    ss.str(s);
    short parsedElem;
    while (getline(ss, item, delim)) {
        parsedElem = atoi(item.c_str()) % 2;
        elems.push_back(parsedElem);
    }
    return elems;
}

VectorParser::~VectorParser() {

}

VectorParser::VectorParser() {}
