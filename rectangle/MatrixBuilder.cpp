#include "MatrixBuilder.h"
#include "CoordValidator.h"
#include "VectorParser.h"

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
    VectorParser *parser = new VectorParser();
    if (mode == 1 || mode == 2) {
        int n = atoi(lines[0].c_str());
        short background = atoi(lines[1].c_str()) % 2;
        short foreground = (background + 1) % 2;
        vector<pair<int, int>> coords = parser->splitAndParseToCoords(lines[2], ' ');
        CoordValidator *validator = new CoordValidator(coords);
        if (mode == 1) {
            bool valid = validator->validateRectCoords(n);
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
            bool valid = validator->validateCoords(n);
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
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            matrix.push_back(parser->splitAndParseToLine(*it, ' '));
        }
    }

    return matrix;
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
