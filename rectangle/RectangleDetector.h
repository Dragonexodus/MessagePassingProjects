
#ifndef PROJECT_RECTANGLEDETECTOR_H
#define PROJECT_RECTANGLEDETECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include "search/RectangleValidator.h"
#include <sstream>
#include "matrixCreation/MatrixBuilder.h"

using namespace std;

class RectangleDetector {
public:
    RectangleDetector();

    virtual ~RectangleDetector();

    pair<int, RectangleValidator> search(const vector<vector<int>> &matrix);

    const vector<vector<int>> readFile(const char *term);

    void printMatrix(vector<vector<int>> matrix);

    int testConfigs(const char *term);

    enum SEARCH_VALUES {
        MISMATCH_FOUND,
        RECT_FOUND,
        NO_RECT
    };

    void printOldMatrix(int *array, int n, int m);
};

#endif //PROJECT_RECTANGLEDETECTOR_H
