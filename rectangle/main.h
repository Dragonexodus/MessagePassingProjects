#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "matrixCreation/MatrixBuilder.h"

using namespace std;

const vector<vector<int>> readFile();

void printMatrix(vector<vector<int>> matrix);

int search(const vector<vector<int>> &matrix);

bool indexRectHasValues(vector<vector<int>> indexRect);

enum SEARCH_VALUES {
    MISMATCH_FOUND,
    RECT_FOUND,
    NO_RECT
};

#endif //PROJECT_MAIN_H
