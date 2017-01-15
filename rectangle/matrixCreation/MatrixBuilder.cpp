#include "MatrixBuilder.h"
#include "CoordValidator.h"
#include "VectorParser.h"

#include <iostream>

MatrixBuilder::MatrixBuilder(const int mode, const vector<string> lines) {
    constructMatrix(mode, lines);
}

MatrixBuilder::~MatrixBuilder() {}

void MatrixBuilder::constructMatrix(const int mode, const vector<string> lines) {
    if (mode == MODE_COMPLETE_RECTANGLE || mode == MODE_POSITION_PLACEMENT) {
        int n = atoi(lines[0].c_str());
        int background = atoi(lines[1].c_str()) % 2;
        int foreground = (background + 1) % 2;
        vector<pair<int, int>> coords = VectorParser::splitAndParseToCoords(lines[2], ' ');
        CoordValidator validator = CoordValidator(coords, n, mode);
        if (validator.getValidation()) {
            fillBackground(n, background);
            if (mode == MODE_COMPLETE_RECTANGLE) {
                drawCompleteRectangle(foreground, coords);
            } else {
                for (auto it = coords.begin(); it != coords.end(); ++it) {
                    matrix[it->first][it->second] = foreground;
                }
            }
        } else {
            std::cout << "error: validation of rectangle failure." << std::endl;
        }
    } else if (mode == MODE_CUSTOM) {
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            matrix.push_back(VectorParser::splitAndParseToLine(*it, ' '));
        }
    } else {
        cout << "error: wrong mode." << endl;
    }
}

void MatrixBuilder::drawCompleteRectangle(const int foreground, const vector<pair<int, int>> &coords) {
    for (int x = coords[0].first; x <= coords[1].first; ++x) {
        for (int y = coords[0].second; y <= coords[2].second; ++y) {
            matrix[x][y] = foreground;
        }
    }
}

void MatrixBuilder::fillBackground(const int n, const int background) {
    for (int y = 0; y < n; ++y) {
        vector<int> tmp;
        for (int x = 0; x < n; ++x) {
            tmp.push_back(background);
        }
        matrix.push_back(tmp);
    }
}

const vector<vector<int>> MatrixBuilder::getMatrix() {
    return matrix;
}
