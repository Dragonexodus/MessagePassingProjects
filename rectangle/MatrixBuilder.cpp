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
    if (mode == 1 || mode == 2) {
        int n = atoi(lines[0].c_str());
        short background = atoi(lines[1].c_str()) % 2;
        short foreground = (background + 1) % 2;
        vector<pair<int, int>> coords = splitAndParseToCoords(lines[2], ' ');
        if (mode == 1) {
            bool valid = validateRectCoords(coords, n);
            if (valid) {
                matrix = fill(n, background);
                for (int x = coords[0].first; x < coords[1].first; ++x) {
                    for (int y = coords[0].second; y < coords[2].second; ++y) {
                        matrix[x][y] = foreground;
                    }
                }
            } else {
                std::cout << "error: validation of rectangle failure." << std::endl;
            }
        } else {
            bool valid = validateCoords(coords, n);
            if (valid) {
                matrix = fill(n, background);
                for (int i = 0; i < coords.size(); ++i) {
                    matrix[coords[i].first][coords[i].second] = foreground;
                }
            } else {
                std::cout << "error: validation of rectangle failure." << std::endl;
            }
        }
    } else if (mode == 3) {
        //TODO: read and parse simple matrix
    }

    return matrix;
}


vector<pair<int, int>> MatrixBuilder::splitAndParseToCoords(const string &s, char delim) {
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

bool MatrixBuilder::validateRectCoords(vector<pair<int, int>> coords, int n) {
    bool valid = false;
    if (coords.size() == 3) {
        int a1 = coords[1].first - coords[0].first;
        int b1 = coords[2].second - coords[0].second;

        bool edgeA1Straight = coords[1].second == coords[0].second;
        bool edgeB1Straight = coords[2].first == coords[0].first;
        bool lowerThanN = coords[0].first < n && coords[1].first < n && coords[2].first < n &&
                          coords[0].second < n && coords[1].second < n && coords[2].second < n;
        bool notNegative = coords[0].first >= 0 && coords[1].first >= 0 && coords[2].first >= 0 &&
                           coords[0].second >= 0 && coords[1].second >= 0 && coords[2].second >= 0 && n > 0;
        valid = a1 > 0 && b1 > 0 && edgeA1Straight && edgeB1Straight && notNegative && lowerThanN;
    }
    return valid;
}

bool MatrixBuilder::validateCoords(vector<pair<int, int>> coords, int n) {
    bool valid = false;
    if (coords.size() > 0) {
        valid = true;
        for (int i = 0; i < coords.size(); ++i) {
            valid = valid && coords[i].first < n && coords[i].first >= 0 && coords[i].second < n &&
                    coords[i].second >= 0;
        }
    }
    return valid;
}

vector<vector<short>> MatrixBuilder::fill(int n, short background) {
    vector<vector<short>> matrix;
    for (int y = 0; y < n; ++y) {
        vector<short> tmp;
        for (int x = 0; x < n; ++x) {
            tmp.push_back(background);
        }
        matrix.push_back(tmp);
    }
    return matrix;
}
