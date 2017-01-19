
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

    ~RectangleDetector();

    pair<int, RectangleValidator> search(short *matrix, int n, int i);

    const pair<short *, int> readFile(const char *term);

    int testConfigs(const char *term);

    enum SEARCH_VALUES {
        MISMATCH_FOUND,
        RECT_FOUND,
        NO_RECT
    };

    void printOldMatrix(short *array, int n, int m);
    void printOldMatrix(int *array, int n, int m);

    void printResult(int res);
};

#endif //PROJECT_RECTANGLEDETECTOR_H
