#include "MatrixBuilder.h"

#include <sstream>
#include <iostream>

MatrixBuilder::MatrixBuilder(int mode) {
    this->mode = mode;
}

MatrixBuilder::~MatrixBuilder() {}

const int MatrixBuilder::getMode() {
    return mode;
}


const vector<vector<short>> MatrixBuilder::constructMatrix(vector<string> lines) {
    vector<vector<short>> matrix;
    if (mode == 1) {
        int n = atoi(lines[0].c_str());
        short backgroundColor = atoi(lines[1].c_str());
        vector<pair<int, int>> coords = splitAndParse(lines[2], ' ');

        bool valid = validateCoords(coords);
        if (valid && n > 0) {
            for (int y = 0; y < n; ++y) {
                vector<short> tmp;
                for (int x = 0; x < n; ++x) {
                    //TODO: check coords to draw inner rectangle
                    tmp.push_back(backgroundColor);
                }
                matrix.push_back(tmp);
            }
        } else {
            std::cout << "error: validation of rectangle failure." << std::endl;
            //TODO: error or exception
        }
    }

    return matrix;
}


vector<pair<int, int>> MatrixBuilder::splitAndParse(const string &s, char delim) {
    vector<pair<int, int>> elems;
    stringstream ss;
    ss.str(s);
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

bool MatrixBuilder::validateCoords(vector<pair<int, int>> coords) {
    bool valid = false;
    if (coords.size() == 4) {
        int a1 = coords[1].first - coords[0].first;
        int b1 = coords[2].second - coords[0].second;
        int a2 = coords[3].first - coords[2].first;
        int b2 = coords[3].second - coords[1].second;

        bool edgeA1Straight = coords[1].second == coords[0].second;
        bool edgeB1Straight = coords[2].first == coords[0].first;
        bool edgeA2Straight = coords[3].second == coords[2].second;
        bool edgeB2Straight = coords[3].first == coords[1].first;
        valid = a1 == a2 && b1 == b2 && a1 > 0 && b1 > 0;
        valid = valid && edgeA1Straight && edgeB1Straight && edgeA2Straight && edgeB2Straight;
    }
    return valid;
}

//??
/*
 * const bool MatrixBuilder::constructMatrix(vector<string> lines){
    //TODO read lines
    bool matrix[4][4] = {{0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0}};
    return matrix;
}*/
